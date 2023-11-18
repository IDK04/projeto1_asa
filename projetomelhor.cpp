/* Projeto de ASA */

/* 
   Ficheiro: projeto.cpp
   Autores: Eduardo Silva(ist1106929) e Duarte Laia(ist106876)
*/

#include <iostream>
#include <vector>

using namespace std;

#define HORIZONTAL 0
#define VERTICAL 1

typedef struct {
    int line;
    int col;
} part;

/* cut */
typedef struct {
    part p;
    int price;
} cut;

/* to define the vector type */

vector<cut> readInput(){
    int n;
    cin >> n;
    vector<cut> cuts ;

    for (int i=0;i<n;i++){
        cut c;
        cin >> c.p.line >> c.p.col >> c.price;
        cuts.push_back(c);
    }
    return cuts;
}

part transposeIfNeeded(part p){
    if(p.col > p.line){
        int temp = p.col;
        p.col = p.line;
        p.line = temp;
    }
    return p;
}

int fits(part p1, part p2){
    return (p1.line <= p2.line && p1.col <= p2.col) || (p1.line <= p2.col && p1.col <= p2.line);
}

void fillMatrix(vector<vector<int>> &values, int line, int col){
    int nLines = values.size();
    int nColumns = values[0].size();

    if(line < nColumns && col < nLines){
        values[col][line] = values[line][col];
    }
}

int knapsack(vector<cut> cuts, part maxSize) {
    vector<vector<int>> values(maxSize.line+1, vector<int>(maxSize.col+1, 0));
    int numCuts = cuts.size();

    for (int i = 1; i <= maxSize.line; i++) {
        for(int j = 1; j <= i && j <= maxSize.col; j++) {
            for (int k = 0; k < numCuts; k++) {
                if (fits(cuts[k].p , {i,j})) {
                    values[i][j] = max(values[i][j], cuts[k].price + values[i - cuts[k].p.line][j - cuts[k].p.col]);
                    fillMatrix(values, i, j);
                }
            }
        }
    }

    for (int i = 0; i <= maxSize.line; i++) {
        for(int j = 0; j <= maxSize.col; j++){
            printf("%d ", values[i][j]);
        }      
        printf("\n");
    }

    return values[maxSize.line][maxSize.col];
}

int main(){
    /* variveis responsaveis por guardar o tamanho da peça*/
    int x,y;
    cin >> x;
    cin >> y;
    vector<cut> cuts = readInput();
    int result = knapsack(cuts,transposeIfNeeded({x,y}));
    cout << result << "\n";
    return 0;
}