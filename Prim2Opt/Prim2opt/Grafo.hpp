#ifndef GRAFO_H
#define GRAFO_H

#include <list>
#include <iostream>
#include <cassert>

using namespace std;

template <typename Costo> class Grafo {
    public:

    Grafo();
    ~Grafo();

    void agregarVertice(int);
    void agregarArco(int origen, int destino, Costo costo);
    void agregarArcoNoDireccional(int origen, int destino, Costo costo);

    void eliminarVertice(int);
    void eliminarArco(int origen, int destino);
    void vaciar();
    void mostrarGrafo();

    int getLongitud(); //Devuelve el numero de vertices
    const Costo & getCosto(int origen, int destino);
    void getVertices(list<int>& vertices);
    void getAdyacentes(int vertice, list<int>& adyacentes);

    bool esVacio();
    bool existeArco(int origen, int destino);
    bool existeVertice(int ver);

    private:

        struct nodoAdyacente {
            Costo costo;
            int verticeId;
        };

        struct nodoVertice {
            int vertice;
            list<nodoAdyacente> adyacentes;
        };

        list<nodoVertice> grafo;

        bool operator =(Grafo<int> &g) {

            if (this == &g)
                return *this;

            vaciar();

            list<int> v;
            g.getVertices(v);
            list<int>::iterator it = v.begin();

            while ( it != v.end()) {
                list<int> ady;
                g.getAdyacentes(*it, ady);
                agregarVertice(*it);
                list<int>::iterator itad = ady.begin();

                while ( itad != ady.end()) {
                    agregarArcoNoDireccional(*it, *itad);
                    itad++;
                }

                it++;
            }
        }

};


template <typename Costo> Grafo<Costo>::Grafo() {

}

template <typename Costo> Grafo<Costo>::~Grafo() {

    vaciar();
}

template <typename Costo> void Grafo<Costo>::vaciar() {

    typename list<nodoVertice>::iterator it;

    for (it = grafo.begin(); it != grafo.end(); it++) {
        it->adyacentes.clear();
    }

    grafo.clear();
}

template <typename Costo> void Grafo<Costo>::agregarVertice(int vert) {
    nodoVertice nuevo;
    nuevo.vertice = vert;
    grafo.push_back(nuevo);
}

template <typename Costo> void Grafo<Costo>::agregarArco(int origen, int destino, Costo costo) {

    if ((!existeVertice(origen)) || (!existeVertice(destino)))
        return;

    nodoAdyacente nuevo;
    nuevo.verticeId = destino;
    nuevo.costo = costo;

    typename list<nodoVertice>::iterator it = grafo.begin();

    while ((it != grafo.end()) && (it->vertice != origen)) {
        it++;
    }

    if (it->vertice == origen) {
        it->adyacentes.push_back(nuevo);
    }
}

template <typename Costo> void Grafo<Costo>::agregarArcoNoDireccional(int origen, int destino, Costo costo) {

    agregarArco(origen, destino, costo);
    agregarArco(destino, origen, costo);
}

template <typename Costo> int Grafo<Costo>::getLongitud() {

    return grafo.size();
}

template <typename Costo> const Costo & Grafo<Costo>::getCosto(int origen, int destino) {

    typename list<nodoVertice>::const_iterator it = grafo.begin();

    while ((it != grafo.end()) && it->vertice != origen) {
        it++;
    }

    typename list<nodoAdyacente>::const_iterator it_ady = it->adyacentes.begin();

    while (it_ady != it->adyacentes.end()) {
        if (it_ady->verticeId == destino) {
            return it_ady->costo;
        }
        it_ady++;
    }

    assert(0);

}

template <typename Costo> void Grafo<Costo>::getVertices(list<int>& vertices) {

    typename list<nodoVertice>::const_iterator it = grafo.begin();

    while (it != grafo.end()) {
        vertices.push_back(it->vertice);
        it++;
    }
}

template <typename Costo> void Grafo<Costo>::getAdyacentes(int vertice, list<int>& adyacentes) {

    typename list<nodoVertice>::const_iterator it = grafo.begin();

    while ((it != grafo.end() && (it->vertice != vertice))) {
        it++;
    }

    typename list<nodoAdyacente>::const_iterator it_ady;

    if (it == grafo.end()) {

        return;
    }

    it_ady = it->adyacentes.begin();
    while (it_ady != it->adyacentes.end()) {
        adyacentes.push_back(it_ady->verticeId);
        it_ady++;
    }

}

template <typename Costo> void Grafo<Costo>::mostrarGrafo() {

    typename list<nodoVertice>::iterator it = grafo.begin();
    typename list<nodoAdyacente>::iterator it_ady;

    while (it != grafo.end()) {
        cout << "Vertice: " << it->vertice << endl;
        it_ady = it->adyacentes.begin();

        while (it_ady != it->adyacentes.end()) {
            cout << "arco con: " << it_ady->verticeId;
            cout << ", costo de: " << it_ady->costo << endl;
            it_ady++;
        }
        cout << endl;
        it++;
    }


}

template <typename Costo> void Grafo<Costo>::eliminarVertice(int vertice) {

    typename list<nodoVertice>::iterator it = grafo.begin();

    while (it != grafo.end()) {
        if (it->vertice == vertice) {
            it = grafo.erase(it);

            return;
        }

        it++;
    }

}

template <typename Costo> void Grafo<Costo>::eliminarArco(int origen, int destino) {

    typename list<nodoVertice>::iterator it = grafo.begin();

    while ((it != grafo.end()) && (it->vertice != origen)) {
        it++;
    }

    if (it == grafo.end()) {

        return;
    }

    typename list<nodoAdyacente>::iterator it_ady = it->adyacentes.begin();

    while (it_ady != it->adyacentes.end()) {
        if (it_ady->verticeId == destino) {
            it_ady = it->adyacentes.erase(it_ady);

            return;
        }

        it_ady++;
    }
}

template <typename Costo> bool Grafo<Costo>::existeVertice(int ver) {

    typename list<nodoVertice>::const_iterator it = grafo.begin();

    while (it != grafo.end()) {

        if (it->vertice == ver) {

            return true;
        }

        it++;
    }

    return false;
}


template <typename Costo> bool Grafo<Costo>::existeArco(int origen, int destino) {

    typename list<nodoVertice>::const_iterator it = grafo.begin();

    while ((it != grafo.end()) && (it->vertice != origen)) {
        it++;
    }

    if (it == grafo.end()) {

        return false;
    }

    typename list<nodoAdyacente>::const_iterator it_ady = it->adyacentes.begin();

    while ((it_ady != it->adyacentes.end())) {
        if (it_ady->verticeId == destino) {

            return true;
        }

        it_ady++;
    }

    return false;

}

template <typename Costo> bool Grafo<Costo>::esVacio() {

    return grafo.empty();
}

#endif
