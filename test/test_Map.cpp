#include <gtest/gtest.h>
#include "Map.hpp"

using namespace std;
using namespace testing;

// TODO: add tests for map graph
TEST(MapTest, DIJKSTRA_TEST) {
    Map* map = new Map();
    string vertexFile = "../src/map1xy.txt";
    string edgeFile = "../src/map1roads.txt";
    map->buildMapFromFile(vertexFile, edgeFile);

    vector<Vertex*> shortestPath;
    map->Dijkstra("Warren", "Revelle", shortestPath);

    delete map;
}