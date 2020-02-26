#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <string>
#include <unordered_map>
#include "MovieEdge.hpp"

using namespace std;

class ActorNode {
  private:
    string name;
    unordered_map<string, MovieEdge*> neighbors;

  public:
    ActorNode(string name) : name(name), neighbors(){};

    void buildEdge(string movieName, int movieYear, ActorNode* actor);

    string getName();

    unordered_map<string, MovieEdge*> getNeighbors();
};

#endif