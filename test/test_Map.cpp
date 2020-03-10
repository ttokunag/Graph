/**
 * This file test Map class
 */

#include <gtest/gtest.h>
#include "Map.hpp"

using namespace std;
using namespace testing;

TEST(MapTest, DIJKSTRA_TEST) {
    Map* map = new Map();
    string vertexFile = "../src/map1xy.txt";
    string edgeFile = "../src/map1roads.txt";
    map->buildMapFromFile(vertexFile, edgeFile);

    vector<Vertex*> shortestPath;
    map->Dijkstra("Warren", "Revelle", shortestPath);

    delete map;
}

TEST(MapTest, KRUSKAL_TEST) {
    Map* map = new Map();
    string vertexFile = "../src/map1xy.txt";
    string edgeFile = "../src/map1roads.txt";
    map->buildMapFromFile(vertexFile, edgeFile);

    vector<Edge*> MSTEdges;
    map->findMST(MSTEdges);

    delete map;
}

TEST(MapTest, CRUCIAL_ROADS_TEST) {
    Map* map = new Map();
    string vertexFile = "../src/map1xy.txt";
    string edgeFile = "../src/map1roads.txt";
    map->buildMapFromFile(vertexFile, edgeFile);

    vector<Edge*> crucialRoads;
    map->crucialRoads(crucialRoads);

    delete map;
}