// NAME: Gary Tou
// FILE: Graph.cpp
// DESCRIPTION: Implementation of the Graph class.

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#include "Graph.h"
#include "QueueInt.h"
#include "StackInt.h"

// Constructor: load the graph from a file
Graph::Graph(char *filename)
{
  string line;

  // Open file
  ifstream graphFile(filename);

  // Get the number of verticies
  graphFile >> this->numVertices;

  // Create the matrix
  this->createMatrix(this->numVertices);

  // Get each edge from the file
  int vertexA;
  int vertexB;
  int weight;
  while (graphFile >> vertexA)
  {
    // there should be two more ints on this line (vertexB and weight)
    graphFile >> vertexB;
    graphFile >> weight;

    // Add the undirected edge to the matrix
    this->addEdge(vertexA, vertexB, weight);
  }

  // Close file
  graphFile.close();
}

// Destructor
Graph::~Graph()
{
  // Delete 2D matrix array
  for (int i = 0; i < this->numVertices; i++)
  {
    delete[] this->matrix[i];
  }
  delete[] this->matrix;
}

// Display the adjacency matrix
void Graph::display() const
{
  for (int i = 0; i < this->numVertices; i++)
  {
    for (int j = 0; j < this->numVertices; j++)
    {
      // Print out the current element
      if (i == j)
      {
        cout << 0;
      }
      else if (this->matrix[i][j] == -1)
      {
        cout << "x";
      }
      else
      {
        cout << this->matrix[i][j];
      }

      // Print a space
      cout << " ";

      // If this is the last element, print a new line
      if (j == this->numVertices - 1)
      {
        cout << endl;
      }
    }
  }
}

// Displays the depth first search starting at the given vertex
void Graph::displayDFS(int vertex) const
{
  // Print label:
  cout << "DFS at vertex " << vertex << ": ";

  // Create bool array to track if a vertex is visited
  bool visited[this->numVertices];
  for (int i = 0; i < this->numVertices; i++)
  {
    visited[i] = false;
  }

  // Call the recursive helper (prints the results)
  this->dfsHelper(vertex, visited);

  // Print a new line
  cout << endl;
}

// Recursive DFS Helper
void Graph::dfsHelper(int vertex, bool *visited) const
{
  // Mark the vertex as visited
  visited[vertex] = true;

  // Print the vertex
  cout << vertex << " ";

  for (int i = 0; i < this->numVertices; i++)
  {
    if (!(visited[i]) && this->isAdjacent(vertex, i))
    {
      dfsHelper(i, visited);
    }
  }
}

// Perform breadth first search starting at the given vertex
void Graph::displayBFS(int vertex) const
{
  // Print label:
  cout << "BFS at vertex " << vertex << ": ";

  // Create bool array to track if a vertex is visited
  bool visited[this->numVertices];
  for (int i = 0; i < this->numVertices; i++)
  {
    visited[i] = false;
  }

  // Create a queue for tracking processing order
  QueueInt queue;

  // PROCESS THE FIRST VERTEX
  // Mark the vertex as visited
  visited[vertex] = true;

  // Print the vertex
  cout << vertex << " ";

  // Enqueue this vertex for processing later
  queue.enqueue(vertex);

  // PROCESS THE REMAINING VERTICES
  while (!queue.isEmpty())
  {
    vertex = queue.dequeue();

    for (int i = 0; i < this->numVertices; i++)
    {
      if (!(visited[i]) && this->isAdjacent(vertex, i))
      {
        // PROCESS THE CURRENT VERTEX
        // Mark the vertex as visited
        visited[i] = true;

        // Print the vertex
        cout << i << " ";

        // Enqueue this vertex for processing later
        queue.enqueue(i);
      }
    }
  }

  // Print a new line
  cout << endl;
}

// Compute the cost of a minimum spanning tree.
int Graph::computeMSTCost() const
{
  int weightSum = 0;

  // Create bool array to track if a vertex is visited
  bool visited[this->numVertices];
  for (int i = 0; i < this->numVertices; i++)
  {
    visited[i] = false;
  }

  // Add first vertex to tree
  visited[0] = true;

  for (int i = 0; i < this->numVertices; i++)
  {
    // Find the next vertex
    int nextEdge[3]; // results from mstNextEdge() will be saved to this array
    this->mstNextEdge(visited, nextEdge);

    int vertexA = nextEdge[0]; // vertexA is already in the tree (visited)
    int vertexB = nextEdge[1]; // vertexB is not yet in the tree (to be visited)
    int weight = nextEdge[2];

    // Handle if a vertex was not found
    if (vertexA == -1 || vertexB == -1 || weight == -1)
    {
      // This most likely means the graph is not connected. We will check later
      // to verify
      continue;
    }

    // Add vertexB to the tree (visited)
    visited[vertexB] = true;
    weightSum += weight;
  }

  for (int i = 0; i < this->numVertices; i++)
  {
    if (!visited[i])
    {
      // The graph is disconnected
      return -1;
    }
  }

  return weightSum;
}

int *Graph::mstNextEdge(bool *visited, int edge[]) const
{
  edge[0] = -1; // vertexA
  edge[1] = -1; // vertexB
  edge[2] = -1; // weight

  for (int i = 0; i < this->numVertices; i++)
  {
    for (int j = 0; j < this->numVertices; j++)
    {
      int weight = this->matrix[i][j];

      // If there is an edge between the two, and one is outside,
      // and the other is outside
      if (this->isAdjacent(i, j) && (visited[i] && !visited[j]))
      {
        // Handle edge case where first edge has not been found
        if (edge[0] == -1 || edge[1] == -1)
        {
          edge[0] = i;
          edge[1] = j;
          edge[2] = weight;
        }

        int minWeight = this->matrix[edge[0]][edge[1]];

        // If we have found a smaller edge
        if (weight < minWeight)
        {
          edge[0] = i;
          edge[1] = j;
          edge[2] = weight;
        }
      }
    }
  }

  return edge;
}

// Create 2D matrix
void Graph::createMatrix(int numVertices)
{
  this->matrix = new int *[numVertices];
  for (int i = 0; i < numVertices; i++)
  {
    this->matrix[i] = new int[numVertices];
    for (int j = 0; j < numVertices; j++)
    {
      // Set all edges to does not exist (-1)
      this->matrix[i][j] = -1;
    }
  }
}

// Add an undirected edge to graph
void Graph::addEdge(int vertexA, int vertexB, int weight)
{
  this->matrix[vertexA][vertexB] = weight;
  this->matrix[vertexB][vertexA] = weight;
}

// Check if two vertices are adjacent
bool Graph::isAdjacent(int vertexA, int vertexB) const
{
  // Graph should be symmetrical because it is undirected
  return this->matrix[vertexA][vertexB] > 0;
}
