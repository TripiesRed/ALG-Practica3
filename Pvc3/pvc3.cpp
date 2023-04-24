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

//Operadores para ordenar. Comprueba si el elemento más a la derecha es menor
// que el elemento más a la izquierda
bool operator<(const Edge& lhs, const Edge& rhs) {
	return rhs.distancia < lhs.distancia;
}

// Dado un vector de Locations y una Location, elimina las apariciones de Location del vector.
void eliminate(vector<Location>& v, const Location& l) {
    v.erase(find(v.begin(), v.end(), l));
}

void eliminate(vector<vector<Edge>>& v, const Edge& l) {
	int i = 0;
	Edge e(l.B, l.A);
	while(i < v.size() && (v[i][0].A != l.A || v[i][0].B != l.B)){
		if(v[i][0].A == l.A )
    		v[i].erase(find(v[i].begin(), v[i].end(), l));

		if(v[i][0].B == l.B )
			v[i].erase(find(v[i].begin(), v[i].end(), e));
		i++;
	}
    
}

// Dado un vector de Edges, devuelve la arista más pequeña
Edge getMinEdge(vector<Edge> v){

	cout << v.size() << endl;
	Edge min = v[0];
	if(min.distancia == 0) min = v[1];

	for(auto i : v){
		if(i.distancia < min.distancia && i.distancia != 0 )
			min = i;
	}
	cout << "MIN: " << min.distancia << endl;

	return min;
}

// Dado una matriz de Edges y un vector de Location, busca la arista de la matriz 
// más cercana a cualquiera de las localizaciones del vector.
Edge shortestEdgeToLocations (vector<Location> locations, vector<vector<Edge>> m){

    priority_queue<Edge> shortestEdges;

    for (int i = 0; i < locations.size(); i++) {
		int j = 0; 

		//Nos posicionamos en la fila correspondiente a la localización A respecto
		// de la cual buscaremos la localización que tiene más cerca
		while(j < m.size() && m[j][0].A != locations[i])
			j++;

		shortestEdges.push(getMinEdge(m[j]));
    }

    return shortestEdges.top();
}

// Dado un vector de Locations, busca la distancia mínimo entre dos Location
Edge shortestEdge (vector<vector<Edge>> m){

	priority_queue<Edge> shortestEdges;
	double d;

    for (int i = 0; i < m.size(); i++) {
		cout << "H:" << m[i].size() << endl;
		shortestEdges.push(getMinEdge(m[i]));
    }

    return shortestEdges.top();
}

//Dado un vector de Location y una matriz de Edge, inserta la localización 
// suministrada tal que la distancia entre los dos puntos entre los que se coloca 
// sea la minima
void insertSorted(vector<Location> &v, vector<vector<Edge>> m, Location l){
	vector<double> distancias;

	for(auto p : v)
		distancias.push_back(distance(p,l));
	
	//cout << "Before : " << v.size() << endl;
	// Buscar la posición de inserción
	double d = distancias[0];
	int pos = 0;
	for(int i = 0; i < distancias.size(); i++){
		if(distancias[i] < d){
			pos = i;
			d = distancias[i];
		}
			
	}

    // Insertar el nuevo elemento en la posición correspondiente
    v.insert(v.begin()+pos,l);
	//cout << "After : " << v.size() << endl;
}

// Tercera heurística. Elegimos la localización más cercana de donde nos encontremos.
vector<Location> ThirdAprox(vector<vector<Edge>> customers){

    vector<Location> path;

	//Buscamos la arista más corta entre todas las ciudades y hacemos una 
	// subruta inicial
	Edge edge = shortestEdge(customers);
	cout << "PASO" << endl;
	path.push_back(edge.A);
	path.push_back(edge.B);

	cout << "(" << edge.A.x << ", " << edge.A.y << ")" << endl; 
	cout << "(" << edge.B.x << ", " << edge.B.y << ")" << endl; 
	eliminate(customers, edge);
	cout << "ELIMINATED" << endl;

	//cout << "HOLA" << endl;
    while(!customers.empty() && path.size() < customers.size()){

		edge = shortestEdgeToLocations(path, customers);
		cout << "(" << edge.A.x << ", " << edge.A.y << ")" << endl; 
		cout << "(" << edge.B.x << ", " << edge.B.y << ")" << endl; 
		insertSorted(path, customers, edge.B);
		//cout << "HOLA2" << endl;
		eliminate(customers, edge);
		//cout << "HOLA3 " << customers.size()  << " " << path.size() << endl;
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
	vector<vector<Edge>> grafo;
	vector<Edge> fila;
	Edge arista;

	for(int i = 0; i < Customers.size(); i++){
		arista.A = Customers[i];
		for(int j = 0; j < Customers.size(); j++){
			arista.B = Customers[j]; 
			arista.distancia = distance(arista.A, arista.B);

			fila.push_back(arista);
			cout << "Fila " << i << " " << fila.size() << endl;
		}
		grafo.push_back(fila);
		fila.clear();
	}
	cout << "TAM GRAPH: " << grafo.size() << endl; 

    vector<Location> pru;

    auto start = high_resolution_clock::now(); // Marca de tiempo inicial
    pru = ThirdAprox(grafo);
    auto stop = high_resolution_clock::now(); // Marca de tiempo final

    auto transcurrido = duration_cast<duration<double>>(stop - start);
    cout << Customers.size() << "\t" << transcurrido.count() << endl;

	for(auto p : pru){
		cout << "(" << p.x << ", " << p.y << ")" << endl; 
	}
    //auto duration = duration_cast<seconds>(stop - start); // Cálculo de la duración en segundos
    //cout << "Tiempo de ejecución: " << duration.count() << " segundos." << endl;

    return 0;
}