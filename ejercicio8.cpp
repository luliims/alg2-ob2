#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int *** pd; //inicializada a -1 en todas sus posiciones para indicar que el estado no ha sido calculado
int * frag; //arrreglo que contiene los colores de los fragmentos
int max(int a, int b);

int maxPuntaje(int ini, int fin, int acPrev){
    //caso base
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
    //op borrar
    int deleteScore = (acPrev+1)*(acPrev+1)+maxPuntaje(ini+1, fin, 0);
    bestScore = deleteScore;

    //op no borrar ahora, unir con otro igual dsp
    //buscamos si hay pos del mismo color
    for(int indSameCol = ini+1; indSameCol <= fin; indSameCol++){
        /*
        si encontramos otro frag del mismo color:
        a) primero eliminamos lo que hay en el medio [ini+1..indSameCol-1]
        b)luego unimos inicio con indSameCol (con acPrev+1)
        */
        if(frag[indSameCol] == frag[ini]){
            int dontDeleteScore = maxPuntaje(ini+1, indSameCol-1,0)+maxPuntaje(indSameCol, fin, acPrev+1);
            bestScore = max(bestScore, dontDeleteScore);
        }
    }
    return pd[ini][fin][acPrev] = bestScore;
}




int main()
{
    // TODO
    return 0;
}