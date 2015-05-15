#include "ciudadano.hpp"
#include "fitness.hpp"
#include "poblacion.hpp"
#include<vector>

#define MAXCIUDADES 89
#define MINCIUDADES 3
#define SALIDA 0
#define POBLACION 2000
#define REPETFITNESS 5

using namespace std;

char genotipo[MAXCIUDADES] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T',
                              'U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n',
                              'o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7',
                              '8','9','!','"','#','$','%','&','(',')','*','?','@','|','¬','=','+','[',']','{',
                              '}','-','_',':',';','.',',','º','ª'};



int main(){
    srand( time(NULL) ) ;

    unsigned int numeroCiudades;
    vector<pair<int, int> > coor;

    do {
        cin >> numeroCiudades;
    } while (numeroCiudades > MAXCIUDADES && numeroCiudades < MINCIUDADES);

    int a,b;
    for( unsigned int i=0; i<numeroCiudades; i++ ) {
        cin>>a; cin>>b;
        coor.push_back( make_pair( a, b ) );
    }

    vector<char> gen ( genotipo, genotipo + numeroCiudades / sizeof(char) );

    Poblacion p(coor, gen, SALIDA, POBLACION);

    int fitnessAnt = 0, repet = 0;

    while(repet < numeroCiudades/REPETFITNESS) {

        p.puntuarYOrdenar();
        (fitnessAnt == p.getMejorFitness() ) ? repet++ : repet=0;
        fitnessAnt = p.getMejorFitness();
        p.recombinar();
    }

    p.puntuarYOrdenar();

    cout << p.getMejorID()<<" - "<<p.getMejorFitness()<<endl;

	return 0;
}















