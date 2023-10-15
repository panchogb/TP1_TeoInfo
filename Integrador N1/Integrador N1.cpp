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

    std::cout << std::endl << "-Matriz de transicion de estados:" << std::endl;
    MetodosTeo::AplicarProbabilidad(&matrizPasaje, alfabeto);
    Math::Matriz::Mostrar(matrizPasaje);

    if (MetodosTeo::EsFuenteNula(matrizPasaje))
    {
        std::cout << std::endl << "*** Fuente Nula ***" << std::endl;

        std::cout << std::endl << "-Probabilidades: ";
        MetodosTeo::MostrarProbabilidades(matrizPasaje);
        if (N > 0)
        {
            entropia = MetodosTeo::CalcularEntropiaOrdenN(matrizPasaje, N, true);
            std::cout << std::endl << "-Entropia de memoria nula: " << MetodosTeo::CalcularEntropiaMemoriaNula(matrizPasaje) << std::endl;
            std::cout << std::endl << "-Entropia de extension de orden N=" << N << " :" << entropia << std::endl;
        }
    }
    else
    {
        std::cout << std::endl << "*** Fuente no nula ***" << std::endl;
        estacionario = MetodosTeo::CalcularVectorEstacionario(matrizPasaje);
        std::cout << std::endl << "-Vector Estacionario: ";
        Math::Vector::Mostrar(*estacionario);
        std::cout << std::endl << "-Entropia de memoria no nula: " << MetodosTeo::CalcularEntropiaMemoriaNoNula(matrizPasaje, *estacionario) << std::endl;
        delete estacionario;
    }

    alfabeto.clear();
    matrizPasaje.clear();
    return 1;
}

int main(int argc, char* argv[])
{
    int N;

    if (MetodosTeo::ComprobarArgumentos(argc, argv, N))
    {
        LeerArchivo(argv[1], N);
    }
    /*else
    {
        char url[] = "../tp1_samples/tp1_sample0.bin";
        LeerArchivo(url, 2);
    }*/
}