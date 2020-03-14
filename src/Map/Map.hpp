/**
 * A header class for Map.cpp
 * Author: Tomoya Tokunaga - winter 2020
 */

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

    /**
     * A helper function for Dijkstra's algorithm which push vertices in the
     * shortest path to a result vector.
     *
     * @param Vertex*: a current node
     * @param vector<Vertex*>*: a vector which contains vertices in the shortest
     * path
     */
    void backtraceThePath(Vertex* node, vector<Vertex*>* path);

    /**
     * A function which implements find method of disjoint set. Returns a
     * representation vertex of a set which a given vertex belongs to
     *
     * @param Vertex*: a vertex
     */
    Vertex* find(Vertex* vertex);

    /**
     * A function which implements union method of disjoint set. Returns true if
     * given two vertices belong to the same set
     *
     * @param Vertex*: first vertex
     * @param Vertex*: second vertex
     */
    bool unionVerts(Vertex* v1, Vertex* v2);

    /**
     * A helper function which calculates bridges
     *
     * @param Vertex*: a current node
     * @param vector<Edge*>*: a vector containing bridges
     * @param int: time of traversal
     */
    void crucialRoadsHelper(Vertex* node, vector<Edge*>*& roads, int time);

  public:
    vector<Vertex*> vertices;
    /* TODO */
    Map();

    /* Build the map graph from vertex and edge files */
    bool buildMapFromFile(const string& vertexFileName,
                          const string& edgeFileName);

    /**
     * calculates a shortest path between given two nodes. if there's no such
     * path, a given vector stays empty. otherwise the vector contains vectors
     * in the order of "from" to "to"
     *
     * @param string: a name of a starting node
     * @param string: a name of a ending node
     * @param vector<Vertex*>: contains nodes of a shortest path
     */
    void Dijkstra(const string& from, const string& to,
                  vector<Vertex*>& shortestPath);

    /**
     * calculates a minimum spanning tree of this map. edges included in this
     * spanning tree are pushed in a given vector
     *
     * @param vector<Edge*>: a vector which is pushed edges in a spanning tree
     */
    void findMST(vector<Edge*>& MST);

    /**
     * a function which calculates bridges in a graph
     *
     * @param vector<Edge*>: a vector containing edges which is bridges
     */
    void crucialRoads(vector<Edge*>& roads);

    /* Destructor of Map graph */
    ~Map();
};

#endif  // Map_HPP