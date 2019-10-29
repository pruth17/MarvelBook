
#include <iostream>
#include <cstdlib>
#include <vector>
#include "List.h"

using namespace std;

class Graph
{
public:

    /**Constructors and Destructors*/

    Graph(int n);
    //initializes an empty graph to have n vertices

    /*** Access Functions ***/

    int getNumEdges() const;
    //returns the number of edges in the graph

    int getNumVertices() const;
    //returns the number of vertices in the graph

    bool isEmpty() const;
    //returns whether the graph is empty (no vertices)

    int getDistance(int v) const;
    //Pre: v <= numVertices
    //Returns the value of the distance[v]

    int getParent(int v) const;
    //Pre: v <= numVertices
    //Returns the value of the parent[v]

    char getColor(int v) const;
    //Pre: v <= numVertices
    //Returns the value of color[v]

    /*** Manipulation Procedures ***/

    void addEdge(int u, int v);
    //inserts vertex v into the adjacency list of vertex u (i.e. inserts v into the list at index u)
    //and inserts u into v.
    
    void addEdge1(int u , int v);
    /*** Additional Operations ***/

    void printGraph(ostream& out);
    //Prints the adjacency list of each vertex in the graph,
    //vertex: <space separated list of adjacent vertices>
    //Prints to the console or to an output file given the ostream parameter

    void printBFS(ostream& out);
    //Prints the current values in the parallel vectors after executing BFS
    //Prints to the console or to an output file given the ostream parameter
    //First prints the heading:
    //v <tab> c <tab> p <tab> d <tab>
    //Then, prints out this information for each vertex in the graph
    //Note that this function is intended purely to help you debug your code

    List<int> BFS(int source);
    //Performs breath first search on this Graph give a source vertex
    //pre: at least one vertex must exist
    //pre: source is a vertex in the graph
    
    List<int> seeFriends(int source);
    
    void removeFriend(int source, int rem);
    
    void printPath(int source, int destination, ostream& out);
    //Prints the path from the source to the destination vertex
    //Prints to the console or to an output file given the ostream parameter

private:
    int vertices;
    double edges; //number of edges and vertices
    vector<List<int> > adj;
    vector<char> color;
    vector<int> distance;
    vector<int> parent;

};







