#include <iostream>
using namespace std;
void algBusqueda(grafo);

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
        void insertarVertice(int);
        void insertarArista(int, int);
        void imprimirGrafo();
        int numVertices();
        pvertice getPgrafo();
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
    if(p!=NULL){
        while(p->datoOrigen != x && p!= NULL)
            p = p->sgteVertice;
        if(p!=NULL){
            a = new arista;
            a->datoDestino = y;
            a->sgteArista = p->adyacente;
            p->adyacente = a;
            
        }
    }
    p = pGrafo;
    if(p!=NULL){
        while(p->datoOrigen != y && p!= NULL)
            p = p->sgteVertice;
        if(p!=NULL){
            a = new arista;
            a->datoDestino = x;
            a->sgteArista = p->adyacente;
            p->adyacente = a;
            
        }
    }
}

void grafo::imprimirGrafo(){
    pvertice p;
    parista a;
    p = pGrafo;
    if (p==NULL) cout << "Grafo vacio" << endl;
    else
        while(p!=NULL){
            cout << p->datoOrigen;
            a = p->adyacente;
            while(a!=NULL){
                cout << "\t" << a->datoDestino;
                a = a->sgteArista;
            }
            cout << endl;
            p = p->sgteVertice;
        }
}

int grafo::numVertices(){
    pvertice p;
    int cont = 0;
    p = pGrafo;
    while(p!=NULL){
        cont++;
        p = p->sgteVertice;
    }
    return cont;
}

pvertice grafo::getPgrafo(){
    return pGrafo;
}

int *pre;
int cont;

void algBusqueda(grafo g){
    cont = 0;
    int n = g.numVertices();
    pre = new int[n];
    int v = 0;
    for (v =  0; v < n; v++){
        pre[v] = -1;
    }
    for (v = 0; v < n; v++){
        if (pre[v] == -1)
            dfs(g, v);
    }
}

void dfs(grafo g, int v){
    pre[v] = cont++;
    pvertice p;
    parista a;
    p = g.getPgrafo();
    if (p==NULL) cout << "Grafo vacio" << endl;
    else
        while(p!=NULL){
            if (p->datoOrigen == v){
                a = p->adyacente;
                while(a!=NULL){
                    if (pre[a->datoDestino] == -1)
                        dfs(g, a->datoDestino);
                    a = a->sgteArista;
                }
            }
            p = p->sgteVertice;
        } 
    

}

int main(){
    grafo g;
    int x,y;
    g.insertarVertice(4);
    g.insertarVertice(6);
    g.insertarVertice(3);
    g.insertarArista(4,6);
    g.insertarArista(3,6);
    g.insertarArista(3,4);
    cout << "Vert || Aristas" << endl;
    g.imprimirGrafo();
 
    return 0;
}