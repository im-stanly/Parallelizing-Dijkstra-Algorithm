# Parallelizing-Dijkstra-Algorithm
It's a project at Uni

## To start the program please follow below steps:
- To get a new input please compile the testGenerator.cpp file using "g++ testGenerator.cpp -o testGenerator" 
  and run this script with the arguments of beggining and end of the rage of verticies number what you want the graph to have. 
  Ex. "./testGenerator 100 1000 > input.txt"
- To run single-thread Dijkstra (dijkstra.cpp) you can compile and run as a normal .cpp program 
  "g++ dijkstra.cpp -o dijkstraNormal" and "./dijkstraNormal < input.txt"
- To run the OpenMP version and the version with <thread> libery you have to compile with the specific compile parameters 
  and while running you have to specify the number of threads you want to use. 
  * For dijkstraOMP.cpp use "g++ -fopenmp dijkstraOMP.cpp -o dijkstraOMP"
    and "./dijkstraOMP 4 < input.txt"
  * For dijkstraThread.cpp use "g++-13 -pthread dijkstraThread.cpp -o dijkstraThread" 
    and "./dijkstraThread 4 < input.txt"


## Also, you can use the getPlot.py script which will ask you to specify the range where the graph size will be drawn 
  and it will automatifly test all the version of Dijkstra on the threads = [1, 2, 4, 8, 16, 32, 64]. 
  This script will automaticly use the outputs and create a plot.
