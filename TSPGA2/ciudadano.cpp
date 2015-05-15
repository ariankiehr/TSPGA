#include "ciudadano.hpp"
#include<algorithm>


Ciudadano::Ciudadano(string ID){
    this->ID = ID;
}

Ciudadano::Ciudadano(vector<char> genotipo, int salida) {

    int num_random;
    char extremos = genotipo[salida];

    genotipo.erase(genotipo.begin()+salida);

    ID.push_back( extremos );

    while(!genotipo.empty()) {
        num_random = rand() % genotipo.size();
        ID.push_back( genotipo[num_random] );
        genotipo.erase(genotipo.begin()+num_random);
    }

    ID.push_back( extremos );
}


Ciudadano::~Ciudadano(){}

int Ciudadano::getFitness(){
    return fitness;
}

string Ciudadano::getID(){
    return ID;
}

void Ciudadano::setFitness(int fitness){
    this->fitness = fitness;
}

void Ciudadano::setID(string ID){
    this->ID.clear();
    this->ID = ID;
}

unsigned int Ciudadano::getSize() {
    return ID.size();
}

void Ciudadano::mutar() {

    unsigned int l1, l2;
    l1 = rand() % getSize()+1;
    l2 = rand() % getSize()+1;

    unsigned int mi = min(l1,l2) , ma = max(l1,l2);

    string mutacion = getID().substr(0, mi);
    string invert = getID().substr(mi,ma-mi);
    reverse( invert.begin(), invert.end());
    mutacion.append(invert);
    mutacion.append(getID().substr(ma, getID().size()-ma));
    setID(mutacion);

}


void Ciudadano::fixID(char s) {
    string temp;
    ID.erase(ID.find(s),1);
    temp.push_back(s);
    temp.append(ID);
    temp.push_back(s);
    ID = temp;

}
