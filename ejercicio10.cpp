#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

// Movimientos: arriba, abajo, izquierda, derecha
int movF[4] = { -1, 1, 0, 0 };
int movC[4] = { 0, 0, -1, 1 };

// Verifica si una posición es válida para visitar
bool esValido(int f, int c, int M, int N, char **mapa, bool **visitado, char buscado) {
    // Dentro del mapa
    if (f < 0 || f >= M || c < 0 || c >= N)
        return false;

    // Ya visitado
    if (visitado[f][c])
        return false;

    // Si es corredor ('C') o es el producto buscado → se puede avanzar
    if (mapa[f][c] == 'C' || mapa[f][c] == buscado)
        return true;

    // Cualquier otro producto NO se puede atravesar
    return false;
}

// Backtracking para encontrar el producto con menor cantidad de pasos
void bt(int f, int c, int pasos, int M, int N, char **mapa, bool **visitado,
        char buscado, int &mejorCantPasos, int indiceFCActual, int &indiceMejorPasos) {

    // Si ya superamos el mejor camino global, no vale la pena seguir
    if (pasos >= mejorCantPasos)
        return;

    // Si encontramos el producto
    if (mapa[f][c] == buscado) {
        mejorCantPasos = pasos;
        indiceMejorPasos = indiceFCActual;
        return;
    }

    visitado[f][c] = true;

    // Probar las 4 direcciones
    for (int i = 0; i < 4; i++) {
        int nf = f + movF[i];
        int nc = c + movC[i];

        if (esValido(nf, nc, M, N, mapa, visitado, buscado)) {
            bt(nf, nc, pasos + 1, M, N, mapa, visitado,
               buscado, mejorCantPasos, indiceFCActual, indiceMejorPasos);
        }
    }

    visitado[f][c] = false;  // backtracking
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char buscado;
    cin >> buscado;

    int P;
    cin >> P;

    // Variables globales reutilizadas para todos los FCs
    int mejorCantPasos = 999999999;  // suficientemente grande
    int indiceMejorPasos = 1;

    for (int idx = 1; idx <= P; idx++) {

        int M, N;
        cin >> M >> N;

        // Crear mapa
        char **mapa = new char*[M];
        for (int i = 0; i < M; i++) {
            mapa[i] = new char[N];
            for (int j = 0; j < N; j++) {
                cin >> mapa[i][j];
            }
        }

        // Crear matriz visitados
        bool **visitado = new bool*[M];
        for (int i = 0; i < M; i++) {
            visitado[i] = new bool[N];
            for (int j = 0; j < N; j++)
                visitado[i][j] = false;
        }

        // Solo explorar si la posición inicial es válida (como en el laberinto del profe)
        if (esValido(0, 0, M, N, mapa, visitado, buscado)) {
            bt(0, 0, 0, M, N, mapa, visitado,
               buscado, mejorCantPasos, idx, indiceMejorPasos);
        }

        // Liberar memoria
        for (int i = 0; i < M; i++) {
            delete[] mapa[i];
            delete[] visitado[i];
        }
        delete[] mapa;
        delete[] visitado;
    }

    cout << indiceMejorPasos << " " << mejorCantPasos << "\n";

    return 0;
}