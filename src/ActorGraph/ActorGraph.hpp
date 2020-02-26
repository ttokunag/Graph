/**
 * TODO: add file header
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <vector>
#include "ActorNode.hpp"

using namespace std;

/**
 * TODO: add class header
 */
class ActorGraph {
  protected:
    // TODO: add data structures used in actor graph
    vector<ActorNode*> actors;

  public:
    /* TODO */
    ActorGraph();

    /* TODO */
    bool buildGraphFromFile(const char* filename);

    /* TODO */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

    /* TODO */
    void predictLink(const string& queryActor, vector<string>& predictionNames,
                     unsigned int numPrediction);

    /* TODO */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
