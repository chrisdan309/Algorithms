#include <iostream>
using namespace std;

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
    int peso;
    arista *sgteArista;
};
typedef arista *parista;

struct vertice{
    int datoOrigen;
    arista *adyacente;
    vertice *sgteVertice;
};
typedef vertice *pvertice;

//funciones
bool existe(parista, int);
parista minimun(pvertice p);

class grafo{
    private:
        pvertice pGrafo;
        int numVertices;

    public:
        grafo();
        ~grafo();
        void insertarVertice(int x);
        void insertarArista(int x, int y, int peso);
        void eliminarArista(int x, int y);
        void mostrarGrafo();
        pvertice getPgrafo();
        int getNumVertices();
        bool existeCircuitoBFS(int);
        grafo Prim();
        grafo Kruskal();
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

pvertice grafo::getPgrafo(){
    return pGrafo;
}

void grafo::insertarVertice(int x){
    pvertice p;
    p = new vertice;
    p->datoOrigen = x;
    p->adyacente = NULL;
    p->sgteVertice = pGrafo;
    pGrafo = p;
}

void grafo::insertarArista(int x, int y, int peso){
    pvertice p;
    parista a;
    p = pGrafo;
    while(p!=NULL){
        if(p->datoOrigen == x){
                a = new arista;
                a->datoDestino = y;
                a->sgteArista = p->adyacente;
                a->peso = peso;
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
                a->peso = peso;
                p->adyacente = a;

        }
        p = p->sgteVertice;
    }
}

void grafo::eliminarArista(int x, int y){
    pvertice p;
    parista a, ra;
    p = pGrafo;
    while(p!=NULL){
        if(p->datoOrigen == x){
            a = p->adyacente;
            if(a->datoDestino == y){
                p->adyacente = a->sgteArista;
                delete a;
            }
            else{
                while(a->sgteArista!=NULL){
                    if(a->sgteArista->datoDestino == y){
                        ra = a->sgteArista;
                        a->sgteArista = ra->sgteArista;
                        delete ra;
                    }
                    a = a->sgteArista;
                }
            }
        }
        p = p->sgteVertice;
    }
    p = pGrafo;
    while(p!=NULL){
        if(p->datoOrigen == y){
            a = p->adyacente;
            if(a->datoDestino == x){
                p->adyacente = a->sgteArista;
                delete a;
            }
            else{
                while(a->sgteArista!=NULL){
                    if(a->sgteArista->datoDestino == x){
                        ra = a->sgteArista;
                        a->sgteArista = ra->sgteArista;
                        delete ra;
                    }
                    a = a->sgteArista;
                }
            }
        }
        p = p->sgteVertice;
    }
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
        }
        cout << endl;
        p = p->sgteVertice;
    }
}

int *pre;
int cont;

bool grafo::existeCircuitoBFS(int v){
    pcola c;
    c = new cola;
    c->insertar(v);
    pre = new int[numVertices];
    for(int i=0; i<numVertices; i++){
        pre[i] = -1;
    }
    while(!c->colaVacia()){
        v = c->extraer();
        pvertice p;
        p = pGrafo;
        while(p->datoOrigen != v){
            p = p->sgteVertice;
        }
        parista a;
        a = p->adyacente;
        while(a!=NULL){
            if(pre[a->datoDestino] == -1){
                pre[a->datoDestino] = v;
            }
            else if(pre[v] != a->datoDestino){
                return true;
            }
            a = a->sgteArista;
        }
    }
    return false;
}

bool buscarCamino(grafo G, int verticeInicial, int verticeFinal){
    pvertice p;
    parista a;
    p = G.getPgrafo();
    while(p!=NULL){
        if(p->datoOrigen == verticeInicial){
            a = p->adyacente;
            while(a!=NULL){
                if(a->datoDestino == verticeFinal){
                    return true;
                }
                else{
                    return buscarCamino(G, a->datoDestino, verticeFinal);
                }
                a = a->sgteArista;
            }
        }
        p = p->sgteVertice;
    }
    return false;
}

void dfs(grafo G, int vertice, int *v, int cont){
    pvertice p;
    parista a;
    p = G.getPgrafo();
    while(p!=NULL && p->datoOrigen != vertice){
        p = p->sgteVertice;
    }
    
    if(p!=NULL){
        a = p->adyacente;
        while(a!=NULL){
            
			if(v[a->datoDestino-1] == -1){
                v[a->datoDestino-1] = cont;
                dfs(G, a->datoDestino, v, cont);
            }
            a = a->sgteArista;
        }
    }

}

bool existe(parista a, int x){
    while(a!=NULL){
        if(a->datoDestino == x)
            return true;
        a = a->sgteArista;
    }
    return false;
}

parista minimun(pvertice p){
    parista min = p->adyacente;
    parista aux = p->adyacente;
    while(aux!=NULL){
        if(aux->peso < min->peso)
            min = aux;
        aux = aux->sgteArista;
    }
    return min;
}

bool esConexo(grafo G){
    pvertice p = G.getPgrafo();
    int n = G.getNumVertices();
    int *v = new int[n];
    for(int i = 0; i < n; i++){
        v[i] = p->datoOrigen;
        p = p->sgteVertice;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i != j){
                if(!buscarCamino(G, v[i], v[j])){
                    return false;
                }
            }
        }
    }
    return true;
}

void unirSubTrees(grafo T, grafo G){
    int n = T.getNumVertices(), cont = 0;
    int *v = new int[n];
    pvertice p = T.getPgrafo(), aux;
    parista a;
    for(int i = 0; i < n; i++){
        v[i] = -1;
    }

    for(int i = 0; i < n; i++){
        if(v[i] == -1){
            dfs(T, i+1, v, cont);
            cont++;
        }
    }

    for(int i = 0; i < n; i++){
        cout << v[i] << " ";
    }
    int grupo1, grupo2;
    int min, verticeInicial, verticeFinal;
    pvertice pg = G.getPgrafo();
    
    for(int i = 0; i < n; i++){
        grupo1 = v[i];
        for(int j = 0; j < n; j++){
            grupo2 = grupo1;
            if(v[j] != grupo1){
                grupo2 = v[j];
                break;
            }    
        }
        if(grupo2 == grupo1) break;
        p = G.getPgrafo();
        while(p != NULL){
            p = p->sgteVertice;
            if(p->datoOrigen == i+1){
                
            }
        }

        
    }
}

grafo grafo::Prim (){
    grafo T;
    pvertice p = pGrafo;
    pvertice t = T.getPgrafo();
    parista a;
    while(p != NULL){
        T.insertarVertice(p->datoOrigen);
        int n = numVertices;
        parista a ;
        a = minimun(p);
        T.insertarArista(p->datoOrigen, a->datoDestino, a->peso);
        p = p->sgteVertice;
    }
    return T;
}

grafo grafo::Kruskal (){
    
}

int main(){
    grafo G, T;
    for (int i = 1; i <= 8; i++){
        G.insertarVertice(i);
    }
    G.insertarArista(1, 2, 3);
    G.insertarArista(1, 3, 1);
    G.insertarArista(2, 4, 1);
    G.insertarArista(2, 7, 5);
    G.insertarArista(3, 4, 2);
    G.insertarArista(3, 6, 5);
    G.insertarArista(4, 5, 4);
    G.insertarArista(4, 6, 2);
    G.insertarArista(5, 7, 2);
    G.insertarArista(5, 8, 1);
    G.insertarArista(6, 8, 3);
    G.mostrarGrafo();
    T = G.Prim();
    cout << "T\n";
    T.mostrarGrafo();
    return 0;
}


