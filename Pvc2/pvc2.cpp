#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Location
{
    int x, y;

	//Constructores
    Location(int a, int b) : x(a), y(b) {}
    Location() : x(0), y(0) {}

	//Operadores
    bool operator==(const Location& p) const{
        return (p.x == x) && (p.y == y);
    }

	bool operator!=(const Location& p) const {
        return (p.x != x) || (p.y != y);
    }
};

// Dadas dos localizaciones, calcula la distancia.
double distance(Location A, Location B){
    
    double distancia_x = B.x - A.x;
    double distancia_y = B.y - A.y;
    double distancia = sqrt(pow(distancia_x, 2) + pow(distancia_y, 2));
    
    return distancia;
}

struct Edge
{
	Location A, B;
	double distancia;

	//Constructores
	Edge() : A(), B(), distancia(0) {}
	Edge (Location a, Location b) :
		A(a), B(b), distancia(distance(A, B)) {}

	//Operadores
	bool operator==(const Edge& p) const {
        return (p.A == A) && (p.B == B);
    }

	bool operator!=(const Edge& p) const {
        return (p.A != A) || (p.B != B);
    }

};

// Dadas dos aristas, comprueba si están unidas por alguno de sus extremos
bool joined(Edge a, Edge b){
	return a.A == b.A || a.B == b.B || a.A == b.B || a.B == b.A;
}

//Operadores para ordenar. Comprueba si el elemento más a la derecha es menor
// que el elemento más a la izquierda
bool operator<(const Edge& lhs, const Edge& rhs) {
	return lhs.distancia < rhs.distancia;
}

// Comprueba si se forma un ciclo entre 3 aristas dadas
bool thereIsACycle(Edge a, Edge b, Edge c){
	bool theyAre = false;

	if(joined(a, b) && joined(a,c) && joined(b,c))
		theyAre = true;

	return theyAre;
}

// Función auxiliar que dado un vector de Edge y un objeto edge, indica
// si ya tiene incluida la arista.
bool haveIt(vector<Edge> v, Edge l){
	bool found= false;
	int size = v.size();
	Edge e(l.B,l.A);

	for(int i = 0; i < size && !found; i++){
		//Comprobamos si ya contiene dicha arista en alguno de los
		// dos sentidos
		if(v[i] == l || v[i]== e)
			found = true;

		else{
			for(int j = i+1; j < size && !found; j++)
				if(thereIsACycle(v[i], v[j], l))
					found = true;
		}
	}

	return found;
}

// Segunda heurística.
vector<Edge> SecondAprox(vector<vector<double>> distances, vector<Location> locations){

    int n = distances.size();
    vector<Edge> edges, path;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.emplace_back(locations[i], locations[j]);
        }
    }
	
	//Ordenamos el vector de aristas de menor a mayor
    sort(edges.begin(), edges.end());

	for(const auto e : edges){
		if(path.size() == n-1)
			break;
		if(!haveIt(path, e))
			path.push_back(e);
	}

	return path;
}

int main(int argc, char *argv[]){

    // Comprobar que se ha pasado el nombre del fichero como argumento
    if (argc < 2) {
        cout << "Debe proporcionar el nombre del fichero como argumento" << endl;
        return 1;
    }

    // Abrir el fichero
    ifstream file(argv[1]);
    if (!file) {
        cout << "No se pudo abrir el fichero " << argv[1] << endl;
        return 1;
    }

    // Leer la ubicación de la empresa
    int x, y;
    file >> x >> y;
    Location Company(x, y);

    // Leer las localizaciones de los clientes
    vector<Location> Customers;
	Customers.push_back(Company);
    while (file >> x >> y) {
        Location customer(x, y);
        Customers.push_back(customer);
    }

	//Creamos una matriz de aristas
	vector<vector<double>> grafo;
	vector<double> fila;
	Edge arista;

	for(int i = 0; i < Customers.size(); i++){
		arista.A = Customers[i];
		for(int j = 0; j < Customers.size(); j++){
			arista.B = Customers[j]; 
			arista.distancia = distance(arista.A, arista.B);

			fila.push_back(arista.distancia);
			//cout << "Fila " << i << " " << fila.size() << endl;
		}
		grafo.push_back(fila);
		fila.clear();
	}
	//cout << "TAM GRAPH: " << grafo.size() << endl; 

    vector<Edge> pru;

    auto start = high_resolution_clock::now(); // Marca de tiempo inicial
    pru = SecondAprox(grafo, Customers);
    auto stop = high_resolution_clock::now(); // Marca de tiempo final

    auto transcurrido = duration_cast<duration<double>>(stop - start);
    cout << Customers.size() << "\t" << transcurrido.count() << endl;

    //auto duration = duration_cast<seconds>(stop - start); // Cálculo de la duración en segundos
    //cout << "Tiempo de ejecución: " << duration.count() << " segundos." << endl;

    return 0;
}
