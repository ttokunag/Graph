#include "ActorNode.hpp"

using namespace std;

void ActorNode::buildEdge(string movieName, int movieYear, ActorNode* actor) {
    MovieEdge* movie = new MovieEdge(movieName, movieYear);
    neighbors.insert(pair<string, MovieEdge*>(actor->getName(), movie));
}

string ActorNode::getName() { return name; }

unordered_map<string, MovieEdge*> ActorNode::getNeighbors() {
    return neighbors;
};