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

int *visit;
class grafo{
    private:
        pvertice pGrafo;
        int numVertices;
    public:
        grafo();
        ~grafo();
        void insertarVertice(int x);
        void insertarArista(int x, int y);
        void mostrarGrafo();
        pvertice getPgrafo();
        int getNumVertices();
        bool dfsCircuito(int x, int y);
        bool existeCircuito();
        
};

grafo::grafo(){
    pGrafo = NULL;
    numVertices = 0;
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
    numVertices++;
}

void grafo::insertarArista(int x, int y){
    pvertice p;
    parista a1,a2;
    p = pGrafo;
    if(p!=NULL){
        while(p!=NULL && p->datoOrigen!=x){
            p = p->sgteVertice;
        }
        if(p!=NULL){
            a1 = new arista;
            a1->datoDestino = y;
            a1->sgteArista = p->adyacente;
            p->adyacente = a1;
        }
    }
    p = pGrafo;
    if(p!=NULL){
        while(p!=NULL && p->datoOrigen!=y){
            p = p->sgteVertice;
        }
        if(p!=NULL){
            a2 = new arista;
            a2->datoDestino = x;
            a2->sgteArista = p->adyacente;
            p->adyacente = a2;
        }
    }
}

pvertice grafo::getPgrafo(){
    return pGrafo;
}

int grafo::getNumVertices(){
    return numVertices;
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
            cout << " a->sgteArista: " << a;
        }
        cout << endl;
        p = p->sgteVertice;
    }
}


// dfs
int *pre;
int cont;

void dfs(grafo G, int v){
    pre[v] = cont++;
    pvertice p;
    parista w;
    p = G.getPgrafo();
    while(p!=NULL){
        if(p->datoOrigen == v){
            w = p->adyacente;
            while(w != NULL){
                if(pre[w->datoDestino] == -1){
                    dfs(G, w->datoDestino);
                }
                w = w->sgteArista;
            }
        }
        p = p->sgteVertice;
    }
}

void algBusqueda(grafo G){
    int n = G.getNumVertices();
    cont = 0;
    pre = new int[n];
    for (int v = 0; v < n; v++){
        pre[v] = -1;
    }
    for (int v = 0; v < n; v++){
        if(pre[v] == -1){
            dfs(G, v);
        }
    }
}

// Busqueda de circuito


bool grafo::dfsCircuito(int v, int padrev){
    visit[v] = 1;
    pvertice p;
    parista a;
    p = pGrafo;
    while(p!=NULL){
        if(p->datoOrigen == v){
            a = p->adyacente;
            while(a != NULL){
                if(visit[a->datoDestino] == -1){
                    if(dfsCircuito(a->datoDestino, v) == 1){
                        return 1;
                    }
                }
                else if(a->datoDestino != padrev){
                    return 1;
                }
                a = a->sgteArista;  
            }
        }
        p = p->sgteVertice;
    }
    return 0;
}

bool grafo::existeCircuito(){
    int n = numVertices;
    visit = new int[numVertices];
    for (int v = 0; v < numVertices; v++){
        visit[v] = -1;
    }
    for (int v = 0; v < numVertices; v++){
        if(visit[v] == -1){
            if(dfsCircuito(v, v) == 1){
                return 1;
            }
        }
    }
    return 0;
}



//MAIN
int main(){
    grafo G;
    G.insertarVertice(0);
    G.insertarVertice(1);
    G.insertarVertice(2);
    G.insertarVertice(3);
    G.insertarVertice(4);
    G.insertarVertice(5);
    G.insertarArista(0, 1);
    G.insertarArista(0, 2);
    G.insertarArista(1, 4);
    G.insertarArista(1, 3);
    G.insertarArista(5, 4);
    //G.insertarArista(3, 4);
    G.mostrarGrafo();
    if(G.existeCircuito() == 1){
        cout << "Existe circuito" << endl;
    }
    else{
        cout << "No existe circuito" << endl;
    }
    return 0;
}

