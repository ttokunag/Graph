/**
 * TODO: add file header
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include "ActorNode.hpp"

using namespace std;

/**
 * TODO: add class header
 */
class ActorGraph {
  protected:
    // TODO: add data structures used in actor graph
    // unordered_map<string, ActorNode*> actors;

  public:
    /* a map contains
     * KEY: a string name of an actor
     * VAL: a corresponding node
     */
    unordered_map<string, ActorNode*> actors;
    /* a map contains
     * KEY: a string name of a movie
     * VAL: a vector of actors of the movie
     */
    unordered_map<string, vector<ActorNode*>*> movies;

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

    void addActor(string name, string movieName, int movieYear);

    void buildConnection();
};

#endif  // ACTORGRAPH_HPP
