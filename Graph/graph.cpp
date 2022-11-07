#include <iostream>
using namespace std;

struct arista{
    int datoDestino;
    arista *sgteArista;
};
typedef arista *parista;

struct vertice{
    int datoOrigen;
    arista *adyacente;
    vertice *sgteVertice;
};
typedef vertice *pvertice;

class grafo{
    private:
        pvertice pGrafo;
    public:
        grafo();
        ~grafo();
        void insertarVertice(int x);
        void insertarArista(int x, int y);
        void mostrarGrafo();
};

grafo::grafo(){
    pGrafo = NULL;
}

grafo::~grafo(){
    pvertice p, rp;
    parista r, ra;
    p = pGrafo;
    while(p!=NULL){
        r = p->adyacente;
        while(r!=NULL){
            ra = r;
            r = r->sgteArista;
            delete ra;
        }
        rp = p;
        p = p->sgteVertice;
        delete rp;
    }
}

void grafo::insertarVertice(int x){
    pvertice p;
    p = new vertice;
    p->datoOrigen = x;
    p->adyacente = NULL;
    p->sgteVertice = pGrafo;
    pGrafo = p;
}

void grafo::insertarArista(int x, int y){
    pvertice p;
    parista a;
    p = pGrafo;
    while(p!=NULL){
        if(p->datoOrigen == x){
            a = new arista;
            a->datoDestino = y;
            a->sgteArista = p->adyacente;
            p->adyacente = a;
        }
        p = p->sgteVertice;
    }
    p = pGrafo;
    while(p!=NULL){
        if(p->datoOrigen == y){
            a = new arista;
            a->datoDestino = x;
            a->sgteArista = p->adyacente;
            p->adyacente = a;
        }
        p = p->sgteVertice;
    }
}

void grafo::mostrarGrafo(){
    pvertice p;
    parista a;
    p = pGrafo;
    while(p!=NULL){
        cout << p->datoOrigen << " -> ";
        a = p->adyacente;
        while(a!=NULL){
            cout << a->datoDestino << " ";
            a = a->sgteArista;
        }
        cout << endl;
        p = p->sgteVertice;
    }
}

int main(){
    grafo G;
    G.insertarVertice(1);
    G.insertarVertice(2);
    G.insertarVertice(3);
    G.insertarVertice(4);
    G.insertarArista(1, 2);
    G.insertarArista(1, 3);
    G.insertarArista(2, 3);
    G.insertarArista(2, 4);
    G.mostrarGrafo();
    return 0;
}

