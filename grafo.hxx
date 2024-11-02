#include "Grafo.h"
#include <fstream>
#include <sstream>
#include <string>

template <class T>
Grafo<T>::Grafo() {
    this->aristas = NULL;
}

template <class T>
void Grafo<T>::setVertices(std::vector<T> vertices) {
    this->vertices = vertices;
}

template <class T>
void Grafo<T>::setAristas (int** aristas) {
    this->aristas = aristas;
}

template <class T>
const std::vector<T>& Grafo<T>::getVertices() const {
    return this->vertices;
}

template <class T>
int** Grafo<T>::getAristas() {
    return this->aristas;
}

template <class T>
int Grafo<T>::cantVertices() {
    return vertices.size();
}

template <class T>
int Grafo<T>::cantAristas() {
    int suma = 0;
    for (int i = 0; i < cantVertices(); i++) {
        for (int j = 0; j < cantVertices(); j++) {
            if (*(*(aristas+i)+j) != 0)  suma++;
        }
    }
    return suma;
}

template <class T>
int Grafo<T>::buscarVertice(T ver) {
    int ind = -1;
    for (int i = 0; i < cantVertices(); i++) {
        if (vertices[i] == ver)  ind = i;
    }
    return ind;
}

template <class T>
bool Grafo<T>::insertarVertice(T ver) {
    bool res = false;
    if (buscarVertice(ver) == -1) {
        vertices.push_back(ver);
        int** nmatriz = new int*[cantVertices()];
        for (int i = 0; i < cantVertices(); i++) {
            *(nmatriz+i) = new int[cantVertices()];
        }
        for (int i = 0; i < cantVertices()-1; i++) {
            for (int j = 0; j < cantVertices()-1; j++) {
                *(*(nmatriz+i)+j) = *(*(aristas+i)+j);
            }
        }

        // Inicializar la nueva fila (para el nuevo vértice)
        for (int j = 0; j < cantVertices(); j++) {
            nmatriz[cantVertices() - 1][j] = 0; // Inicializa todos los elementos de la nueva fila
        }
        // Inicializar la nueva columna (para el nuevo vértice)
        for (int i = 0; i < cantVertices(); i++) {
            nmatriz[i][cantVertices() - 1] = 0; // Inicializa todos los elementos de la nueva columna
        }

        for (int i = 0; i < cantVertices()-1; i++) {
            delete[] *(aristas+i);
        }
        delete[] aristas;
        aristas = nmatriz;
        res = true;
    }
    return res;
}

template <class T>
bool Grafo<T>::insertarArista(T ori, T des, int cos) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if ( i_ori != -1 && i_des != -1 ) {
        if (*(*(aristas+i_ori)+i_des) == 0) {
            *(*(aristas+i_ori)+i_des) = cos;
            res = true;
        }
    }
    return res;
}


template <class T>
bool Grafo<T>::insAristaNoDir(T ori, T des, int cos) {
   bool res1 = insertarArista(ori, des, cos);
   bool res2 = insertarArista(des, ori, cos);
   return (res1 && res2); 
}

template <class T>
int Grafo<T>::buscarArista(T origen, T destino) {
		int res = -1;
		int i_ori = buscarVertice(origen);
		int i_des = buscarVertice(destino);
		if ( i_ori != -1 && i_des != -1 ) {
			res = *(*(aristas+i_ori)+i_des);
		}
		return res;
}

template <class T>
bool Grafo<T>::eliminarVertice(T ver) {
    int i_ori = buscarVertice(ver);
    int numVer = cantVertices();

    bool eliminado = false;

    if (i_ori != -1) {
        eliminado = true;

        // Eliminar el vértice del vector de vértices
        vertices.erase(vertices.begin() + i_ori);

        // Eliminar fila de la matriz de adyacencia
        delete [] this->aristas[i_ori];

        // Mover las filas restantes para sobreescribir la fila eliminada
        for (int i = i_ori; i < numVer - 1; ++i) {
            aristas[i] = aristas[i + 1];
        }

        // Eliminar la columna en la matriz de adyacencia
        for (int i = 0; i < numVer - 1; i++) {
            for (int j = i_ori; j < numVer - 1; j++) {
                aristas[i][j] = aristas[i][j + 1];
            }
        }

        // Redimensionar las filas restantes
        for (int i = 0; i < numVer - 1; i++) {
            int *nuevafila = new int[numVer - 1];
            for (int j = 0; j < numVer - 1; j++) {
                nuevafila[j] = aristas[i][j];
            }

            // Liberar mem de fila antigua
            delete[] aristas[i];
            aristas[i] = nuevafila;
        }

        // Actualizar el número de vértices
        numVer--;
    }

    return eliminado;
}


template <class T>
bool Grafo<T>::eliminarArista (T origen, T destino) {
		bool res = false;
		int i_ori = buscarVertice(origen);
		int i_des = buscarVertice(destino);
		if ( i_ori != -1 && i_des != -1 ) {
			*(*(aristas+i_ori)+i_des) = 0;
			res = true;
		}
		return res;
}

template <class T>
bool Grafo<T>::elimAristaNoDir (T origen, T destino) {
    bool res1 = eliminarArista(origen, destino);
    bool res2 = eliminarArista(destino, origen);

    return (res1 && res2);
}

template <class T>
std::vector<T> Grafo<T>::vecinosVertice(T ver) {
    int indice = buscarVertice(ver);
    std::vector<T> ver_vecinos;

    if (indice != -1) {
        //Ubicar los vecinos que le correspondan al vertice
        for (int i = 0; i < cantVertices(); i++) {
            if (aristas[indice][i] != 0) {
                ver_vecinos.push_back(vertices[i]);
            }
        }
    }

    //Ordenar los vecinos dependiendo de su tipo de dato
    std::sort(ver_vecinos.begin(), ver_vecinos.end());
    return ver_vecinos;
}

template <class T>
void Grafo<T>::plano() {
    typename std::vector<T>::iterator it = vertices.begin();
    for (;it != vertices.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <class T>
std::vector<T> Grafo<T>::DFS(T ver_inicial) {
    std::vector<bool> ver_visitados;
    std::vector<T> caminoDFS;
    std::stack<T> pila_ver;

    if (buscarVertice(ver_inicial) == -1) {
        std::cout << "El vertice " << ver_inicial << " no esta dentro del grafo" << std::endl;
        return caminoDFS;
    }

    pila_ver.push(ver_inicial);

    ver_visitados.resize(cantVertices(), false);

    while (!pila_ver.empty()) {
        T ver_actual = pila_ver.top();
        pila_ver.pop();
        //Obtener todos los vertices que tengan a ver_actual como origen
        std::vector<T> ver_vecinos = vecinosVertice(ver_actual);
        int ind = buscarVertice(ver_actual);
        //Revisar que el vertice aun no ha sido visitado
        if(!ver_visitados[ind]) {
            std::cout<< vertices[ind] << " ";
            ver_visitados[ind] = true;
            caminoDFS.push_back(vertices[ind]);

            typename std::vector<T>::reverse_iterator it = ver_vecinos.rbegin();
            for (;it != ver_vecinos.rend(); it ++) {
                pila_ver.push(*it);
            }   

        }
    }

    std::cout << std::endl;

    return caminoDFS;
}

template <class T>
std::vector<T> Grafo<T>::BFS(T ver_inicial) {
    std::vector<bool> ver_visitados;
    std::vector<T> caminoBFS;
    std::queue<T> pila_ver;

    if (buscarVertice(ver_inicial) == -1) {
        std::cout << "El vertice " << ver_inicial << " no esta dentro del grafo" << std::endl;
        return caminoBFS;
    }

    pila_ver.push(ver_inicial);

    ver_visitados.resize(cantVertices(), false);

    while (!pila_ver.empty()) {
        T ver_actual = pila_ver.front();
        pila_ver.pop();
        //Obtener todos los vertices que tengan a ver_actual como origen
        std::vector<T> ver_vecinos = vecinosVertice(ver_actual);
        int ind = buscarVertice(ver_actual);
        //Revisar que el vertice aun no ha sido visitado
        if(!ver_visitados[ind]) {
            std::cout<< vertices[ind] << " ";
            ver_visitados[ind] = true;
            caminoBFS.push_back(vertices[ind]);

            typename std::vector<T>::iterator it = ver_vecinos.begin();
            for (;it != ver_vecinos.end(); it ++) {
                pila_ver.push(*it);
            }   

        }
    }

    std::cout << std::endl;

    return caminoBFS;
}

//Funciones para la realización del taller
template <class T>
void Grafo<T>::cargarRelacionesDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    int n;
    archivo >> n; // Lee la cantidad de personas en el archivo
    T persona1, persona2;

    while (archivo >> persona1 >> persona2) {
        insertarVertice(persona1);
        insertarVertice(persona2);
        insAristaNoDir(persona1, persona2, 1); // Usa 1 como costo de la arista de amistad
    }

    archivo.close();
}

template <class T>
int Grafo<T>::calcularDistanciaMinima(T origen, T destino) {
    int idxOrigen = buscarVertice(origen);
    int idxDestino = buscarVertice(destino);

    if (idxOrigen == -1 || idxDestino == -1) {
        return -1; // Si alguno de los vértices no está en el grafo
    }

    std::vector<bool> visitado(cantVertices(), false);
    std::vector<int> distancia(cantVertices(), -1);
    std::queue<int> cola;

    visitado[idxOrigen] = true;
    distancia[idxOrigen] = 0;
    cola.push(idxOrigen);

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();

        // Corrección aquí: 'vecino' debe ser del tipo T, no int
        for (T vecino : vecinosVertice(vertices[actual])) {
            int idxVecino = buscarVertice(vecino);
            if (!visitado[idxVecino]) {
                visitado[idxVecino] = true;
                distancia[idxVecino] = distancia[actual] + 1;
                cola.push(idxVecino);

                if (idxVecino == idxDestino) {
                    return distancia[idxVecino];
                }
            }
        }
    }
    return -1; // No hay camino entre origen y destino
}


template <class T>
void Grafo<T>::evaluarGradosDeSeparacion(const std::string& archivoPares, const std::string& archivoSalida) {
    std::ifstream archivo(archivoPares);
    std::ofstream salida(archivoSalida);

    if (!archivo.is_open() || !salida.is_open()) {
        std::cerr << "No se pudo abrir uno de los archivos" << std::endl;
        return;
    }

    int m;
    archivo >> m; // Cantidad de relaciones a evaluar

    T persona1, persona2;
    while (archivo >> persona1 >> persona2) {
        int distancia = calcularDistanciaMinima(persona1, persona2);
        salida << persona1 << " " << persona2 << " ";
        if (distancia != -1 && distancia <= 6) {
            salida << "Cumple" << std::endl;
        } else {
            salida << "No Cumple" << std::endl;
        }
    }

    archivo.close();
    salida.close();
}