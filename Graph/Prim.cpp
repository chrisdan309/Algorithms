#include <iostream>
using namespace std;

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
    public:
        grafo();
        ~grafo();
        void insertarVertice(int x);
        void insertarArista(int x, int y, int peso);
        void mostrarGrafo();
        pvertice getPgrafo();
        int numVertices();
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
            if(!existe(p->adyacente, y)){
                a = new arista;
                a->datoDestino = y;
                a->sgteArista = p->adyacente;
                a->peso = peso;
                p->adyacente = a;
            }
        }
        p = p->sgteVertice;
    }
    p = pGrafo;
    while(p!=NULL){
        if(p->datoOrigen == y){
            if(!existe(p->adyacente, x)){
                a = new arista;
                a->datoDestino = x;
                a->sgteArista = p->adyacente;
                a->peso = peso;
                p->adyacente = a;

            }
        }
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
    int n = G.numVertices();
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
    int n = T.numVertices(), cont = 0;
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

grafo MST (grafo g){
    grafo T;
    pvertice p = g.getPgrafo();
    pvertice t;
    while(p!=NULL){
        T.insertarVertice(p->datoOrigen);
        p = p->sgteVertice;
    }
    p = g.getPgrafo();
    while(p!=NULL){
        parista a = minimun(p);
        T.insertarArista(p->datoOrigen, a->datoDestino, a->peso);
        p = p->sgteVertice;
    }   
    unirSubTrees(T, g); 
    return T;
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
    T = MST(G);
    cout << "T\n";
    T.mostrarGrafo();
    return 0;
}


