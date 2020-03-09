#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <vector>

using namespace std;

class Edge;

/* This class defines a vertex in map graph. Each vertex has a name and x, y
 * coordinates in the map */
class Vertex {
  public:
    const string name;
    float x;
    float y;
    vector<Edge*> outEdges;  // the adjacency list of this vertex that contains
                             // all outgoing edges

    // member variables for Dijkstra's algorithm
    float distance;    // distance from a root
    Vertex* previous;  // a previous node in a dijkstra shortest path
    bool done;         // true if a shortest distance is already calculated

    // member variables for Kruskal's algorithm
    Vertex* parent;  // a parent node in a disjoint set

    // member variables for crucial roads
    int discoveryTime;
    int low;

    /* The constructor that creates a new vertex */
    Vertex(const string& name, float x, float y)
        : name(name),
          x(x),
          y(y),
          distance(INFINITY),
          previous(nullptr),
          parent(nullptr),
          done(false),
          discoveryTime(-1),
          low(-1) {}
};

struct VertexPtrCmp {
    // decide priority of vertices
    bool operator()(Vertex*& lhs, Vertex*& rhs) const {
        // otherwise return the shorter one
        return lhs->distance > rhs->distance;
    }
};

#endif  // VERTEX_HPP