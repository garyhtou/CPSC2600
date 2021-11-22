// NAME: Gary Tou
// FILE: Graph.h
// DESCRIPTION: Definition of the Graph class.

#ifndef GRAPH_H
#define GRAPH_H

#include "QueueInt.h"
#include "StackInt.h"

class Graph
{

public:
  // Constructor: load the graph from a file
  Graph(char *fileName);

  // Destructor
  ~Graph();

  // Display the adjacency matrix
  void display() const;

  // Display the depth first search from the given vertex
  void displayDFS(int vertex) const;

  // Display the breadth first search from the given vertex
  void displayBFS(int vertex) const;

  // Compute the cost of a minimum spanning tree.
  int computeMSTCost() const;

private:
  // 2D array to store edges and weights
  int **matrix;

  // Number of vertices in the graph
  int numVertices;

  // Create 2D matrix
  void createMatrix(int numVertices);

  // Add edge to graph
  void addEdge(int vertexA, int vertexB, int weight);

  // Check if two vertices are adjacent (assumed undirected graph)
  bool isAdjacent(int vertexA, int vertexB) const;

  // Recursive DFS Helper
  void dfsHelper(int vertex, bool *visited) const;

  // Helper for computeMSTCost(). Finds the small (weight) edge from the set of
  // vertices in visited to the set of vertices outside of visited.
  int* mstNextEdge(bool *visited, int edge[]) const;
};

#endif
