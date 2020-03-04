#include "ActorNode.hpp"

using namespace std;

void ActorNode::buildEdge(string movieName, int movieYear, ActorNode* actor) {
    MovieEdge movie(movieName, movieYear);
    neighbors.insert(pair<string, MovieEdge>(actor->getName(), movie));
}

string ActorNode::getName() { return name; }

ActorNode::~ActorNode() {
    delete prevNode;
    neighbors.clear();
}