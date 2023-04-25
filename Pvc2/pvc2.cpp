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
	return lhs.distancia < rhs.distancia;
}

// Dadas dos aristas, comprueba si están unidas por alguno de sus extremos
bool joined(Edge a, Edge b){
	return a.A == b.A || a.B == b.B || a.A == b.B || a.B == b.A;
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

	}

	return found;
}

// Segunda heurística.
vector<Edge> SecondAprox(vector<Location> locations){

    int n = locations.size();
    vector<Edge> edges, path;
    vector<pair<Location,int>> related;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.emplace_back(locations[i], locations[j]);
            
        }
        related.emplace_back(locations[i], 0);
    }
	
	//Ordenamos el vector de aristas de menor a mayor
    sort(edges.begin(), edges.end());
    path.push_back(edges[0]);

    //Recorremos el vector de aristas buscando la más corta tal que 
    // verifique las condiciones, para introducirla a la solución
	for(const auto e : edges){

		if(path.size() >= n)break;

        bool createsCycle = false;
        bool moreThanTwo = false;
        bool alreadyIn = false;

        // Comprueba si se crea un ciclo
		for (Edge t : path)
        {
            if (joined(t, e) && path.size() < n-1)
            {
                createsCycle = true;
                break;
            }
        }

        // Comprueba si una arista está ya en path 
        for (Edge t : path)
        {   
            Edge prueba(t.B, t.A);
            if (t == e || prueba == e)
            {
                alreadyIn = true;
                break;
            }
        }

        int degreeA = 0;
        int degreeB = 0;

        // Comprueba si un nodo de 
        for (Edge t : path)
        {
            if (t.A == e.A || t.B == e.A) degreeA++;
            if (t.A == e.B || t.B == e.B) degreeB++;
        }

        if (!createsCycle && !(degreeA > 2 || degreeB > 2) && !alreadyIn){
            path.push_back(e);
        }
        
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

    vector<Edge> pru;

    auto start = high_resolution_clock::now(); // Marca de tiempo inicial
    pru = SecondAprox(Customers);
    auto stop = high_resolution_clock::now(); // Marca de tiempo final

    auto transcurrido = duration_cast<duration<double>>(stop - start);
    cout << Customers.size() << "\t" << transcurrido.count() << endl;

    for(auto p : pru){
        cout << p.A.x << ", " << p.A.y << endl;
        cout << p.B.x << ", " << p.B.y << endl;
    }
    //auto duration = duration_cast<seconds>(stop - start); // Cálculo de la duración en segundos
    //cout << "Tiempo de ejecución: " << duration.count() << " segundos." << endl;

    return 0;
}
