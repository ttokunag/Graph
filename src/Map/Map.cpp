
#include <queue>
#include "Map.hpp"

/* TODO */
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

void Map::backtraceThePath(Vertex* node, vector<Vertex*>* path) {
    // base case: a given node is nullptr
    if (node == nullptr) {
        return;
    }
    // recursive phase
    backtraceThePath(node->previous, path);

    path->push_back(node);
}

/* TODO */
void Map::findMST(vector<Edge*>& MST) {}

/* TODO */
void Map::crucialRoads(vector<Edge*>& roads) {}

/* Destructor of Map graph */
Map::~Map() {
    for (Vertex* v : vertices) {
        for (Edge* e : v->outEdges) {
            delete e;
        }
        delete v;
    }
    for (Edge* e : undirectedEdges) {
        delete e;
    }
}

class DisjointSet {
  public:
    Vertex* find(Vertex* vertex) {
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

    bool unionVerts(Vertex* v1, Vertex* v2) {
        if (v1 == nullptr || v2 == nullptr) {
            return false;
        }

        Vertex* v1Parent = find(v1);
        Vertex* v2Parent = find(v2);
        if (v1Parent != v2Parent) {
            v2Parent->parent = v1Parent;
        }

        return true;
    }
};