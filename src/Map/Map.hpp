#ifndef MAP_HPP
#define MAP_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Edge.hpp"

using namespace std;

class Map {
  private:
    // vector storing vertices in the map: id of each vertex = index in vector
    // vector<Vertex*> vertices;

    // Map: name of vertex -> id of vertex = index storing vertex ptr
    unordered_map<string, unsigned int> vertexId;

    // Directed edge in vector represents an undirected edge used in MST
    vector<Edge*> undirectedEdges;

    /*
     * Add a vertex with name and x, y coordinates to the map graph. Returns
     * false if the name already existed in the map graph, and true otherwise
     */
    bool addVertex(const string& name, float x, float y);

    /*
     * Add an undirected edge between vertices with names "name1" and "name2".
     * Returns false if either name is not in the map graph.
     */
    bool addEdge(const string& name1, const string& name2);

    void backtraceThePath(Vertex* node, vector<Vertex*>* path);

    Vertex* find(Vertex* vertex);

    bool unionVerts(Vertex* v1, Vertex* v2);

  public:
    vector<Vertex*> vertices;
    /* TODO */
    Map();

    /* Build the map graph from vertex and edge files */
    bool buildMapFromFile(const string& vertexFileName,
                          const string& edgeFileName);

    /* TODO */
    void Dijkstra(const string& from, const string& to,
                  vector<Vertex*>& shortestPath);

    /* TODO */
    void findMST(vector<Edge*>& MST);

    /* TODO */
    void crucialRoads(vector<Edge*>& roads);

    /* Destructor of Map graph */
    ~Map();
};

#endif  // Map_HPP