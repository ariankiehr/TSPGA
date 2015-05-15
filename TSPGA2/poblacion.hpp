#ifndef POBLACION_H
#define POBLACION_H
#include "ciudadano.hpp"
#include "fitness.hpp"
#include <algorithm>
#define INDICEMUTACION 25
#define MINSELECCION 10
#define MAXSELECCION 50

class Poblacion {
public:
    Poblacion(vector<pair<int, int> >, vector<char>, int , int );
    ~Poblacion();
    void puntuarYOrdenar();
    string getMejorID();
    int getMejorFitness();
    void recombinar();


private:

    void elitismo(vector<Ciudadano>&);
    string mezclar();

    vector<Ciudadano> ciudadanos;
    Fitness fit;
    int recombinaciones;

    struct s {
        bool operator() (Ciudadano i,Ciudadano j) {
            return (i.getFitness() < j.getFitness());
        }
    } comparador;
};



#endif
