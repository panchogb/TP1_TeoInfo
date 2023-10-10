#include <iostream>

#include "MetodosTeo.h"
#include "Math.h"

int LeerArchivo(char *url, int N)
{
    const int size = 2;

    std::vector<float> alfabeto(size, 0);
    std::vector<float>* estacionario;
    std::vector<std::vector<float>> matrizPasaje(size, std::vector<float>(size, 0));
    float entropia;

    MetodosTeo::CargarArchivo(url, &alfabeto, &matrizPasaje);

    std::cout << std::endl << "-Matriz de transaccion de estados:" << std::endl;
    MetodosTeo::AplicarProbabilidad(&matrizPasaje, alfabeto);
    Math::Matriz::Mostrar(matrizPasaje);
    std::cout << std::endl << "-Entropia:" << MetodosTeo::CalcularEntropia(matrizPasaje, 1, false) << std::endl;

    if (MetodosTeo::EsFuenteNula(matrizPasaje))
    {
        std::cout << std::endl << "*** Fuente Nula ***" << std::endl;

        std::cout << std::endl << "-Probabilidades: " << std::endl;
        MetodosTeo::MostrarProbabilidades(matrizPasaje);
        if (N > 0)
        {
            entropia = MetodosTeo::CalcularEntropia(matrizPasaje, N, true);
            std::cout << std::endl << "-Entropia de la extension de orden N=" << N << " :" << entropia << std::endl;
        }
    }
    else
    {
        std::cout << std::endl << "*** Fuente no nula ***" << std::endl;
        estacionario = MetodosTeo::CalcularVectorEstacionario(matrizPasaje);
        std::cout << std::endl << "-Vector Estacionario: " << std::endl;
        Math::Vector::Mostrar(*estacionario);
        delete estacionario;
    }

    alfabeto.clear();
    matrizPasaje.clear();
    return 1;
}

int main(int argc, char* argv[])
{
    int N;
    argc = 3;
    argv = (char**)malloc(argc * sizeof(char*));

    // Asignar memoria para las cadenas y copiar los valores
    argv[0] = _strdup("tpi1");
    argv[1] = _strdup("../tp1_samples/tp1_sample0.bin");
    argv[2] = _strdup("3");
    //argv[2] = _strdup("2");

    if (MetodosTeo::ComprobarArgumentos(argc, argv, N))
    {
        LeerArchivo(argv[1], N);
    }
    /*else
    {
        char url[] = "../tp1_samples/tp1_sample9.bin";
        LeerArchivo(url, 5);
    }*/
}