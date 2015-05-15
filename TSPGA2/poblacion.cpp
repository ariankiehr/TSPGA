#include "poblacion.hpp"

Poblacion::Poblacion(vector<pair<int, int> > coor, vector<char> genotipo, int salida, int cantidad) {
    fit.setFitness(coor, genotipo);
    for(int i=0; i<cantidad; i++)
        ciudadanos.push_back( Ciudadano(genotipo,salida) );
    recombinaciones = 0;
}

Poblacion::~Poblacion(){
    ciudadanos.clear();
}


void Poblacion::puntuarYOrdenar(){
    for(unsigned int i=0; i<ciudadanos.size(); i++)
        ciudadanos[i].setFitness( fit.calculateFitness(ciudadanos[i]) );
    sort(ciudadanos.begin(), ciudadanos.end(), comparador);

}


void Poblacion::elitismo(vector<Ciudadano>& nuevosCiudadanos) {
    nuevosCiudadanos.assign( ciudadanos.begin(), ciudadanos.begin() + ciudadanos.size()/MINSELECCION );
}

void Poblacion::recombinar() {
    recombinaciones++;
    vector<Ciudadano> nuevosCiudadanos;
    elitismo(nuevosCiudadanos);

    for(unsigned int i=0; i< ciudadanos.size()-(ciudadanos.size()/MINSELECCION) ; i++) {

        string nuevoCiudadano = mezclar();

        Ciudadano c(nuevoCiudadano);

        if(rand()%100 < INDICEMUTACION) c.mutar();

        c.fixID( ciudadanos[0].getID().at(0) );

        nuevosCiudadanos.push_back(c);
    }

    ciudadanos = nuevosCiudadanos;

}


string Poblacion::getMejorID() {
    return ciudadanos[0].getID();
}


int Poblacion::getMejorFitness() {
    return ciudadanos[0].getFitness();
}

string Poblacion::mezclar() {
    int c1, c2; // dos ciudadanos de la mejor mitad
    int l1,l2; // dos ciudades aleatorias de cada ciudadano
    bool f1, f2; //indican las ciudades no repetidas hasta el momentos
    string nc; //nuevo ciudadano

    //en la primer recombinacion se seleccione solo el 11% de los individuos
    //numero que crece en uno con una cota de 50%
    int seleccion = (recombinaciones<MAXSELECCION-MINSELECCION)?MINSELECCION+recombinaciones:MAXSELECCION;
    c1 = rand() % (ciudadanos.size()/ seleccion);
    c2 = rand() % (ciudadanos.size()/ seleccion);
    l1 = rand() % ciudadanos[0].getSize(); //una ciudad aleatoria
    //se busca la misma ciudad en el otro ciudadano
    size_t found = ciudadanos[c2].getID().find( ciudadanos[c1].getID().at(l1) );
    l2 = int(found);
    //se coloca esa ciudad como solucion del nuevo ciudadano
    nc.push_back( ciudadanos[c1].getID().at(l1) );
    f1 = f2 = true;

    do {
        l1--; l2++;
        if( l1<0 || l2>ciudadanos[c1].getSize()-2) break;

        if(f1) {
            if(nc.find( ciudadanos[c1].getID().at(l1) ) == string::npos)
                nc.insert( 0, 1, ciudadanos[c1].getID().at(l1) );
            else
                f1=false;
        }
        if(f2) {
            if(nc.find( ciudadanos[c2].getID().at(l2) ) == string::npos)
                nc.push_back( ciudadanos[c2].getID().at(l2) );
            else
                f2=false;
        }

    } while( f1 || f2 );

    //los caracteres restantes se colocan de forma aleatoria
    if( nc.size() < ciudadanos[c1].getSize() )
        for(unsigned int i=0; i<ciudadanos[c1].getSize(); i++ )
            if( nc.find( ciudadanos[c1].getID().at(i) ) == string::npos )
                nc.push_back( ciudadanos[c1].getID().at(i) );

    return nc;
}


