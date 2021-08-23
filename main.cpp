#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

struct Visitados {
    int posI;
    int posJ;
};

void imprime_matriz(int** matriz, int vertices){
    int cont=0;
    cout<<"  ";
    for(int i = 0; i < vertices; i++){
        cout<<(i+1)<<"   ";
    }
    cout<<endl;
    for(int i = 0; i < vertices; i++) {
        cout<<(i+1)<<" ";
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

int main() {

    int vertices = 0;
    bool dirigido = false;

    cout << "Entre com o número de vértices: "; cin >> vertices; cout << "endl";
    cout << "Grafo não dirigido - 0; Grafo dirigido - 1: "; cin >> dirigido; cout << endl;

    //01 // 02 // 23 // 13 // -10
    int** (matriz) = new int*[vertices];
    for(int i = 0; i < vertices; i++){
        matriz[i] = new int[vertices];
    }

    bool seletor = true;
    int cont = 1;
    cout << "Digite as conexões, cada número seguido de um ENTER." << endl;
    cout << "Digite um valor negativo para parar." << endl;
    
    int val1 = 0, val2 = 0;
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

    imprime_matriz(matriz,vertices);

    stack<int> stack;

    seletor = true;
    Visitados visitados[vertices];
    for(int i = 0; i < vertices; i++) {
        visitados[i].posI = 0;
        visitados[i].posJ = 0;
    }
    int i = 0;
    int j = 0;
    bool volta = false;
    cont = 0;
    while(seletor) {
        if(!volta) {
            if(matriz[i][j] == 1) {
                if(stack.empty()) {
                    i = j;
                    stack.push(j);
                    j = 0;
                } else if(stack.top() == i) {
                    visitados[cont].posI = i;
                    visitados[cont].posJ = j;
                    cont++;
                    j++;
                    continue;
                } else {
                    i = j;
                    stack.push(j);
                    j = 0;
                }
            }
            cout << "i: " << i << " j: " << j << " val: " << matriz[i][j] << endl;
            j++;
            if(j == vertices) {
                if(stack.top() == i) {
//                    cout << i << endl;
                    i++;
                    j = 0;
                    continue;
                }
                volta = true;
                j = 0;
            }
        } else {

            seletor = false;
        }

//        break;

    }

    return 0;
}