/* Projeto de ASA */

/* 
   Ficheiro: projeto.cpp
   Autores: Eduardo Silva(ist1106929) e Duarte Laia(ist106876)
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <stdio.h>

using namespace std;

#define HORIZONTAL 0
#define VERTICAL 1

typedef struct {
    int line;
    int col;
} part;

typedef struct {
    part p;
    int price;
} cut;

part transpose(part p){
    int temp = p.col;
    p.col = p.line;
    p.line = temp;
    return p;
}

vector<cut> readInput(){
    int n;
    cin >> n;
    vector<cut> cuts;

    for (int i=0;i<n;i++){
        cut c,cT;
        cin >> c.p.line >> c.p.col >> c.price;
        cT.p = transpose(c.p);
        cuts.push_back(c);
        cuts.push_back(cT);
    }
    return cuts;
}

int knapsack(vector<cut> cuts,part maxSize) {
    vector<vector<int>> values(maxSize.line+1, vector<int>(maxSize.col+1, 0));
    int numCuts = cuts.size();
    for (int i = 1; i <= maxSize.line; i++) {
        for(int j = 1; j <= maxSize.col; j++) {
            for (int w = 0; w < numCuts; w++) {
                part currentPart = cuts[w].p;
                if (currentPart.line <=  i && currentPart.col <= j){
                    int final = max (cuts[w].price,
                                    max(values[i][currentPart.col]+values[i][j-currentPart.col],
                                    values[currentPart.line][j]+values[i-currentPart.line][j]));
                    
                    values[i][j] = max(values[i][j],final);
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
    cin >> x >> y;
    vector<cut> cuts = readInput();
    int result = knapsack(cuts,{x,y});
    cout << result << "\n";
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Print the duration in milliseconds
    std::cout << "Runtime: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}