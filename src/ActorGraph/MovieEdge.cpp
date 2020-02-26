#include "MovieEdge.hpp"

using namespace std;

string MovieEdge::getName() { return name; };

int MovieEdge::getYear() { return year; };

bool MovieEdge::equals(MovieEdge movie) {
    return name.compare(movie.getName()) == 0 && year == movie.getYear();
};