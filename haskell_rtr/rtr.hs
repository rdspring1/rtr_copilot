module Main where
import Data.Matrix
import Data.Bits

data Resample = Resample { resample :: Bool, reconstruct :: Bool }
data Interval = Interval { minV :: Double, maxV :: Double }
data Neighborhood = Neighborhood { delta :: [Interval], width :: [Interval] }
data RNeighborhood = RNeighborhood { reconstruct :: bool, n :: Neighborhood }

main = do
	let hyperRect = [(Interval 0.0 0.0), (Interval 0.35 0.36), (Interval 0.0 0.0), (Interval 0.0 0.0)]
	let pendulum_reach_time = 0.75
	printHyperRect $ facelift hyperRect pendulum_reach_time

facelift :: [Interval] -> Double -> [Interval]
facelift hyperRect reachTimeRemaining
	| reachTimeRemaining <= 0 = hyperRect
facelift hyperRect reachTimeRemaining = facelift nextHyperRect (reachTimeRemaining-advanceReachTime)
	where	nextHyperRect = advanceBox hyperRect (delta neighborhood) advanceReachTime
		advanceReachTime = min (minCrossReachTime (delta neighborhood) (width neighborhood) (1/0)) reachTimeRemaining
		neighborhood = constructNeighborhood hyperRect 1 [] []
		num_states = 4 :: Int

-- TODO - constructNeighborhood

reconstructNeighborhood ::[Interval] -> Neighborhood -> Int -> Bool -> [Interval] -> [Interval] -> Neighborhood
reconstructNeighborhood hyperRect flatN states rebuild delta' width'
	| states > num_states = (RNeighborhood rebuild (Neighborhood delta' width'))
	| otherwise = reconstructNeighborhood hyperRect flatN (states+1) (rebuild .|. (reconstruct rd)) ((Interval minDV maxDV):delta') ((Interval minWidth maxWidth):width')  
		where 	minWidth = (if (resample rdMin) then (minDV * reachTimeStep) else (minV ((width flatN) !! states)))
		 	maxWidth = (if (resample rdMax) then (maxDV * reachTimeStep) else (maxV ((width flatN) !! states)))
			rdMin = resampleDerivative False (minV ((delta flatN) !! states)) (minV ((width flatN) !! states))
			rdMax = resampleDerivative True (maxV ((delta flatN) !! states)) (maxV ((width flatN) !! states))
			minDV = (minV (getMinMaxDerivative (generateNeighborhood hyperRect states False (width flatN)) (num_states^2) states (-1/0) (1/0)))
			maxDV = (maxV (getMinMaxDerivative (generateNeighborhood hyperRect states True (width flatN)) (num_states^2) states (-1/0) (1/0)))
			num_states = 4
			reachTimeStep = 0.0006

-- TODO - generateNeighborhood
-- TODO - resampleDerivative

flatNeighborhood :: [Interval] -> Int -> [Interval] -> [Interval] -> Neighborhood
flatNeighborhood hyperRect states delta' width'
	| states > num_states = (Neighborhood delta' width')
	| otherwise = flatNeighborhood hyperRect (states+1) ((Interval minDV maxDV):delta') ((Interval minWidth maxWidth):width')
		where 	minWidth = minDV * reachTimeStep
			maxWidth = maxDV * reachTimeStep
			minDV = (minV (getMinMaxDerivative (generateNeighborhood hyperRect states False) (num_states^2) states (-1/0) (1/0)))
			maxDV = (maxV (getMinMaxDerivative (generateNeighborhood hyperRect states True) (num_states^2) states (-1/0) (1/0)))
			num_states = 4
			reachTimeStep = 0.0006 

generateNeighborhood :: [Interval] -> Int -> Bool -> [Interval]
generateNeighborhood [] _ _ = []
generateNeighborhood (x:xs) 1 maxFace
	| maxFace 	= (Interval (maxV x) (maxV x)):(generateNeighborhood xs (-1) maxFace)
	| otherwise 	= (Interval (minV x) (minV x)):(generateNeighborhood xs (-1) maxFace)
generateNeighborhood (x:xs) states maxFace = (Interval (minV x) (maxV x)):(generateNeighborhood xs (states-1) maxFace)


getMinMaxDerivative :: [Interval] -> Int -> Int -> Double -> Double -> Interval
getMinMaxDerivative _ pts _ minDerivative maxDerivative
	| pts <= 0 = (Interval minDerivative maxDerivative)
getMinMaxDerivative hyperRect pts dim minDerivative maxDerivative = getMinMaxDerivative hyperRect (pts-1) dim (min minDerivative dv) (max maxDerivative dv)
	where	dv = getElem dim 1 (derivative a b k (fromList num_states 1 (generateHyperPoint pts hyperRect)))
		a = fromList num_states num_states [0,1,0,0, 0,-10.95,-2.75,0.0043, 0,0,0,1, 0,24.92,28.58,-0.044]
		b = fromList num_states num_inputs [0, 1.94, 0, -4.44]
		k = fromList num_inputs num_states [0.4072, 7.2373, 18.6269, 3.6725]
		num_states = 4
		num_inputs = 1
		
generateHyperPoint :: Int -> [Interval] -> [Double]
generateHyperPoint _ [] = []
generateHyperPoint pts (x:xs) =
	(if (pts .&. 1) == 1 then (maxV x) else (minV x)):generateHyperPoint (shiftR pts 1) xs
	

minCrossReachTime :: [Interval] -> [Interval] -> Double -> Double
minCrossReachTime [] _ minReachTime = minReachTime
minCrossReachTime _ [] minReachTime = minReachTime
minCrossReachTime (x:xs) (y:ys) minReachTime = minCrossReachTime xs ys (min (min minReachTime minTimeDim) maxTimeDim)
	where 	minTimeDim = (minV y) / (abs $ minV x)
		maxTimeDim = (minV y) / (abs $ minV x)  

advanceBox :: [Interval] -> [Interval] -> Double -> [Interval]
advanceBox [] _ reachTime = []
advanceBox _ [] reachTime = []
advanceBox (x:xs) (y:ys) reachTime = (Interval newmin newmax):(advanceBox xs ys reachTime) 
	where 	newmin = (minV x) + reachTime * (minV y)
		newmax = (maxV x) + reachTime * (maxV y)

derivative :: (Num a) => Matrix a -> Matrix a -> Matrix a -> Matrix a -> Matrix a
derivative a b k state = (multStd a state) + (multStd b (multStd k state))

printValue :: (Show a) => a -> IO ()
printValue x = putStr (show x) 

printHyperRect :: [Interval] -> IO ()
printHyperRect [] = return () 
printHyperRect [x] = printInterval x >> putStrLn "]" 
printHyperRect (x:xs) = printInterval x >> putStr "]\t"  >> printHyperRect xs

printInterval :: Interval -> IO ()
printInterval x = putStr "[" >> (printValue $ (minV x)) >> putStr " " >> (printValue $ (maxV x))
