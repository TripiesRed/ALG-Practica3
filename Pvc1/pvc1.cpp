#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Location
{
    int x, y;
    Location(int a, int b) : x(a), y(b) {}
    Location() : x(0), y(0) {}
    bool operator==(const Location& p) {
        return (p.x == x) && (p.y == y);
    }
};

// Dadas dos localizaciones, calcula la distancia.
double distance(Location A, Location B){
    
    double distancia_x = B.x - A.x;
    double distancia_y = B.y - A.y;
    double distancia = sqrt(pow(distancia_x, 2) + pow(distancia_y, 2));
    
    return distancia;
}

// Dado un vector de Locations y una Location, elimina las apariciones de Location del vector.
void eliminate(vector<Location>& v, const Location& l) {
    v.erase(find(v.begin(), v.end(), l));
}

// Dado un vector de Locations, busca la Location más cerca a otra Location suministrada.
Location closestLocation (Location A, vector<Location> v){

    Location closest = v[0];
    for (auto i : v) {
        if(distance(i, A) < distance(closest, A)){
            closest = i;
        }
    }

    return closest;
}

// Primera heurística. Elegimos la localización más cercana de donde nos encontremos.
vector<Location> FirstAprox(vector<Location> customers, Location company){

    vector<Location> path;
    path.push_back(company);

    while(!customers.empty()){
        Location c = closestLocation(path.back(), customers);
        path.push_back(c);
        eliminate(customers, c);
    }
    path.push_back(company);

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
    while (file >> x >> y) {
        Location customer(x, y);
        Customers.push_back(customer);
    }

    vector<Location> pru;

    auto start = high_resolution_clock::now(); // Marca de tiempo inicial
    pru = FirstAprox(Customers, Company);
    auto stop = high_resolution_clock::now(); // Marca de tiempo final

    auto transcurrido = duration_cast<duration<double>>(stop - start);
    cout << Customers.size() << "\t" << transcurrido.count() << endl;
    //auto duration = duration_cast<seconds>(stop - start); // Cálculo de la duración en segundos
    //cout << "Tiempo de ejecución: " << duration.count() << " segundos." << endl;

    return 0;
}