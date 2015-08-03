module Main where

main = do
	let hyperRect = [[0,0], [0.35, 0.36], [0.0, 0.0], [0.0, 0.0]]
	printHyperRect hyperRect

printValue :: (Show a) => a -> IO ()
printValue x = putStr (show x) 

printHyperRect :: (Floating a, Show a) => [[a]] -> IO ()
printHyperRect [x] = putStr "[" >> printInterval x >> putStrLn "]" 
printHyperRect (x:xs) = putStr "[" >> printInterval x >> putStr "]\t" >> printHyperRect xs

printInterval :: (Floating a, Show a) => [a] -> IO ()
printInterval [x] = printValue x
printInterval (x:xs) = printValue x >> putStr " " >> printInterval xs 
