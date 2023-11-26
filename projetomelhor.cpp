/* Projeto de ASA */

/* 
   Ficheiro: projeto.cpp
   Autores: Eduardo Silva(ist1106929) e Duarte Laia(ist106876)
*/

#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

typedef struct {
    int line;
    int col;
} part;

/* cut */
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
        if (c.p.line <= 0 || c.p.col <= 0 || c.price <= 0){
            continue;
        }
        if ((cT.p.line != c.p.line) || (cT.p.col != c.p.col)){
            cT.p = transpose(c.p);
            cT.price = c.price;
            cuts.push_back(cT);
        }
        cuts.push_back(c);
    }
    return cuts;
}

int knapsackv2(vector<cut> &cuts,part maxSize) {
    vector<vector<int>> values(maxSize.line+1, vector<int>(maxSize.col+1, 0));
    int numCuts = cuts.size();
    for (int i = 1; i <= maxSize.line; i++) {
        for(int j = 1; j <= maxSize.col; j++) {
            values[i][j] = max(values[i-1][j-1],max(values[i][j-1],values[i-1][j]));
            for (int w = 0; w < numCuts; w++) {
                part p1=cuts[w].p;
                if (p1.line <=  i && p1.col <= j){
                    int final = max (cuts[w].price,
                                    max(values[i][p1.col]+values[i][j-p1.col],
                                        values[p1.line][j]+values[i-p1.line][j]));

                    values[i][j] = max(values[i][j],final);
                }
            }
        }
    }
    
    return values[maxSize.line][maxSize.col];
}

int main(){
    int x,y;
    cin >> x;
    cin >> y;
    part smallestPart;
    vector<cut> cuts = readInput();
    int result = knapsackv2(cuts,{x,y});
    cout << result << "\n";
    return 0;
}