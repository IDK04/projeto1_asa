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
    return  cuts;
}

int fitsInPart(part *p1, part p2){
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

int isEqualPart(part p1, part p2){
    return (p1.line ==  p2.line && p1.col == p2.col) || (p1.col == p2.line && p1.line == p2.col);
}

/* cut in vertical or horizontal */
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

int knapsack(vector<cut> cuts, part currentPart, cut lastCutReference, part lastPartToCut) {
    if (currentPart.line == 0 || currentPart.col == 0) return 0;
    if (isEqualPart(currentPart, lastCutReference.p)) return lastCutReference.price;

    int maxValue = 0;
    int numObjects = cuts.size();
    for (int i = 0; i < numObjects; i++) {
        if (fitsInPart(&cuts[i].p,currentPart)) {
            part p1, p2;
            cutPart(currentPart, cuts[i].p, HORIZONTAL, &p1, &p2);
            if(isEqualPart(p1,lastPartToCut) || isEqualPart(p2,lastPartToCut)) return 0;
            int h1 = knapsack(cuts, p1, cuts[i],currentPart);
            int h2 = knapsack(cuts, p2, cuts[i],currentPart);
            
            cutPart(currentPart, cuts[i].p, VERTICAL, &p1, &p2);
            if(isEqualPart(p1,lastPartToCut) || isEqualPart(p2,lastPartToCut)) return 0;
            int v1 = knapsack(cuts, p1, cuts[i],currentPart);
            int v2 = knapsack(cuts, p2, cuts[i],currentPart);

            maxValue = max(maxValue, max(h1+h2, v1+v2));
        }
    }
    return maxValue;
} 


int main(){
    /* variveis responsaveis por guardar o tamanho da peça*/
    auto start = std::chrono::high_resolution_clock::now();
    int x,y;
    cin >> x;
    cin >> y;
    vector<cut> cuts = readInput();
    int result = knapsack(cuts,{x,y},{0,0},{0,0});
    cout << result << "\n";
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Print the duration in milliseconds
    std::cout << "Runtime: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}