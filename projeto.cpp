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
    return  cuts;
}

/* force p1 to fits in p2 (if is possible) */
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

/* cut in vertical or horizontal */
part cutPart(part partToCut,part cutReference,int orientation){
    if (orientation == HORIZONTAL){
        partToCut.line -= cutReference.line;
    }
    if (orientation == VERTICAL){
        partToCut.col -= cutReference.col;
    }
    return partToCut;
}

int knapsack(vector<cut> cuts, part currentpart) {
    if (currentpart.line == 0 || currentpart.col == 0) return 0;

    int maxValue = 0;
    int numObjects = cuts.size();
    for (int i = 0; i < numObjects; i++) {
        if (fitsInPart(&cuts[i].p,currentpart)) {
            maxValue = max(maxValue,max (knapsack(cuts,cutPart(currentpart,cuts[i].p,HORIZONTAL)) + cuts[i].price, 
                                        knapsack(cuts,cutPart(currentpart,cuts[i].p,VERTICAL)) + cuts[i].price));
        }
    }
    return maxValue;
} 


int main(){
    /* variveis responsaveis por guardar o tamanho da peça*/
    int x,y;
    cin >> x;
    cin >> y;
    vector<cut> cuts = readInput();
    int result = knapsack(cuts,{x,y});
    cout << result;
    return 0;
}