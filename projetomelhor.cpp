/* Projeto de ASA */

/* 
   Ficheiro: projeto.cpp
   Autores: Eduardo Silva(ist1106929) e Duarte Laia(ist106876)
*/

#include <iostream>
#include <vector>
#include <chrono>

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

int fits(part *p1, part p2){
    /* rotation 1 - default */
    if (p1->line <=  p2.line && p1->col <= p2.col){
        return 1;
    }
    /* rotaion 2 - inverse */
    if (p1->col <= p2.line && p1->line <= p2.col){
        int temp = p1->line;
        p1->line = p1->col;
        p1->col = temp;
        return 1;
    }
    return 0;
}

void fillMatrix(vector<vector<int>> &values, int line, int col){
    int nLines = values.size();
    int nColumns = values[0].size();

    if(line < nColumns && col < nLines){
        values[col][line] = values[line][col];
    }
}

part cutPart(part partToCut,part cutReference,int orientation, part *p1, part *p2){
    if (orientation == HORIZONTAL){
        p1->line = cutReference.line;
        p1->col = partToCut.col;

        p2->line = partToCut.line - cutReference.line;
        p2->col = partToCut.col;
    }
    if (orientation == VERTICAL){
        p1->line = partToCut.line;
        p1->col = cutReference.col;

        p2->line = partToCut.line;
        p2->col = partToCut.col - cutReference.col;
    }
    return partToCut;
}

int knapsack(vector<cut> cuts, part maxSize) {
    vector<vector<int>> values(maxSize.line+1, vector<int>(maxSize.col+1, 0));
    int numCuts = cuts.size();

    for (int i = 1; i <= maxSize.line; i++) {
        for(int j = 1; j <= i && j <= maxSize.col; j++) {
            for (int k = 0; k < numCuts; k++) {
                if (fits(&cuts[k].p , {i,j})) {
                    part p1, p2;
                    cutPart({i,j}, cuts[k].p, HORIZONTAL, &p1, &p2);
                    int h1 = values[p1.line][p1.col];
                    int h2 = values[p2.line][p2.col];
                    
                    cutPart({i,j}, cuts[k].p, VERTICAL, &p1, &p2);
                    int v1 = values[p1.line][p1.col];
                    int v2 = values[p2.line][p2.col];

                    values[i][j] = max(values[i][j], max(cuts[k].price, max(h1+h2,v1+v2)));
                    fillMatrix(values, i, j);
                }
            }
        }
    }

    return values[maxSize.line][maxSize.col];
}

int main(){
    /* variveis responsaveis por guardar o tamanho da peça*/
    auto start = std::chrono::high_resolution_clock::now();
    int x,y;
    cin >> x;
    cin >> y;
    vector<cut> cuts = readInput();
    int result = knapsack(cuts,transposeIfNeeded({x,y}));
    cout << result << "\n";
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Print the duration in milliseconds
    std::cout << "Runtime: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}