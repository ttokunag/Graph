#ifndef MOVIEEDGE_HPP
#define MOVIEEDGE_HPP

#include <string>

using namespace std;

class MovieEdge {
  private:
    string name;
    int year;

  public:
    MovieEdge(string movieName, int movieYear) {
        name = movieName;
        year = movieYear;
    };

    string getName();

    int getYear();
};

#endif