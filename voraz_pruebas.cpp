
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;



vector<vector<float>> VorazCatering (vector<float> comensales, int c){

    float totalTime = 0;

    for(int i = 0; i < comensales.size(); i++)
        totalTime += comensales[i];
    
    //Tiempo ideal que debería tardar cada camarero
    float maxTimeEach = totalTime / c; 

    //Ordenamos el vector de comensales en orden creciente
    sort(comensales.begin(), comensales.end());

    vector<vector<float>> camareros;
    vector<float> camareroIesimo;
    vector<float> times2;
    float contador = 0;
    int comensalIesimo = 0;

    //Asignamos a cada camarero los comensales que le corresponden
    // siempre y cuando el tiempo total que tarda el camarero en atenderlos
    // a todos no supere maxTimeEach
    for(int i = 0; i < c; i++){

        while(contador < maxTimeEach && comensalIesimo < comensales.size()){

            camareroIesimo.push_back(comensales[comensalIesimo]);
            contador += comensales[comensalIesimo];
            comensalIesimo++;
        }
        
        camareros.push_back(camareroIesimo);
        times2.push_back(contador);
        contador = 0;
        camareroIesimo.clear();

    }

    cout << "Tiempos: " << times2[0] << " " << times2[1] << " "
         << times2[2] << " " << endl;

    return camareros;
}




int main(){

    vector<int>c1, c2, c3;
    vector<vector<int>> camareros;
    vector<float> comensales2;

    camareros.push_back(c1);
    camareros.push_back(c2);
    camareros.push_back(c3);

    priority_queue<int, vector<int>, greater<int>> comensales;
    float time = 0;
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1, 300);
    int comensal;

    for (int i = 0; i < 10000; i++)
    {   
        comensal = distribution(generator);
        comensales.push(comensal);
        comensales2.push_back(comensal);
        time += comensal;
    }

    float maxTimeEach = time / camareros.size();
    int cont = 0, comensalIesimo = 0;
    vector<int> times;

    for (int i = 0; i < camareros.size(); i++)
    {

        while (cont <= maxTimeEach && comensales.size() > 0)
        {
            comensal = comensales.top();
            camareros[i].push_back(comensal);
            cont += comensal;
            comensales.pop();
        }

        times.push_back(cont);

        cont = 0;
    }

    cout << "Maximo Tiempo: " << maxTimeEach << endl;   

    cout << "\nTamanios: " << camareros[0].size() << " " << camareros[1].size() << " "
         << camareros[2].size() << " " << endl;

    cout << "TiemposU: " << times[0] << " " << times[1] << " "
         << times[2] << " " << endl;
    

    vector<vector<float>> camareros2 = VorazCatering(comensales2, camareros.size());

    cout << "\nTamanios: " << camareros2[0].size() << " " << camareros2[1].size() << " "
         << camareros2[2].size() << " " << endl;
    

    return 0;
}