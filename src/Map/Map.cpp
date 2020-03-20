/**
 * This file implements Map class. A vertex class and edge class used in this
 * class defined in Vertex.hpp and Edge.hpp
 *
 * Author: Tomoya Tokunaga
 */
#include <queue>
#include "Map.hpp"

/* constructor of Map class */
Map::Map() {}

/* Build the map graph from vertex and edge files */
bool Map::buildMapFromFile(const string& vertexFileName,
                           const string& edgeFileName) {
    // add vertices first
    ifstream vertexFile(vertexFileName);
    while (vertexFile) {
        string s;
        if (!getline(vertexFile, s)) break;

        // process data at each line
        istringstream ss(s);
        vector<string> data;
        while (ss) {
            string str;
            if (!getline(ss, str, ' ')) break;
            data.push_back(str);
        }
        if (data.size() != 3) continue;

        // add vertex defined in this line to the graph
        string name(data[0]);
        float x = stoi(data[1]);
        float y = stoi(data[2]);

        addVertex(name, x, y);
    }

    // then add edges
    ifstream edgeFile(edgeFileName);
    while (edgeFile) {
        string s;
        if (!getline(edgeFile, s)) break;

        // process data at each line
        istringstream ss(s);
        vector<string> data;
        while (ss) {
            string str;
            if (!getline(ss, str, ' ')) break;
            data.push_back(str);
        }
        if (data.size() != 2) continue;

        // add edge defined in this line to the graph
        string name1(data[0]);
        string name2(data[1]);

        addEdge(name1, name2);
    }

    return true;
}

/*
 * Add a vertex with name and x, y coordinates to the map graph. Returns
 * false if the name already existed in the map graph, and true otherwise
 */
bool Map::addVertex(const string& name, float x, float y) {
    if (vertexId.count(name) > 0) return false;
    vertexId[name] = vertices.size();
    vertices.push_back(new Vertex(name, x, y));
    return true;
}

/*
 * Add an undirected edge between vertices with names "name1" and "name2".
 * Returns false if either name is not in the map graph.
 */
bool Map::addEdge(const string& name1, const string& name2) {
    if (vertexId.count(name1) == 0 || vertexId.count(name2) == 0) {
        return false;
    }
    unsigned int id1 = vertexId[name1];
    unsigned int id2 = vertexId[name2];
    Vertex* v1 = vertices[id1];
    Vertex* v2 = vertices[id2];
    float weight = sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2));
    v1->outEdges.push_back(new Edge(v1, v2, weight));
    v2->outEdges.push_back(new Edge(v2, v1, weight));

    undirectedEdges.push_back(new Edge(v1, v2, weight));
    return true;
}

/**
 * calculates a shortest path between given two nodes. if there's no such path,
 * a given vector stays empty. otherwise the vector contains vectors in the
 * order of "from" to "to"
 *
 * @param string: a name of a starting node
 * @param string: a name of a ending node
 * @param vector<Vertex*>: contains nodes of a shortest path
 */
void Map::Dijkstra(const string& from, const string& to,
                   vector<Vertex*>& shortestPath) {
    Vertex* start = vertices[vertexId[from]];
    Vertex* dest = vertices[vertexId[to]];

    start->distance = 0;  // set the initial distance

    // a priority queue which contains next nodes to visit
    priority_queue<Vertex*, vector<Vertex*>, VertexPtrCmp> pq;
    pq.push(start);

    vector<Vertex*> visited;
    visited.push_back(start);

    while (!pq.empty()) {
        Vertex* curr = pq.top();
        pq.pop();
        curr->done = true;  // mark a current node done
        // when reaching the destination node
        if (curr == dest) {
            break;
        } else {  // otherwise push neighbor nodes
            for (Edge* edge : curr->outEdges) {
                Vertex* neighbor = edge->target;
                // when a new weight is smaller, update a node and push it
                if (!(neighbor->done) &&
                    curr->distance + edge->weight < neighbor->distance) {
                    // updates a node's distance
                    neighbor->distance = curr->distance + edge->weight;
                    // updates a node's previous node
                    neighbor->previous = curr;
                    // push a node to a priority queue and a visited vector
                    pq.push(neighbor);
                    visited.push_back(neighbor);
                }
            }
        }
    }

    // when there's no such path
    if (dest->previous == nullptr) {
        return;
    }

    // back trace the shortest path
    backtraceThePath(dest, &shortestPath);

    // reset visited nodes' status
    for (Vertex* node : visited) {
        node->distance = INFINITY;
        node->previous = nullptr;
        node->done = false;
    }
}

/**
 * A helper function for Dijkstra's algorithm which push vertices in the
 * shortest path to a result vector.
 *
 * @param Vertex*: a current node
 * @param vector<Vertex*>*: a vector which contains vertices in the shortest
 * path
 */
void Map::backtraceThePath(Vertex* node, vector<Vertex*>* path) {
    // base case: a given node is nullptr
    if (node == nullptr) {
        return;
    }
    // recursive phase
    backtraceThePath(node->previous, path);

    path->push_back(node);
}

/**
 * calculates a minimum spanning tree of this map. edges included in this
 * spanning tree are pushed in a given vector
 *
 * @param vector<Edge*>: a vector which is pushed edges in a spanning tree
 */
void Map::findMST(vector<Edge*>& MST) {
    // initializes a priority queue
    priority_queue<Edge*, vector<Edge*>, EdgePtrCmp> pq;
    for (Edge* edge : undirectedEdges) {
        pq.push(edge);
    }

    int numEdges = 0;

    while (!pq.empty() && numEdges < vertices.size() - 1) {
        Edge* currEdge = pq.top();
        pq.pop();

        if (unionVerts(currEdge->source, currEdge->target)) {
            MST.push_back(currEdge);
            numEdges++;
        }
    }

    // reset parents status
    for (Vertex* v : vertices) {
        v->parent = nullptr;
    }
}

/**
 * a function which calculates bridges in a graph
 *
 * @param vector<Edge*>: a vector containing edges which is bridges
 */
void Map::crucialRoads(vector<Edge*>& roads) {
    // invalid case: a map contains no node
    if (vertices.size() == 0) {
        return;
    }

    int time = 0;
    vector<Edge*>* vecPtr = &roads;
    crucialRoadsHelper(vertices[0], vecPtr, time);

    // reset a parent status
    for (Vertex* v : vertices) {
        v->discoveryTime = -1;
        v->low = -1;
        v->parent = nullptr;
    }
}

/**
 * A helper function which calculates bridges
 * (reference: https://www.geeksforgeeks.org/bridge-in-a-graph/)
 *
 * @param Vertex*: a current node
 * @param vector<Edge*>*: a vector containing bridges
 * @param int: time of traversal
 */
void Map::crucialRoadsHelper(Vertex* node, vector<Edge*>*& roads, int time) {
    // set the time of discovery and low of a current node
    node->discoveryTime = node->low = ++time;

    for (Edge* edge : node->outEdges) {
        Vertex* neighbor = edge->target;

        // when a neighbor node is not yet visited
        if (neighbor->discoveryTime == -1) {
            neighbor->parent = node;
            // recursive call
            crucialRoadsHelper(neighbor, roads, time);

            node->low = min(node->low, neighbor->low);

            if (neighbor->low > node->discoveryTime) {
                roads->push_back(edge);
            }
        }
        // when a neighbor is not a current node's parent
        else if (neighbor != node->parent) {
            node->low = min(node->low, neighbor->discoveryTime);
        }
    }
}

/* Destructor of Map graph */
Map::~Map() {
    for (Vertex* v : vertices) {
        for (Edge* e : v->outEdges) {
            delete e;
        }
        delete (v);
    }
    for (Edge* e : undirectedEdges) {
        delete (e);
    }
}

/**
 * A function which implements find method of disjoint set. Returns a
 * representation vertex of a set which a given vertex belongs to
 *
 * @param Vertex*: a vertex
 */
Vertex* Map::find(Vertex* vertex) {
    // holds vertices so as to reset their parents status later
    vector<Vertex*> children;

    while (vertex->parent != nullptr) {
        children.push_back(vertex);
        vertex = vertex->parent;
    }

    // compress a path
    for (Vertex* v : children) {
        v->parent = vertex;
    }

    return vertex;
}

/**
 * A function which implements union method of disjoint set. Returns true if
 * given two vertices belong to the same set
 *
 * @param Vertex*: first vertex
 * @param Vertex*: second vertex
 */
bool Map::unionVerts(Vertex* v1, Vertex* v2) {
    // invalid case: a given pointer is nullptr
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    Vertex* v1Parent = find(v1);
    Vertex* v2Parent = find(v2);
    if (v1Parent != v2Parent) {
        v2Parent->parent = v1Parent;
        return true;
    }

    return false;
}