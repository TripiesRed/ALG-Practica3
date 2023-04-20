#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    // Verificar que se haya pasado un argumento para el número de líneas
    if (argc != 3)
    {
        cout << "Uso: " << argv[0] << " <numero de lineas> " << "<nombre del fichero>" << endl;
        return 1;
    }

    // Convertir el argumento a un entero
    int num_lines = atoi(argv[1]);
    string file_name = argv[2];

    // Inicializar la semilla aleatoria con la hora actual
    srand(time(nullptr));

    // Abrir el archivo para escribir
    ofstream file(file_name, ios::trunc);

    // Generar el número de líneas especificado con dos números aleatorios tipo float en cada línea
    for (int i = 0; i < num_lines; i++)
    {
        std::random_device rd; // Genera una semilla aleatoria
        std::mt19937 gen(rd()); // Generador de números aleatorios
        std::uniform_int_distribution<> dis(1, 10000); // Distribución uniforme entre -100 y 100

        int num1 = dis(gen);

        if(i == num_lines - 1){
            file << num1;
        }
        else{
            file << num1 << "\n";
        }
    }

    // Cerrar el archivo
    file.close();

    return 0;
}
