module Main where
import Data.Matrix

data Interval = Interval { min :: Float, max :: Float }
data Neighborhood = Neighborhood { delta :: [Interval], width :: [Interval] }

main = do
	let hyperRect = [[0.0, 0.0], [0.35, 0.36], [0.0, 0.0], [0.0, 0.0]]
	let num_states = 4
	let num_inputs = 1
	let a = fromList num_states num_states [0,1,0,0, 0,-10.95,-2.75,0.0043, 0,0,0,1, 0,24.92,28.58,-0.044]
	let b = fromList num_states num_inputs [0, 1.94, 0, -4.44]
	let k = fromList num_inputs num_states [0.4072, 7.2373, 18.6269, 3.6725]
	let pendulum_derivative = derivative a b k
	let pendulum_reach_time = 0.75
	printHyperRect $ facelift hyperRect pendulum_reach_time

facelift :: (RealFloat a, Ord a, Show a) => [[a]] -> a -> [[a]]
facelift hyperRect reachTimeRemaining
	| reachTimeRemaining <= 0 = hyperRect
facelift hyperRect reachTimeRemaining =
	facelift nextHyperRect (reachTimeRemaining-advanceReachTime)
		where	nextHyperRect = advanceBox hyperRect (delta neighborhood) advanceReachTime
			advanceReachTime = Prelude.min (minCrossReachTime (delta neighborhood) (width neighborhood)) reachTimeRemaining
			neighborhood = constructNeighborhood hyperRect
-- TODO
constructNeighborhood :: (RealFloat a, Ord a) => [[a]] -> Neighborhood
constructNeighborhood hyperRect = Neighborhood [] []

-- TODO
minCrossReachTime :: (RealFloat a, Ord a) => [Interval] -> [Interval] -> a
minCrossReachTime delta width = 0.2

-- TODO
advanceBox :: (RealFloat a, Ord a) => [[a]] -> [Interval] -> a -> [[a]]
advanceBox hyperRect delta advanceReachTime = [[0.0, 1.0]] 

derivative :: (Num a) => Matrix a -> Matrix a -> Matrix a -> Matrix a -> Matrix a
derivative a b k state = (multStd a state) + (multStd b (multStd k state))

printValue :: (Show a) => a -> IO ()
printValue x = putStr (show x) 

printHyperRect :: (Floating a, Show a) => [[a]] -> IO ()
printHyperRect [x] = putStr "[" >> printInterval x >> putStrLn "]" 
printHyperRect (x:xs) = putStr "[" >> printInterval x >> putStr "]\t" >> printHyperRect xs

printInterval :: (Floating a, Show a) => [a] -> IO ()
printInterval [x] = printValue x
printInterval (x:xs) = printValue x >> putStr " " >> printInterval xs 
