/**
 * TODO: add file header
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

/* TODO */
ActorGraph::ActorGraph() : actors() {}

/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 */
bool ActorGraph::buildGraphFromFile(const char* filename) {
    ifstream infile(filename);
    bool readHeader = false;

    while (infile) {
        string s;
        if (!getline(infile, s)) break;

        // skip the header of the file
        if (!readHeader) {
            readHeader = true;
            continue;
        }

        // read each line of the dataset to get the movie actor relation
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        // if format is wrong, skip current line
        if (record.size() != 3) {
            continue;
        }

        // extract the information
        string actor(record[0]);
        string title(record[1]);
        int year = stoi(record[2]);

        // TODO: we have an actor/movie relationship to build the graph
        addActor(actor, title, year);
    }

    // if failed to read the file, clear the graph and return
    if (!infile.eof()) {
        cerr << "Failed to read " << filename << endl;
        return false;
    }
    infile.close();

    return true;
}

/* TODO */
void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {
    // Invalid Input: a graph doesn't contains either given actors
    if (actors.count(fromActor) == 0 || actors.count(toActor) == 0) {
        return;
    }

    ActorNode* startActor = actors.at(fromActor);
    startActor->distanceFromRoot = 0;  // mark it visited

    ActorNode* destination = nullptr;

    queue<ActorNode*> q;
    q.push(startActor);  // push a start actor & modifies a shortestPath string
    queue<ActorNode*> visited;
    visited.push(startActor);

    // begins BFS
    while (!q.empty()) {
        ActorNode* curr = q.front();
        q.pop();
        if (curr->getName().compare(toActor) == 0) {  // reached a destination
            destination = curr;
            break;
        }
        // visit a current node neighbors
        for (pair<string, MovieEdge> neighborPair : curr->neighbors) {
            ActorNode* neighbor = actors.at(neighborPair.first);
            // checks if a neighbor is visited yet
            if (neighbor->distanceFromRoot == -1) {
                neighbor->distanceFromRoot = curr->distanceFromRoot + 1;
                neighbor->prevNode = curr;
                q.push(neighbor);
                visited.push(neighbor);
            }
        }
    }

    string to;
    string edge;
    MovieEdge* movieInfo;
    // trace back a generated shortest path
    if (destination != nullptr) {
        while (destination != nullptr) {
            to = "(" + destination->getName() + ")";
            edge = "";

            // unless a node isn't a root, create an edge string
            if (destination->prevNode != nullptr) {
                // retrieve movie info between two actors
                movieInfo = &destination->prevNode->neighbors.at(
                    destination->getName());

                edge = "--[" + movieInfo->getName() + "#@" +
                       to_string(movieInfo->getYear()) + "]-->";
            }

            shortestPath = edge + to + shortestPath;
            destination = destination->prevNode;
        }
    }

    ActorNode* curr;
    while (!visited.empty()) {
        curr = visited.front();
        curr->prevNode = nullptr;
        curr->distanceFromRoot = -1;
        visited.pop();
    }

    return;
}

/* TODO */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {}

void ActorGraph::addActor(string name, string title, int year) {
    ActorNode* currActor;

    // when an actor is not included in a graph
    if (actors.count(name) > 0) {
        currActor = actors.at(name);
    } else {
        currActor = new ActorNode(name);
        actors.insert(pair<string, ActorNode*>(name, currActor));
    }

    // add an actor to a movie actor list
    string movieKey = title + to_string(year);

    vector<ActorNode*>* movieActors;
    // when a movie is included in a graph already
    if (movies.count(movieKey) > 0) {
        movieActors = movies.at(movieKey);
    } else {
        movieActors = new vector<ActorNode*>();
    }

    // add a current actor to a vector
    movieActors->push_back(currActor);
    // when a graph contains a given movie title
    if (movies.count(movieKey) == 0) {
        movies.insert(pair<string, vector<ActorNode*>*>(movieKey, movieActors));
    }
}

void ActorGraph::buildConnection() {
    // exhaustive search for actor pairs by movies
    for (pair<string, vector<ActorNode*>*> movie : movies) {
        // a vector of actors appear in the movie
        vector<ActorNode*>* movieActors = movie.second;
        // build connections for each pair of actors
        for (int i = 0; i < movieActors->size() - 1; i++) {
            for (int j = i + 1; j < movieActors->size(); j++) {
                ActorNode* actor1 = movieActors->at(i);
                ActorNode* actor2 = movieActors->at(j);
                string title = movie.first.substr(0, movie.first.size() - 4);
                int year = stoi(movie.first.substr(movie.first.size() - 4, 4));

                actor1->buildEdge(title, year, actor2);
                actor2->buildEdge(title, year, actor1);
            }
        }
    }
}

/* TODO */
ActorGraph::~ActorGraph() {
    for (pair<string, ActorNode*> actor : actors) {
        delete actor.second;
    }
    actors.clear();

    for (pair<string, vector<ActorNode*>*> movie : movies) {
        delete movie.second;
    }
    movies.clear();
}
