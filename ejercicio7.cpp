#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

// Función para mergear y contar cantidad de invertidos
long long mergeYCont(int arr[], int temp[], int izq, int mid, int der) {
    int i = izq;    // Índice para el subarreglo izquierdo
    int j = mid + 1; // Índice para el subarreglo derecho
    int k = izq;    // Índice para el arreglo temporal
    long long invCount = 0;

    // Merge de los arreglos mientras se cuentan los invertidos
    while (i <= mid && j <= der) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            invCount += (mid - i + 1);
        }
    }

    // Copiar elementos restantes del subarreglo izquierdo
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copiar elementos restantes del subarreglo derecho
    while (j <= der) {
        temp[k++] = arr[j++];
    }

    // Copiar el arreglo temporal de vuelta al original
    for (i = izq; i <= der; i++) {
        arr[i] = temp[i];
    }

    return invCount;
}

// Función recursiva de merge sort que cuenta invertidos
long long mergearOrdenarYContar(int arr[], int temp[], int izq, int der) {
    long long invCount = 0;
    
    if (izq >= der) {
        return invCount;
    }else{
        int mid = izq + (der - izq) / 2;

        // Contar invertidos en la mitad izquierda
        invCount += mergearOrdenarYContar(arr, temp, izq, mid);

        // Contar invertidos en la mitad derecha
        invCount += mergearOrdenarYContar(arr, temp, mid + 1, der);

        // Contar invertidos al hacer merge
        invCount += mergeYCont(arr, temp, izq, mid, der);
    }

    return invCount;
}

int main()
{
    int n;
    cin >> n;

    string* oficial = new string[n];
    int* posicionOficial = new int[n]; 
    
    for (int i = 0; i < n; i++) {
        cin >> oficial[i];
    }

    // Leer ranking del ayudante y convertir a posiciones según el oficial
    int* rankingAyudante = new int[n];
    
    for (int i = 0; i < n; i++) {
        string nombre;
        cin >> nombre;
        
        // Buscar la posición de este nombre en el ranking oficial
        for (int j = 0; j < n; j++) {
            if (oficial[j] == nombre) {
                rankingAyudante[i] = j;
                break;
            }
        }
    }
    //Arreglo temporal
    int* temp = new int[n];

    long long invertidos = mergearOrdenarYContar(rankingAyudante, temp, 0, n - 1);

    cout << invertidos << endl;

    delete[] oficial;
    delete[] posicionOficial;
    delete[] rankingAyudante;
    delete[] temp;

    return 0;
}