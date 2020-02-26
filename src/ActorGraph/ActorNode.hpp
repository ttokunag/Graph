#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <string>
#include <vector>
#include "ActorEdge.hpp"

using namespace std;

class ActorNode {
  private:
    string name;
    vector<ActorEdge*> acquaintances;

  public:
    ActorNode();

    void buildEdge(string movieName, ActorNode* actor);

    string getName();

    vector<ActorEdge*> getAcqs();
};

#endif