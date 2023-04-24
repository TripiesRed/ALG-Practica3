#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>

using namespace std;

struct Location
{
    int x, y;

	//Constructores
    Location(int a, int b) : x(a), y(b) {}
    Location() : x(0), y(0) {}

	//Operadores
    bool operator==(const Location& p) {
        return (p.x == x) && (p.y == y);
    }

	bool operator!=(const Location& p) {
        return (p.x != x) || (p.y != y);
    }
};

// Dadas dos localizaciones, calcula la distancia.
double calc_distance(Location A, Location B){
    
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
	Edge (Location a, Location b) : A(a), B(b) {
		distancia = calc_distance(A, B);
	}

	//Operadores
    bool operator<(const Edge& lhs, const Edge& rhs) {
    return rhs.distancia < lhs.distancia;
	}
};


int main() {
	
	priority_queue<Edge> v;
	
	Edge e1(Location(0,0), Location(1,1)), 
	     e2(Location(0,0), Location(2,2)), 
	     e3(Location(0,0), Location(1,1)), 
	     e4(Location(0,0), Location(3,3)), 
	     e5(Location(0,0), Location(2,0));
	
	v.push(e1);
	v.push(e2);
	v.push(e3);
	v.push(e4);
	v.push(e5);
	
	while(!v.empty()){
		cout << v.top().distancia << endl;
		v.pop();
	}
	
	return 0;
}


