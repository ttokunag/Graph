#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "MovieEdge.hpp"

using namespace std;

class ActorNode {
  private:
    string name;
    // unordered_map<string, MovieEdge*> neighbors;
    // vector<MovieEdge*> movies;

  public:
    // vector<MovieEdge*> movies;
    unordered_map<string, MovieEdge*> neighbors;
    ActorNode* prevNode;
    int distanceFromRoot;

    ActorNode(string name)
        : name(name),
          neighbors(),
          // movies(),
          distanceFromRoot(-1),
          prevNode(nullptr){};

    // void addMovie(string name, int year);

    void buildEdge(string movieName, int movieYear, ActorNode* actor);

    string getName();

    unordered_map<string, MovieEdge*> getNeighbors();
};

#endif