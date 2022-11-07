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

int *visit;

class grafo{
    private:
        pvertice pGrafo;
        int numVertices;
        int numAristas;
    public:
        grafo();
        ~grafo();
        void insertarVertice(int x);
        void insertarArista(int x, int y, int peso);
        void eliminarArista(int x, int y);
        void mostrarGrafo();
        pvertice getPgrafo();
        int getNumVertices();
        int getNumAristas();
        bool dfsCircuito(int x, int y);
        bool existeCircuito();
        grafo boruvska();
        grafo prim();
        grafo kruskal();
        bool esConexo();
        bool buscarCamino(int x, int y);
        bool existeCamino(int x, int y);
        void agruparDFS(int x, int *v, int cont);
        void unirSubgrafos(grafo);
        void unirGrupos(grafo, int *v);
        
};

grafo::grafo(){
    pGrafo = NULL;
    numVertices = 0;
    numAristas = 0;
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

void grafo::insertarArista(int x, int y, int peso){
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
            a1->peso = peso;
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
            a2->peso = peso;
            p->adyacente = a2;
        }
    }
    numAristas++;
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

pvertice grafo::getPgrafo(){
    return pGrafo;
}

int grafo::getNumVertices(){
    return numVertices;
}

int grafo::getNumAristas(){
    return numAristas;
}

void grafo::mostrarGrafo(){
    pvertice p;
    parista a;
    p = pGrafo;
    while(p!=NULL){
        cout << p->datoOrigen + 1 << " -> ";
        a = p->adyacente;
        while(a!=NULL){
            cout << a->datoDestino + 1 << " ";
            a = a->sgteArista;
        }
        cout << endl;
        p = p->sgteVertice;
    }
}

// Busqueda de circuito
void limpiar(int n){
    for(int i=0; i<n; i++){
        visit[i] = -1;
    }
}

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

bool grafo::existeCamino(int x, int y){
    bool respuesta = buscarCamino(x, y);
    limpiar(numVertices);
    return respuesta;
}

bool grafo::buscarCamino(int x, int y){
    if(x == y){
        return 1;
    }
    visit[x] = 1;
    pvertice p;
    parista a;
    p = pGrafo;
    while(p!=NULL){
        if(p->datoOrigen == x){
            a = p->adyacente;
            while(a != NULL){
                if(visit[a->datoDestino] == -1){
                    if(buscarCamino(a->datoDestino, y) == 1){
                        return 1;
                    }
                }
                a = a->sgteArista;  
            }
        }
        p = p->sgteVertice;
    }
}

bool grafo::esConexo(){
    bool respuesta = true;
    for(int i=0; i<numVertices; i++){
        for(int j=0; j<numVertices; j++){
            if(i != j){
                if(existeCamino(i, j) == 0){
                    respuesta = false;
                }
            }
        }
    }
    return respuesta;
}

parista minimo(pvertice p){
    parista min = p->adyacente;
    parista aux = p->adyacente;
    while(aux!=NULL){
        if(aux->peso < min->peso)
            min = aux;
        aux = aux->sgteArista;
    }
    return min;
}

grafo grafo::boruvska(){
    grafo T;
    pvertice p;
    parista a;
    bool primera = true;
    p = pGrafo;
    while(p!=NULL){
        T.insertarVertice(p->datoOrigen);
        p = p->sgteVertice;
    }
    p = pGrafo;
    while(p!=NULL){
        a = minimo(p);
        T.insertarArista(p->datoOrigen, a->datoDestino, a->peso);
        cout << "Arista insertada: " << p->datoOrigen << " " << a->datoDestino << endl;
        if(T.existeCircuito()){
            cout << "Arista eliminada: " << p->datoOrigen << " " << a->datoDestino << endl;
            
            T.eliminarArista(p->datoOrigen, a->datoDestino);
        
        }
        p = p->sgteVertice;
    }
    return T;
}

void grafo::agruparDFS(int i, int *v, int cont){
    pvertice p = pGrafo;
    parista a;
    while(p != NULL && p->datoOrigen != i){
        p = p->sgteVertice;
    }

    if(p!= NULL){
        a = p->adyacente;
        while(a!=NULL){
            if(v[a->datoDestino] == -1){
                v[a->datoDestino] = cont;
                agruparDFS(a->datoDestino, v, cont);
            }
            a = a->sgteArista;
        }
    }
}

void grafo::unirGrupos(grafo G, int *v){
    
    int numAristasSobrantes = G.getNumAristas() - numAristas;
    int *aristasOrigen = new int[numAristasSobrantes];
    int *aristasDestino = new int[numAristasSobrantes];
    int *pesos = new int[numAristasSobrantes];
    int contAristas = 0;
    pvertice p = G.pGrafo;
    parista a;
    while(p != NULL){
        a = p->adyacente;
        while(a != NULL){
            if(v[p->datoOrigen] != v[a->datoDestino]){
                aristasOrigen[contAristas] = p->datoOrigen;
                aristasDestino[contAristas] = a->datoDestino;
                pesos[contAristas] = a->peso;
                contAristas++;
            }
            a = a->sgteArista;
        }
        p = p->sgteVertice;
    }

    for(int i = 0; i < numAristasSobrantes; i++){
        for(int j = 0; j < numAristasSobrantes - 1; j++){
            if(pesos[j] > pesos[j+1]){
                int aux = pesos[j];
                pesos[j] = pesos[j+1];
                pesos[j+1] = aux;

                aux = aristasOrigen[j];
                aristasOrigen[j] = aristasOrigen[j+1];
                aristasOrigen[j+1] = aux;

                aux = aristasDestino[j];
                aristasDestino[j] = aristasDestino[j+1];
                aristasDestino[j+1] = aux;
            }
        }
    }
    cout << "Aristas a unir: " << endl;
    for(int i = 0; i < numAristasSobrantes; i++){
        cout << aristasOrigen[i] << " " << aristasDestino[i] << endl;
    }
    insertarArista(aristasOrigen[0], aristasDestino[0], pesos[0]);
}

void grafo::unirSubgrafos(grafo G){
    int *v = new int[numVertices];
    int cont;
    int numeroAristas = G.getNumAristas();
    int *aristasOrigen = new int[numeroAristas];
    int *aristasDestino = new int[numeroAristas];
    int *pesos = new int[numeroAristas];
    int contAristas = 0;
    pvertice p;

    while(!esConexo()){
        cont = 0;
        contAristas = 0;
        for (int i = 0; i < numVertices; i++){
            v[i] = -1;
        }
        
        for(int i  = 0; i < numVertices; i++){
            if(v[i] == -1){
                agruparDFS(i, v, cont);
                cout << "cont: " << cont << endl;
                cont++;
            }
        }
        for(int i = 0; i < numVertices; i++){
            cout << v[i] << " ";
        }

        for(int i = 0; i < numVertices; i++){
            for(int j = 0; j < numVertices; j++){
                if(i != j){ // Diferentes vertice
                    if(v[i] != v[j]){ //Diferentes grupos
                        aristasOrigen[contAristas] = i;
                        aristasDestino[contAristas] = j;
                        //pesos[contAristas] = a->peso;
                        cout<<"Arista: "<<i<<" "<<j<<endl;
                        contAristas++;
                        G.eliminarArista(i, j);
                        
                    
                        cout << "Arista eliminada: " << i << " " << j << endl;
                    }
                }
            }
        }

        for(int i = 0; i < contAristas; i++){
            for(int j = 0; j < contAristas - 1; j++){
                if(pesos[j] > pesos[j+1]){
                    int aux = pesos[j];
                    pesos[j] = pesos[j+1];
                    pesos[j+1] = aux;

                    aux = aristasOrigen[j];
                    aristasOrigen[j] = aristasOrigen[j+1];
                    aristasOrigen[j+1] = aux;

                    aux = aristasDestino[j];
                    aristasDestino[j] = aristasDestino[j+1];
                    aristasDestino[j+1] = aux;
                }
            }
        }

        insertarArista(aristasOrigen[0], aristasDestino[0], pesos[0]);
    }
    
}

grafo grafo::prim(){
    grafo T;
    pvertice p;
    parista a;
    bool primera = true;
    p = pGrafo;
    while(p!=NULL){
        T.insertarVertice(p->datoOrigen);
        p = p->sgteVertice;
    }
    p = pGrafo;
    while(p!=NULL){
        a = minimo(p);
        T.insertarArista(p->datoOrigen, a->datoDestino, a->peso);
        if(T.existeCircuito()){            
            T.eliminarArista(p->datoOrigen, a->datoDestino);
        
        }
        p = p->sgteVertice;
    }
    return T;
}

grafo grafo::kruskal(){
    int *aristasOrigen = new int[numAristas];
    int *aristasDestino = new int[numAristas];
    int *pesos = new int[numAristas];
    int contAristas = 0;
    pvertice p = pGrafo;
    parista a;
    while(p != NULL){
        a = p->adyacente;
        while(a != NULL){
            aristasOrigen[contAristas] = p->datoOrigen;
            aristasDestino[contAristas] = a->datoDestino;
            pesos[contAristas] = a->peso;
            eliminarArista(p->datoOrigen, a->datoDestino);
            contAristas++;
            a = a->sgteArista;
        }
        p = p->sgteVertice;
    }

    for(int i = 0; i < numAristas; i++){
        for(int j = 0; j < numAristas - 1; j++){
            if(pesos[j] > pesos[j+1]){
                int aux = pesos[j];
                pesos[j] = pesos[j+1];
                pesos[j+1] = aux;

                aux = aristasOrigen[j];
                aristasOrigen[j] = aristasOrigen[j+1];
                aristasOrigen[j+1] = aux;

                aux = aristasDestino[j];
                aristasDestino[j] = aristasDestino[j+1];
                aristasDestino[j+1] = aux;
            }
        }
    }
    grafo T;
    pvertice p2;
    parista a2;
    p2 = pGrafo;
    while(p2!=NULL){
        T.insertarVertice(p2->datoOrigen);
        p2 = p2->sgteVertice;
    }
    for(int i = 0; i < numAristas; i++){
        T.insertarArista(aristasOrigen[i], aristasDestino[i], pesos[i]);
        
        if(T.existeCircuito()){
            T.eliminarArista(aristasOrigen[i], aristasDestino[i]);
        }
    }

    return T;
}

void llenar(grafo G){
    
}

//MAIN
int main(){
    grafo G, B, P , K;
    for (int i = 0; i < 8; i++){
        G.insertarVertice(i);
    }
    G.insertarArista(0, 1, 3);
    G.insertarArista(0, 2, 1);
    G.insertarArista(1, 3, 1);
    G.insertarArista(1, 6, 5);
    G.insertarArista(2, 3, 2);
    G.insertarArista(2, 5, 5);
    G.insertarArista(3, 4, 4);
    G.insertarArista(3, 5, 2);
    G.insertarArista(4, 6, 2);
    G.insertarArista(4, 7, 1);
    G.insertarArista(5, 7, 3);
    G.mostrarGrafo();
    
    //Boruvska
    B = G.boruvska();
    cout << "Arbol de expansion minima Boruvska: " << endl;
    B.mostrarGrafo();
    limpiar(B.getNumVertices());
    //B.unirSubgrafos(G);
    P = G.prim();
    cout << "Arbol de expansion minima Boruvska: " << endl;
    P.mostrarGrafo();
    limpiar(P.getNumVertices());
    //Prim
    
    K = G.kruskal();
    cout << "Arbol de expansion minima kruskal: " << endl;
    K.mostrarGrafo();
    return 0;
}

