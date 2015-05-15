#include "Grafo.hpp"
#include <list>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#define INF 99999

using namespace std;

typedef pair<int,int> PII;

void imprimirLista(const list<int> &l) {

    list<int>::const_iterator it = l.begin();
    while ( it != l.end()) {
	cout << *it << " ";
        it++;
    }
}

Grafo<int> generarMST(int raiz[], int costo[], int N, int r) {
    Grafo<int> g;
    for (int i = 1; i < N; i++) {
        g.agregarVertice(i);
    }
    for (int i = 1; i < N; i++) {
        if (i != r)
            g.agregarArcoNoDireccional(i, raiz[i], costo[i]);
    }

    return g;
}


Grafo<int> Prim(Grafo<int> g, int vertice) {
    int N = g.getLongitud()+1;
    int raiz[N];
    int distancia[N];
    int visitado[N];

    for (int i = 0; i < N; i++) {
        distancia[i] = INF;
        raiz[i] = -1;
        visitado[i] = 0;
    }

    priority_queue <PII, vector<PII>, greater<PII> > colap;
    distancia[vertice] = 0;
    colap.push(PII(0,vertice));
    while (!colap.empty()){
        int aux = colap.top().second;
        colap.pop();
        if (visitado[aux] == 1)
            continue;
        visitado[aux] = 1;
        list<int>ady;
        g.getAdyacentes(aux,ady);
        list<int>::iterator it = ady.begin();
        while (it != ady.end()){
            int dist = g.getCosto (aux,*it);//en DIJKSTRA es dist = distancia[*it] + g.costoArco(aux,*it)
            if (dist < distancia[*it] && !visitado[*it]){
                distancia[*it] = dist;
                raiz[*it] = aux;
                colap.push(PII(dist,*it));
            }
            it++;
        }
    }

    Grafo<int> MST = generarMST(raiz, distancia, N, vertice);
    //MST.mostrarGrafo();
    return MST;
}

void preorderTreeWalk(Grafo<int> g, int v, int visitados[], list<int> &S) {
    visitados[v] = 1;
    S.push_back(v);
    list<int> ady;
    g.getAdyacentes(v, ady);
    list<int>::iterator it = ady.begin();

    while(it != ady.end()) {
        if(!visitados[*it]){
            preorderTreeWalk(g, *it, visitados, S);
        }
        it++;
    }
}

int getCostoTour(Grafo<int> g, list<int> L){
    int costoTour = 0;
    list<int>::iterator it = L.begin();
    list<int>::iterator itant = it;
    it++;
    while ( it != L.end()) {
        costoTour+=g.getCosto(*itant, *it);
        itant = it;
        it++;
    }
    return costoTour;
}

void TravelingSalesman(Grafo<int> g, int r) {
    int visitados[g.getLongitud()+1];
    for (int i = 0; i < g.getLongitud()+1; i++)
        visitados[i] = 0;

    Grafo<int> T = Prim(g, r);
    list<int> L;
    preorderTreeWalk(T, r, visitados, L);
    L.push_back(r);
    ///cout<<getCostoTour(g, L)<<endl; //para saber cuanto antes de optimizar

    /// 2opt here
    list<int> listaAux = L;

    int costoInicial = getCostoTour(g, L);
    int aleatorio, aleatorio2;
    int ma, mi;

    for(int i=0; i < g.getLongitud()*200; i++) {


        aleatorio = rand() % listaAux.size();
        if(aleatorio<=0) aleatorio++;
        if(aleatorio>(listaAux.size()-2)) aleatorio--;


        aleatorio2 = rand() % listaAux.size();
        if(aleatorio2<=0) aleatorio2++;
        if(aleatorio2>(listaAux.size()-2)) aleatorio2--;

        list<int>::iterator it = listaAux.begin();
        list<int>::iterator it2 = listaAux.begin();

        ma = max(aleatorio, aleatorio2);
        mi = min(aleatorio, aleatorio2);

        advance(it, mi);
        advance(it2, ma);

        list<int> rev (it, it2);
        rev.reverse();

        list<int> temp (listaAux.begin(), it);
        temp.splice(temp.end(), rev);
        temp.splice(temp.end(), listaAux, it2, listaAux.end());
        listaAux = temp;

        if(getCostoTour(g, listaAux) < costoInicial){
            costoInicial = getCostoTour(g, listaAux);
            L = listaAux;
        } else {
            listaAux = L;
        }
    }



    imprimirLista(L);
    cout<<" - ";
    cout<<getCostoTour(g, L)<<endl;

}



int main() {
    srand(time(NULL));
    Grafo<int> g;

    int numCiudades;
    cin >> numCiudades;

    for(int i=1; i<=numCiudades; i++) {
        g.agregarVertice(i);
    }

    vector<pair<int, int> > coor;

    int a,b;
    for( int i=0; i<numCiudades; i++ ) {
        cin>>a; cin>>b;
        coor.push_back( make_pair( a, b ) );
    }

    for(int i=1; i<=numCiudades; i++) {
        for(int j=1; j<=numCiudades; j++) {
            if(i!=j){
                int valor = round(
                                sqrt(
                                    pow( (coor[i].first - coor[j].first) ,2) +
                                    pow( (coor[i].second - coor[j].second) ,2)
                                )
                             );
                if(!g.existeArco(i,j))
                    g.agregarArcoNoDireccional(i,j, valor);
            }
        }
    }

    //g.mostrarGrafo();

    TravelingSalesman(g, 1);

    return 0;
}
