#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

struct Visitados {
    int posI;
    int posJ;
};

void imprime_matriz(int** matriz, int vertices){
    int cont=0;
    cout<<"  ";
    for(int i = 0; i < vertices; i++){
        cout<<(i)<<"   ";
    }
    cout<<endl;
    for(int i = 0; i < vertices; i++) {
        cout<<(i)<<" ";
        for(int j = 0; j < vertices; j++) {
            if(matriz[i][j] != 1) {
                matriz[i][j] = 0;
            }
            cout << matriz[i][j];
            if(j == vertices-1) {
                cout << endl;
                cont++;
                continue;
            }
            cout << " - ";
        }
    }
}

void dfs(int** matriz, int vertices, int i, int visitados[]){
    visitados[i]=1;
    cout << "visitou: " << i+1 << "\n";
    for(int j=0; j<vertices; j++){
        if(!visitados[j]&&matriz[i][j]==1){
            dfs(matriz, vertices, j, visitados);
        }
    }
}

void bfs(int** matriz, int vertices, int i){
    int visitados[vertices];
    for(int j=0; j<vertices; j++){
        visitados[j]=0;
    }
    queue<int> q;
    visitados[i] = 1;
    q.push(i);

    while(!q.empty()){
        i=q.front();
        q.pop();
        cout << "visitou: " << i << "\n";
        for(int j = 0; j<vertices; j++){
            if(matriz[i][j]==1 && (visitados[j]!=1)){
                q.push(j);
                visitados[j]=1;
            }
        }
    }
}

int** montar_matriz(int** matriz, bool dirigido){
    int val1 = 0, val2 = 0, cont = 1;
    bool seletor = true;

    cout << "Digite as conexões, cada número seguido de um ENTER." << endl;
    cout << "Digite um valor negativo para parar." << endl;

    while(seletor) {
        if(val1 < 0 || val2 < 0) {
            break;
        }

        cout << "Conexão " << cont << ": ";
        cin >> val1; cin >> val2; cout << endl;

        if(val1 < 0 || val2 < 0) {
            break;
        }

        if(dirigido) {
            matriz[val1][val2] = 1;
            cont++;
            continue;
        }

        matriz[val1][val2] = 1;
        matriz[val2][val1] = 1;

        cont++;
    }
    return matriz;
}

void menu(int** matriz, int vertices, bool dirigido){
    int j = 0;
    int i = 0;
    int x = 0, y=0;
    int escolha=1;
    int visitados[vertices];
    while(escolha!=0){
        sleep(3);
        cout << "-----------------------------" << endl;
        cout << "imprimir(1)" << endl;
        cout << "dfs(2)" << endl;
        cout << "bfs(3)" << endl;
        cout << "incluir arestas/arcos(4)" << endl;
        cout << "excluir arestas/arcos(5)" << endl;
        cout << "sair(0)" << endl;
        cout << "-----------------------------" << endl;
        cout << endl << endl;
        cin >> escolha;
        if(!isdigit(escolha)){
            if(escolha!=0){
                switch(escolha){
                    case 1:
                        imprime_matriz(matriz,vertices);
                        break;
                    case 2:
                        for(int i=0; i<vertices; i++){
                            visitados[i]=0;
                        }
                        cout << "digite o ponto inicial da pesquisa: ";
                        cin >> j;
                        dfs(matriz, vertices, j, visitados);
                        for(int i = 0; i<vertices; i++){
                            if(visitados[i]!=1){
                                dfs(matriz, vertices, i, visitados);
                            }
                        }
                        break;
                    case 3:

                        cout << "digite o ponto inicial da pesquisa: ";
                        cin >> i;
                        bfs(matriz, vertices, i);
                        break;
                    case 4:
                        montar_matriz(matriz, dirigido);
                        break;
                    case 5:
                        cout << "digite a aresta que deseja excluir: ";
                        cin >> x;
                        cin >> y;
                        if(dirigido){
                            matriz[x][y]=0;
                        }else{
                            matriz[y][x]=0;
                            matriz[x][y]=0;
                        }
                        cout << endl << endl;
                        break;
                    case 6:
                        break;
                }
            }
        }
    }


}

int main() {

    int vertices = 0;
    bool dirigido = false;

    cout << "Entre com o número de vértices: "; cin >> vertices; cout << endl;
    cout << "Grafo não dirigido - 0; Grafo dirigido - 1: "; cin >> dirigido; cout << endl;

    //01 // 02 // 23 // 13 // -10
    int** (matriz) = new int*[vertices];
    for(int i = 0; i < vertices; i++){
        matriz[i] = new int[vertices];
    }

    matriz = montar_matriz(matriz, dirigido);

    menu(matriz, vertices, dirigido);


    return 0;
}