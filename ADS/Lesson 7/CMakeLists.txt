cmake_minimum_required(VERSION 2.8)
project(DijkstraGraph C) # Прописываю жёстко компилятор C

add_executable(dijkstra_graph.exe Src/queue.c Src/dijkstra_graph.c)

target_include_directories(dijkstra_graph.exe PRIVATE Inc)
