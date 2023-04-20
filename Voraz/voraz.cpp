#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;


/*
 ->Algoritmo Voraz encargado de resolver el Problema 1: Servicio de Catering

    Recibe los siguientes parámetros:
        -comensales (vector<float>): Un vector con los tiempos que tarda un camarero 
        en llegar a la mesa del comensal desde cocina.
        -c (int): Indica el número total de camareros en servicio
    
    Devuelve: Un vector de vectores de tipo float, donde cada vector representa
    un camarero con los comensales que les han sido asignados.
    
*/
vector<vector<float>> VorazCatering (vector<float> comensales, int c){

    float totalTime = 0;

    for(int i = 0; i < comensales.size(); i++)
        totalTime += comensales[i];
    
    //Tiempo ideal que debería tardar cada camarero
    float maxTimeEach = totalTime / c; 

    //Ordenamos el vector de comensales en orden creciente
    sort(comensales.begin(), comensales.end());

    vector<vector<float>> camareros; //Vector de camareros
    vector<float> camareroIesimo; //Vector de comensales asignados a un camarero 
    //Auxiliar para calcular el tiempo que tarda cada camarero
    //float contador = 0;
    //vector<float> times; 
    

    //Asignamos a cada camarero los comensales que le corresponden
    // siempre y cuando el tiempo total que tarda el camarero en atenderlos
    // a todos no supere maxTimeEach
    for(int i = 0; i < c; i++){

        for(int j = i; j < comensales.size(); j += c){

            camareroIesimo.push_back(comensales[j]);
            //contador += comensales[j];

        }

        camareros.push_back(camareroIesimo); //Añadimos el camarero          
        camareroIesimo.clear(); //Borramos para inicializar un nuevo camarero
        //times.push_back(contador); 
        //contador = 0; 
        

    }

    //Muestra los tiempos que tarda cada camarero
    /*
    cout << "Timepos: " << endl;
    for(int i = 0; i < times.size(); i++)
        cout << times[i] << " ";
    */

    return camareros;
}

int main (int argc, char** argv) {
    
    // Comprobamos que se ha pasado un argumento con la ruta del fichero
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <n_camareros> " << " <fichero_entrada> " 
             << " <fichero_salida> " << endl;
        return 1;
    }
    
    vector<float> comensales;
    string line;
    int ncamareros = stoi(argv[1]); // Leemos número de camareros

    //ENTRADA DEL PROBLEMA

    // Abrimos el fichero
    ifstream file(argv[2]);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el fichero" << endl;
        return 1;
    }

    // Leemos el fichero línea a línea 
    while (getline(file, line)) {

        // Parseamos la línea para obtener el tiempo del comensal
        istringstream iss(line);
        float comensal;
        if (!(iss >> comensal)) {
            cerr << "Error al leer el fichero" << endl;
            return 1;
        }

        // Lo añadimos al vector
        comensales.push_back(comensal);
    }
	
	// Cerramos el fichero
    file.close();

    //Comprobamos si los datos recibidos son correctos
    if(!(ncamareros < comensales.size())){
        cerr << "Error en los datos: " << endl;
        cerr << "Numero camareros mayor al de comensales " << endl;
        return 1;
    }
    
    //CÁLCULO DEL TIEMPO EMPÍRICO

    //Inicializamos las variables para calcular el tiempo que tarda el algoritmo
    high_resolution_clock::time_point t_antes, t_despues;
	duration<double> transcurrido;
    
    //Pasamos los datos del vector y calculamos el tiempo que tarda
    t_antes = high_resolution_clock::now();
    vector<vector<float>> sol = VorazCatering(comensales, ncamareros);
    t_despues = high_resolution_clock::now();
    
    transcurrido = duration_cast<duration<double>>(t_despues - t_antes);
    cout << comensales.size() << "\t" << ncamareros << "\t" 
         << transcurrido.count() << endl;
    

    //SALIDA DEL PROGRAMA (Solución al Problema)

    //Abrimos el fichero de salida
    ofstream ofile(argv[2]);
    
    if (!ofile.is_open()) {
        cerr << "No se pudo abrir el fichero de salida" << endl;
        return 1;
    }
    
    float time = 0;
    vector<float> allTimes;
    for(int i = 0; i < sol.size(); i++){

        for(int j = 0; j < sol[i].size(); j++)
            time += sol[i][j];

        line = "Tiempo de servicio Camarero " + to_string(i) + ":" + to_string(time) + " s\n";
        ofile << line;
        allTimes.push_back(time);
        time = 0;
    }
    
    //Cerramos el fichero
    ofile.close();

    


    return 0;
}