#include <iostream>
using namespace std;
void algBusqueda(grafo);

struct nodo{
    int data;
    nodo *next;
};

class cola{
    private:
        nodo *head;
        nodo *tail;
    public:
        cola();
        ~cola();
        void insertar(int);
        int extraer();
        bool colaVacia();
};
typedef cola *pcola;

cola::cola(){
    head = NULL;
    tail = NULL;
}

cola::~cola(){
    nodo *p, *rp;
    p = head;
    while(p!=NULL){
        rp = p;
        p = p->next;
        delete rp;
    }
}

void cola::insertar(int x){
    nodo *p;
    p = new nodo;
    p->data = x;
    p->next = NULL;
    if(head==NULL){
        head = p;
        tail = p;
    }
    else{
        tail->next = p;
        tail = p;
    }
}

int cola::extraer(){
    nodo *p;
    int x;
    if(head!=NULL){
        p = head;
        x = p->data;
        head = head->next;
        delete p;
        return x;
    }
    else{
        return -1;
    }
}

bool cola::colaVacia(){
    if(head==NULL){
        return true;
    }
    else{
        return false;
    }
}

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
    bfs(g, 0);
}

void bfs(grafo g, int r){
    pcola c;
    c = new cola;
    c->insertar(r);
    int v;
    while(!c->colaVacia()){
        v = c->extraer();
        pvertice p;
        p = g.getPgrafo();
        while(p->datoOrigen != v){
            p = p->sgteVertice;
        }
        parista a;
        a = p->adyacente;
        while(a!=NULL){
            if(pre[a->datoDestino] == -1){
                pre[a->datoDestino] = cont;
                cont++;
                c->insertar(a->datoDestino);
            }
            a = a->sgteArista;
        }
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