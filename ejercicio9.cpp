#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int max(int a, int b) {
	return a > b ? a : b;
}

void mochila3DO1(int maxSize, int maxLines, int cantArch)
{
    int* tam = new int[cantArch]; 
    int* lineas = new int[cantArch]; 
    int* puntos = new int[cantArch]; 

    for (int i = 0; i < cantArch; i++) {
        cin >> tam[i] >> lineas[i] >> puntos[i];
    }

	
	int *** tab = new int **[cantArch + 1]; 
	for (int archAct = 0; archAct <= cantArch; archAct++)
	{
		tab[archAct] = new int*[maxSize + 1](); 
		for(int sizeAct = 0; sizeAct <= maxSize; sizeAct++) {
			tab[archAct][sizeAct] = new int[maxLines + 1]();
		}
	}



    for (int archAct = 1; archAct <= cantArch; archAct++)
	{
		
		int tamAct = tam[archAct - 1];	
		int linAct = lineas[archAct - 1];
		int volAct = puntos[archAct - 1];

        for (int maxSizeActual = 0; maxSizeActual <= maxSize; maxSizeActual++)
		{

			for (int maxLinesActual = 0; maxLinesActual <= maxLines; maxLinesActual++)
			{

                if (tamAct > maxSizeActual || linAct > maxLinesActual){
                    tab[archAct][maxSizeActual][maxLinesActual] =
                    tab[archAct - 1][maxSizeActual][maxLinesActual];
                } else {

                    int valorDeUsarElArchivo = volAct + tab[archAct - 1][maxSizeActual - tamAct][maxLinesActual - linAct];
                    int valorDeNoUsarElArchivo = tab[archAct - 1][maxSizeActual][maxLinesActual];
                    tab[archAct][maxSizeActual][maxLinesActual] = max(valorDeUsarElArchivo, valorDeNoUsarElArchivo);
                }
			}
		}
	}

    cout << tab[cantArch][maxSize][maxLines] << endl;    


    for (int archivoActual = 0; archivoActual <= cantArch; archivoActual++) {
        for (int sizeActual = 0; sizeActual <= maxSize; sizeActual++) {
            delete[] tab[archivoActual][sizeActual];
        }
        delete[] tab[archivoActual];
    }
    delete[] tab;
    delete[] tam;
    delete[] lineas;
    delete[] puntos;
}

int main()
{
	int cantArch; 
	int maxSize; 
	int maxLines; 
    cin >> cantArch;
	cin >> maxSize;
	cin >> maxLines;
	mochila3DO1(maxSize, maxLines, cantArch);
	return 0;
}