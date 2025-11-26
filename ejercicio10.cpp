#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

void buscarProducto(char** mapa, int M, int N, char producto, 
                    int fila, int col, bool** visitado, 
                    int pasosActuales, int& mejorCantPasos, 
                    int indiceFCActual, int& indiceMejorPasos) {
    if (pasosActuales >= mejorCantPasos) {
        return;
    }
    
    if (mapa[fila][col] == producto) {
        if (pasosActuales < mejorCantPasos) {
            mejorCantPasos = pasosActuales;
            indiceMejorPasos = indiceFCActual;
        }
        return;
    }
    
    int dFila[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};
    
    for (int i = 0; i < 4; i++) {
        int nuevaFila = fila + dFila[i];
        int nuevaCol = col + dCol[i];
        
        if (nuevaFila >= 0 && nuevaFila < M && nuevaCol >= 0 && nuevaCol < N) {
            if (!visitado[nuevaFila][nuevaCol] && 
                (mapa[nuevaFila][nuevaCol] == 'C' || mapa[nuevaFila][nuevaCol] == producto)) {
                
                visitado[nuevaFila][nuevaCol] = true;
                buscarProducto(mapa, M, N, producto, nuevaFila, nuevaCol, 
                              visitado, pasosActuales + 1, mejorCantPasos, 
                              indiceFCActual, indiceMejorPasos);
                visitado[nuevaFila][nuevaCol] = false; 
            }
        }
    }
}

bool** crearMatrizVisitados(int filas, int columnas) {
    bool** visitado = new bool*[filas];
    for (int i = 0; i < filas; i++) {
        visitado[i] = new bool[columnas];
        for (int j = 0; j < columnas; j++) {
            visitado[i][j] = false;
        }
    }
    return visitado;
}

char** crearMapa(int filas, int columnas) {
    char** mapa = new char*[filas];
    for (int i = 0; i < filas; i++) {
        mapa[i] = new char[columnas];
    }
    return mapa;
}

void leerMapa(char** mapa, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cin >> mapa[i][j];
        }
    }
}

int main()
{
    char producto;
    int P;
    
    cin >> producto;
    cin >> P;
    
    int mejorCantPasos = numeric_limits<int>::max();
    int indiceMejorPasos = 1;
    
    for (int fc = 1; fc <= P; fc++) {
        int M, N;
        cin >> M >> N;
        
        char** mapa = crearMapa(M, N);

        leerMapa(mapa, M, N);
        
        bool** visitado = crearMatrizVisitados(M, N);
       
        if (mapa[0][0] == 'C' || mapa[0][0] == producto) {
            visitado[0][0] = true;
            buscarProducto(mapa, M, N, producto, 0, 0, visitado, 
                          0, mejorCantPasos, fc, indiceMejorPasos);
        }
        
        for (int i = 0; i < M; i++) {
            delete[] mapa[i];
            delete[] visitado[i];
        }
        delete[] mapa;
        delete[] visitado;
    }
    
    cout << indiceMejorPasos << " " << mejorCantPasos << endl;
    
    return 0;
}