#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <chrono>
#include <set>

using namespace std;
using namespace std::chrono;


struct Location
{
    int x;
    int y;
    bool operator==(const Location& p) {
        return (p.x == x) && (p.y == y);
    }
    bool operator<(const Location &other) const        // Sobrecargamos el operador < con la semántica siguiente:
    {                                               // un punto p1 es menor que otro punto p2 si p1 está mas abajo,
        if (y != other.y)                           // es decir, tiene componente y menor. En caso de empate, 
        {                                           // se escoge el que esté más a la izquierda (componente x menor).
            return y < other.y;
        }
        else
        {
            return x < other.x;
        }
    }
    bool operator!=(const Location &other) const       // Sobrecargamos el operador !=
    {

        return ((x != other.x) || (y != other.y));
    }
    Location(int a, int b) : x(a), y(b) {}
    Location() : x(0), y(0) {}
};

enum Orientation{
    ALIGNED,
    CLOCKWISE,
    COUNTERCLOCKWISE
};

// Dado un vector de puntos, devuelve el menor punto (ver sobrecarga operador <).
Location FirstLocation(vector<Location> &v)
{
    Location first_p = *min_element(v.begin(), v.end());
    return first_p;
}

// Devuelve la orientación relativa entre 3 puntos. Devuelve un valor del tipo de dato enumerado Orientation.
Orientation orientation(const Location p, const Location q, const Location r)
{
    int val = (q.y - p.y) * (r.x - q.x) -               // Para evitar el cálculo del ángulo, podemos hallar el
              (q.x - p.x) * (r.y - q.y);                // producto vectorial de los dos vectores que se definen.

    if (val == 0)
    {

        return ALIGNED;                                  // Puntos alineados
    }
    else
    {

        return (val > 0) ? CLOCKWISE : COUNTERCLOCKWISE; // Sentido horario o antihorario
    }
}

// Devuelve la distancia entre dos puntos.
double distance(Location a, Location b)
{
    int x_c = b.x - a.x;
    int y_c = b.y - a.y;
    return sqrt(x_c * x_c + y_c * y_c);
}

// Compara dos puntos según el ángulo que forman el eje horizontal y la recta que pasa por
// cada punto y un punto fijo (p0).
int compare_by_orientation(Location p1, Location p2, Location p0)
{

    Orientation o = orientation(p0, p1, p2);          // Hallamos la orientación de los puntos.
    if (o == ALIGNED)
    {
        // Si los puntos están alineados, devuelve el que está más lejos del punto de referencia
        if (distance(p0, p2) >= distance(p0, p1))
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        // Si los puntos no están en la misma línea, devuelve el que está a la izquierda en relación al punto de referencia
        if (o == COUNTERCLOCKWISE)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
}

// Ordena un vector según la función anterior.
void sort_by_orientation(vector<Location> &Locations, const Location &P)
{

    sort(Locations.begin(), Locations.end(), [&](const Location &p1, const Location &p2)
                                        { return compare_by_orientation(p1, p2, P) < 0; });
}

// Calcula el polígono convexo que contine a todos los puntos de un vector.
vector<Location> Convex_Polygon(vector<Location> &Locations)
{

    if (Locations.size() <= 3) {               // Si hay menos de tres puntos, devolvemos el mismo vector.
        return Locations;
    }

    vector<Location> aux;                      // Vector auxiliar
    Location p0 = FirstLocation(Locations);          // Hallamos el punto más abajo (más a la izquierda en caso de empate)

    for (int i = 0; i < Locations.size(); i++) // Copiamos los demás puntos en el vector auxiliar
    {
        if (Locations[i] != p0)
        {
            aux.push_back(Locations[i]);
        }
    }

    sort_by_orientation(aux, p0);           // Ordenamos según el ángulo que forme cada punto con el punto de referencia

    aux.insert(aux.begin(), p0);            // Colocamos p0 en la primera posición

    vector<Location> convex_polygon;           // Vector con los puntos que forman el polígono convexo

    convex_polygon.push_back(aux[0]);       // Añadimos los tres primeros puntos del vector auxiliar
    convex_polygon.push_back(aux[1]);
    convex_polygon.push_back(aux[2]);

    for (int i = 3; i < aux.size(); i++)    // Para el resto del vector
    {
        // Si el ángulo que forman los puntos aux[i] y los dos últimos ángulos de convex_polygon
        // hace un giro en sentido horario o los puntos están alineados, eliminamos el último elemento de 
        // convex_polygon.

        while (orientation(convex_polygon[convex_polygon.size() - 2], convex_polygon.back(), aux[i]) != 2){
            
            convex_polygon.pop_back();
        }
        convex_polygon.push_back(aux[i]);
    }

    return convex_polygon;
}


// Dado un vector de Locations y una Location, elimina las apariciones de Location del vector.
void eliminate(vector<Location>& v, const Location& l) {
    v.erase(remove(v.begin(), v.end(), l), v.end());
}

// Dado dos vectores de Locations, elimina del primero las apariciones de los elementos del segundo.
void eliminateVector(vector<Location>& v, vector<Location>& e) {
    for(int i = 0; i< e.size(); i++){
        v.erase(remove(v.begin(), v.end(), e[i]), v.end());
    }
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

// Tercera heurística
vector<Location> SecondAprox(vector<Location> &v){

    vector<Location> convex_polygon = Convex_Polygon(v);
    vector<Location> result;
    result = convex_polygon;

    // Eliminamos de v los lementos que ya tenemos procesados
    eliminateVector(v, convex_polygon);

    // Mientras queden elementos, aplicamos la primera heurística
    while(!v.empty()){
        Location c = closestLocation(result.back(), v);
        result.push_back(c);
        eliminate(v, c);
    }

    return result;
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

    vector<Location> proof;

    auto start = high_resolution_clock::now(); // Marca de tiempo inicial
    proof = SecondAprox(Customers);
    auto stop = high_resolution_clock::now(); // Marca de tiempo final

    auto duration = duration_cast<seconds>(stop - start); // Cálculo de la duración en segundos
    cout << "Tiempo de ejecución: " << duration.count() << " segundos." << endl;

    return 0;
}