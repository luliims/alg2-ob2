#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int *** pd; 
int * frag; 
int max(int a, int b){
    if(a<b){
        return b;
    }
    return a;
}

int maxPuntaje(int ini, int fin, int acPrev){
    if(ini > fin){
        return 0;
    }
    if(pd[ini][fin][acPrev] != -1){
        return pd[ini][fin][acPrev];
    }
    if(ini == fin){
        return pd[ini][fin][acPrev] = (acPrev+1)*(acPrev+1);
    }
    int bestScore = 0;
    int deleteScore = (acPrev+1)*(acPrev+1)+maxPuntaje(ini+1, fin, 0);
    bestScore = deleteScore;

    for(int indSameCol = ini+1; indSameCol <= fin; indSameCol++){
        if(frag[indSameCol] == frag[ini]){
            int dontDeleteScore = maxPuntaje(ini+1, indSameCol-1,0)+maxPuntaje(indSameCol, fin, acPrev+1);
            bestScore = max(bestScore, dontDeleteScore);
        }
    }
    return pd[ini][fin][acPrev] = bestScore;
}




int main() {
    int cantFrag;
    cin >> cantFrag;
    frag = new int[cantFrag];
    for(int i = 0; i < cantFrag; i++) {
        cin >> frag[i];
    }
    pd = new int**[cantFrag];
    for(int i = 0; i < cantFrag; i++) {
        pd[i] = new int*[cantFrag];
        for(int j = 0; j < cantFrag; j++) {
            pd[i][j] = new int[cantFrag];
        }
    }
    for(int i = 0; i < cantFrag; i++) {
        for(int j = 0; j < cantFrag; j++) {
            for(int k = 0; k < cantFrag; k++) {
                pd[i][j][k] = -1;
            }
        }
    }
    cout << maxPuntaje(0, cantFrag - 1, 0);

    return 0;
}
