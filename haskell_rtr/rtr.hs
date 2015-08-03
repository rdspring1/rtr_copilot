module Main where
import Data.Matrix

main = do
	let hyperRect = [[0,0], [0.35, 0.36], [0.0, 0.0], [0.0, 0.0]]
	let num_states = 4
	let num_inputs = 1
	let a = fromList num_states num_states [0,1,0,0, 0,-10.95,-2.75,0.0043, 0,0,0,1, 0,24.92,28.58,-0.044]
	let b = fromList num_states num_inputs [0, 1.94, 0, -4.44]
	let k = fromList num_inputs num_states [0.4072, 7.2373, 18.6269, 3.6725]
	let hyperPoint = fromList num_states 1 [0, 0.35, 0, 0]
	print (derivative hyperPoint a b k)

derivative :: (Num a) => Matrix a -> Matrix a -> Matrix a -> Matrix a -> Matrix a
derivative state a b k = (multStd a state) + (multStd b (multStd k state))

printValue :: (Show a) => a -> IO ()
printValue x = putStr (show x) 

printHyperRect :: (Floating a, Show a) => [[a]] -> IO ()
printHyperRect [x] = putStr "[" >> printInterval x >> putStrLn "]" 
printHyperRect (x:xs) = putStr "[" >> printInterval x >> putStr "]\t" >> printHyperRect xs

printInterval :: (Floating a, Show a) => [a] -> IO ()
printInterval [x] = printValue x
printInterval (x:xs) = printValue x >> putStr " " >> printInterval xs 
