#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;


long long mergeYCont(int arr[], int temp[], int izq, int mid, int der) {
    int i = izq;  
    int j = mid + 1;
    int k = izq; 
    long long invCount = 0;

    while (i <= mid && j <= der) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            invCount += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= der) {
        temp[k++] = arr[j++];
    }

    for (i = izq; i <= der; i++) {
        arr[i] = temp[i];
    }

    return invCount;
}

long long mergearOrdenarYContar(int arr[], int temp[], int izq, int der) {
    long long invCount = 0;
    
    if (izq >= der) {
        return invCount;
    }else{
        int mid = izq + (der - izq) / 2;

        invCount += mergearOrdenarYContar(arr, temp, izq, mid);

        invCount += mergearOrdenarYContar(arr, temp, mid + 1, der);

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

    int* rankingAyudante = new int[n];
    
    for (int i = 0; i < n; i++) {
        string nombre;
        cin >> nombre;
        
        for (int j = 0; j < n; j++) {
            if (oficial[j] == nombre) {
                rankingAyudante[i] = j;
                break;
            }
        }
    }
    int* temp = new int[n];

    long long invertidos = mergearOrdenarYContar(rankingAyudante, temp, 0, n - 1);

    cout << invertidos << endl;

    delete[] oficial;
    delete[] posicionOficial;
    delete[] rankingAyudante;
    delete[] temp;

    return 0;
}