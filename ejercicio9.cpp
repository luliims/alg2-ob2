#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int max(int a, int b) {
	return a > b ? a : b;
}

// Importante usar variables nemotecnicas
void mochila3DO1(int maxSize, int maxLines, int cantArch)
{
    //inicializamos los arrays con los datos
    int* tam = new int[cantArch]; // tamaño de cada uno de los ejercicios
    int* lineas = new int[cantArch]; // lineas de cada uno de los ejercicios
    int* puntos = new int[cantArch]; // volumen de cada uno de los ejercicios

    // Cargamos los valores desde la entrada estándar
    for (int i = 0; i < cantArch; i++) {
        cin >> tam[i] >> lineas[i] >> puntos[i];
    }

	// Generamos la matriz de tabulacion ahora con 3 dimensiones, la tercera dimension son los puntos
	int *** tab = new int **[cantArch + 1]; // archivos +1 para generar la fila de 0 correspondiente a no tener ningun objeto
	for (int archAct = 0; archAct <= cantArch; archAct++)
	{
		tab[archAct] = new int*[maxSize + 1](); // +1 para generar la columna de 0 correspondiente a no tener capacidad
		for(int sizeAct = 0; sizeAct <= maxSize; sizeAct++) {
			tab[archAct][sizeAct] = new int[maxLines + 1]();
		}
	}


	// La fila 0 no la recorremos, solamente la consultamos
	for (int archAct = 1; archAct <= cantArch; archAct++)
	{
		// en todos los casos se resta 1 porque el vector comienza en 0 y el objeto actual esta dado por la matriz considerando el 0 como donde no hay objeto
		int tamAct = tam[archAct - 1];	
		int linAct = lineas[archAct - 1];
		int volAct = puntos[archAct - 1];
		// Recorremos todas las columnas desde 0 (no tener capacidad) hasta la capacidad maxima inclusive
		for (int maxSizeActual = 0; maxSizeActual <= maxSize; maxSizeActual++)
		{

			for (int maxLinesActual = 0; maxLinesActual <= maxLines; maxLinesActual++)
			{
                // Si el objeto actual no entra en la capacidad actual (puede no entrar por peso o por volumen)
                if (tamAct > maxSizeActual || linAct > maxLinesActual){
                    tab[archAct][maxSizeActual][maxLinesActual] =
                    tab[archAct - 1][maxSizeActual][maxLinesActual];
                } else {
                    // El valor maximo que podemos obtener es el valor del objeto actual + el valor maximo que podemos obtener sin usar el objeto actual (fila de arriba) y sin usar la capacidad que ocupa el objeto actual (restar la capacidad actual con el peso del objeto actual)
                    int valorDeUsarElArchivo = volAct + tab[archAct - 1][maxSizeActual - tamAct][maxLinesActual - linAct];
                    int valorDeNoUsarElArchivo = tab[archAct - 1][maxSizeActual][maxLinesActual];
                    tab[archAct][maxSizeActual][maxLinesActual] = max(valorDeUsarElArchivo, valorDeNoUsarElArchivo);
                }
			}
		}
	}
    // La cantidad de puntos que obtendra por la entrega.
    cout << tab[cantArch][maxSize][maxLines] << endl;    

    //libero memoria
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
	int cantArch; // cantidad de archivos (N)
	int maxSize; // tamaño máximo (S)
	int maxLines; // líneas máxima (L)
    cin >> cantArch;
	cin >> maxSize;
	cin >> maxLines;
	mochila3DO1(maxSize, maxLines, cantArch);
	return 0;
}