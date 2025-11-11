#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct Pozo {
    long long inicio;
    long long fin;
};

struct Mejora {
    long long posicion;
    long long potencia;
};

// Implementación de Max-Heap
class MaxHeap {
private:
    Mejora* arr;
    int capacidad;
    int tamanio;
    
    void heapifyUp(int pos) {
        while (pos > 0) {
            int padre = (pos - 1) / 2;
            if (arr[pos].potencia > arr[padre].potencia) {
                Mejora temp = arr[pos];
                arr[pos] = arr[padre];
                arr[padre] = temp;
                pos = padre;
            } else {
                break;
            }
        }
    }
    
    void heapifyDown(int pos) {
        while (true) {
            int mayor = pos;
            int izq = 2 * pos + 1;
            int der = 2 * pos + 2;
            
            if (izq < tamanio && arr[izq].potencia > arr[mayor].potencia) {
                mayor = izq;
            }
            if (der < tamanio && arr[der].potencia > arr[mayor].potencia) {
                mayor = der;
            }
            
            if (mayor != pos) {
                Mejora temp = arr[pos];
                arr[pos] = arr[mayor];
                arr[mayor] = temp;
                pos = mayor;
            } else {
                break;
            }
        }
    }
    
public:
    MaxHeap(int cap) {
        capacidad = cap;
        tamanio = 0;
        arr = new Mejora[capacidad];
    }
    ~MaxHeap() {
        delete[] arr;
    }
    void push(Mejora m) {
        if (tamanio < capacidad) {
            arr[tamanio] = m;
            heapifyUp(tamanio);
            tamanio++;
        }
    }
    Mejora top() {
        return arr[0];
    }
    void pop() {
        if (tamanio > 0) {
            arr[0] = arr[tamanio - 1];
            tamanio--;
            heapifyDown(0);
        }
    }
    bool esVacio() {
        return tamanio == 0;
    }
};

int main()
{
    int N, M;
    long long F;
    cin >> N >> M >> F;
    Pozo* pozos = new Pozo[N];
    for (int i = 0; i < N; i++) {
        cin >> pozos[i].inicio >> pozos[i].fin;
    }
    Mejora* mejoras = new Mejora[M];
    for (int i = 0; i < M; i++) {
        cin >> mejoras[i].posicion >> mejoras[i].potencia;
    }
    long long posicionActual = 1;
    long long potenciaActual = 1;
    int mejorasUsadas = 0;
    int indiceMejora = 0;
    
    MaxHeap heap(M);
    
    while (posicionActual < F) {
        long long alcanceMaximo = posicionActual + potenciaActual;
        // Si ya podemos llegar al destino
        if (alcanceMaximo >= F) {
            cout << mejorasUsadas << endl;
            delete[] pozos;
            delete[] mejoras;
            return 0;
        }
        // Agregar todas las mejoras alcanzables al heap
        while (indiceMejora < M && mejoras[indiceMejora].posicion <= alcanceMaximo) {
            heap.push(mejoras[indiceMejora]);
            indiceMejora++;
        }
        // Encontrar hasta dónde podemos avanzar realmente (considerando pozos)
        long long nuevaPosicion = alcanceMaximo;
        // Buscar el primer pozo que nos bloquea completamente
        for (int i = 0; i < N; i++) {
            // Si el pozo empieza después de nuestro alcance, no nos afecta
            if (pozos[i].inicio > alcanceMaximo) {
                break;
            }
            // Si el pozo termina antes de nuestra posición actual, ya lo pasamos
            if (pozos[i].fin < posicionActual) {
                continue;
            }
            if (pozos[i].inicio <= alcanceMaximo && pozos[i].fin >= alcanceMaximo) {
                // Solo podemos avanzar hasta antes del pozo
                nuevaPosicion = pozos[i].inicio - 1;
                break;
            }
        }
        // Si no podemos avanzar, necesitamos una mejora
        if (nuevaPosicion <= posicionActual) {
            if (heap.esVacio()) {
                cout << "Imposible" << endl;
                delete[] pozos;
                delete[] mejoras;
                return 0;
            }
            Mejora mejorMejora = heap.top();
            heap.pop();
            potenciaActual += mejorMejora.potencia;
            mejorasUsadas++;
        } else {
            posicionActual = nuevaPosicion;
        }
    }
    cout << mejorasUsadas << endl;
    delete[] pozos;
    delete[] mejoras;
    return 0;
}