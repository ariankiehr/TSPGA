#ifndef FITNESS_H
#define FITNESS_H
#include<vector>
#include "ciudadano.hpp"
#include<math.h>

using namespace std;

class Fitness {
public:
    Fitness();
    ~Fitness();
    int calculateFitness(Ciudadano);
    void setFitness(vector<pair<int, int> >, vector<char>);

private:
    int getPos(char);
    vector<pair<int, int> > coordenadas;
    vector<char> genotipo;
};


#endif
