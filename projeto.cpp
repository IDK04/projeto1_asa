/* Projeto de ASA */

/* 
   Ficheiro: projeto.cpp
   Autores: Eduardo Silva(ist1106929) e Duarte Laia(ist106876)
*/

#include <iostream>
#include <vector>

using namespace std;

/* estrutura que define a peça (matriz é a representação )*/
/* pode ser alterada se acharmos que nao se adequa */
typedef struct{
    int X;
    int Y;
    vector<vector<int>> matriz;
} peça;

/* corte */
typedef struct {
    int x;
    int y;
    int preco;
} corte;

/* para definir o tipo do vetor (ponteiros para structs corte)*/
typedef corte* Corte;

vector<Corte> leInput(){
    int n;
    cin >> n;
    vector<Corte> cortes ;

    for (int i=0;i<n;i++){
        corte *c = new corte;
        cin >> c->x >> c->y >> c->preco;
        cortes.push_back(c);
    }
    return  cortes;
}

int main(){
    /* variveis responsaveis por guardar o tamanho da peça*/
    int x,y;
    cin >> x;
    cin >> y;
    vector<Corte> cortes = leInput();

    return 0;
}