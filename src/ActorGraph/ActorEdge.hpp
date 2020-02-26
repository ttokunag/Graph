#ifndef ACTOREDGE_HPP
#define ACTOREDGE_HPP

#include <string>
#include "ActorNode.hpp"

using namespace std;

class ActorEdge {
  private:
    string movieName;
    ActorNode* actor1;
    ActorNode* actor2;

  public:
    ActorEdge();

    bool containsActor(ActorNode* actor);

    string getMovieName();
};

#endif