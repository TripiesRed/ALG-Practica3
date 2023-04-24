#include <iostream>
#include <fstream>
#include <random>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        std::cout << "Uso: " << argv[0] << " <número de líneas>\n";
        return 1;
    }
    int n = std::stoi(argv[1]);

    // Crear un generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-1000, 1000);

    // Crear un conjunto para evitar duplicados
    set<pair<int, int>> lines;

    // Generar n líneas aleatorias únicas
    while (lines.size() < n+1) {
        int a = dis(gen);
        int b = dis(gen);
        lines.insert({a, b});
    }

    // Escribir las líneas en el archivo
    ofstream file("Generador-pvc/data");
    for (const auto& [a, b] : lines) {
        file << a << " " << b << "\n";
    }
    file.close();

    return 0;
}
