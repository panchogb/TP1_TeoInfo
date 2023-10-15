#ifndef METODOSTEO_H
#define METODOSTEO_H

#include "Math.h"
#include <iostream>

namespace MetodosTeo
{
	const float TOLERACIA_FUENTE_NULA = 0.01f;

	const int MAX_ITERACIONES = 2000;
	const float TOLERACIA_ITERACIONES = 0.001f;


	bool ComprobarArgumentos(int argc, char* argv[], int& N);
	void CargarArchivo(std::string url, std::vector<float>* vector, std::vector<std::vector<float>>* matriz);

	void AplicarProbabilidad(std::vector<std::vector<float>>* m, std::vector<float> a);
	void MostrarProbabilidades(std::vector<std::vector<float>> m);
	bool EsFuenteNula(std::vector<std::vector<float>> m);
	float CalcularEntropiaMemoriaNula(std::vector<std::vector<float>> distr);
	float CalcularEntropiaOrdenN(std::vector<std::vector<float>> distr, int orden, bool mostrarSecuencia);
	float CalcularEntropiaMemoriaNoNula(std::vector<std::vector<float>> P, std::vector<float> V);

	std::vector<float>* CalcularVectorEstacionario(std::vector<std::vector<float>> m);
}

#endif

