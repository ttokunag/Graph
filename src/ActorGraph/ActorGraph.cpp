/**
 * TODO: add file header
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
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

        cout << actor << endl;

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
                     string& shortestPath) {}

/* TODO */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {}

void ActorGraph::addActor(string name, string title, int year) {
    ActorNode* actorNode;

    // create a new node OR retrieve an existent one
    if (actors.count(name) > 0) {
        actorNode = actors.at(name);
    } else {
        actorNode = new ActorNode(name);
        actors.insert(pair<string, ActorNode*>(name, actorNode));
    }
    // add a movie
    actorNode->addMovie(title, year);

    // add an actor to a movie actor list
    string movieKey = title + to_string(year);
    vector<ActorNode*>* movieActors;
    if (movies.count(movieKey) > 0) {
        movieActors = &(movies.at(movieKey));
        movieActors->push_back(actorNode);
    } else {
        movieActors = new vector<ActorNode*>();
        movieActors->push_back(actorNode);
        movies.insert(pair<string, vector<ActorNode*>>(movieKey, *movieActors));
    }

    // movieActors->push_back(actorNode);
}

void ActorGraph::buildConnection() {
    for (pair<string, vector<ActorNode*>> movie : movies) {
        vector<ActorNode*> movieActors = movie.second;
        for (int i = 0; i < movieActors.size() - 1; i++) {
            for (int j = i + 1; j < movieActors.size(); j++) {
                ActorNode* actor1 = movieActors[i];
                ActorNode* actor2 = movieActors[j];
                string title = movie.first.substr(0, movie.first.size() - 4);
                int year = stoi(movie.first.substr(movie.first.size() - 4, 4));

                actor1->buildEdge(title, year, actor2);
                actor2->buildEdge(title, year, actor1);
            }
        }
    }
}

/* TODO */
ActorGraph::~ActorGraph() {}
