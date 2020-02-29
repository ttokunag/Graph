#include <gtest/gtest.h>
#include <iostream>
#include "ActorGraph.hpp"
#include "ActorNode.hpp"

using namespace std;
using namespace testing;

// TODO: add tests for actor graph
TEST(ActorTest, ACTOR_NODE_TEST) {
    ActorNode actor1("a");
    ActorNode actor2("b");
    actor1.buildEdge("movie1", 2020, &actor2);

    ASSERT_EQ("a", actor1.getName());
    ASSERT_EQ("b", actor2.getName());
}

TEST(ActorTest, ACTOR_GRAPH_TEST) {
    ActorGraph graph;

    graph.addActor("actor1", "movie1", 2000);
    graph.addActor("actor1", "movie1", 2002);
    graph.addActor("actor2", "movie1", 2000);
    graph.addActor("actor3", "movie1", 2002);
    graph.buildConnection();

    for (pair<string, ActorNode*> actor : graph.actors) {
        for (MovieEdge* m : actor.second->movies) {
            cout << actor.first << ": " << m->getName() << " " << m->getYear()
                 << endl;
        }
    }
    cout << '\n';

    for (pair<string, vector<ActorNode*>> movie : graph.movies) {
        cout << movie.first << ": " << endl;
        for (ActorNode* actor : movie.second) {
            cout << actor->getName() << " " << endl;
        }
    }
    cout << '\n';

    for (pair<string, ActorNode*> actor : graph.actors) {
        cout << actor.first << endl;
        for (pair<string, MovieEdge*> n : actor.second->getNeighbors()) {
            cout << n.first << ": " << n.second->getName() << ", "
                 << n.second->getYear() << endl;
        }
    }

    ASSERT_EQ("actor1", graph.actors.at("actor1")->getName());
}