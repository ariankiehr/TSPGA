#include "fitness.hpp"


Fitness::Fitness() {
}

void Fitness::setFitness(vector<pair<int,int> > coor, vector<char> genotipo) {
    coordenadas = coor;
    this->genotipo = genotipo;
}

Fitness::~Fitness(){
    coordenadas.clear();
    genotipo.clear();
}

int Fitness::calculateFitness(Ciudadano c) {
	double valor = 0; int a,b;
	for(unsigned int i=1; i<c.getSize(); i++) {

        a = getPos(c.getID().at(i));
        b = getPos(c.getID().at(i-1));

		valor += round(
                    sqrt(
                        pow( (coordenadas[a].first - coordenadas[b].first) ,2) +
                        pow( (coordenadas[a].second - coordenadas[b].second) ,2)
                    )
                 );
	}
	return valor;
}

int Fitness::getPos(char ciudad) {
    for(unsigned int i=0; i<genotipo.size(); i++) {
        if( genotipo[i] == ciudad )
            return i;
    }
    return 0;
}

