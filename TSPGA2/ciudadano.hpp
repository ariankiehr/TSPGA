#ifndef CIUDADANO_H
#define CIUDADANO_H
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Ciudadano {
public:
    Ciudadano(string);
    Ciudadano(vector<char>, int);
    ~Ciudadano();
    string getID();
    void setID(string);
    int getFitness();
    void setFitness(int);
    unsigned int getSize();
    void mutar();
    void fixID(char);

private:

    string ID;
    int fitness;
};

#endif
