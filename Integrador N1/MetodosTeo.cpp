#include "MetodosTeo.h"

#include <iostream>
#include <fstream>

namespace MetodosTeo
{
    bool ComprobarArgumentos(int argc, char* argv[], int& N)
    {
        bool rta = true;
        if (argc != 2 && argc != 3)
        {
            std::cout << "Cantidad de argumentos incorrectos!" << std::endl;
            return false;
        }

        std::ifstream archivo(argv[1]);

        if (!archivo.good())
        {
            std::cerr << "No se pudo abrir el archivo!" << std::endl;
            return false;
        }
        archivo.close();

        if (argc == 3)
        {
            char* end;
            N = std::strtol(argv[2], &end, 10);

            if (*end != '\0' && N <= 0)
            {
                std::cout << "N no es un numero valido." << std::endl;
                return false;
            }
        }
        else
        {
            N = -1;
        }

        return true;
    }

    void CargarArchivo(std::string url, std::vector<float>* vector, std::vector<std::vector<float>>* matriz)
    {
        std::ifstream archivo(url, std::ios::binary);
        char bit;

        int a, p = -1;

        if (!archivo) {
            std::cerr << "Error al intentar abrir el archivo." << std::endl;
        }

        while (archivo.get(bit)) {
            for (int i = 7; i >= 0; i--)
            {
                a = p;
                p = ((bit >> i) & 1);
                (*vector)[p]++;
                if (a != -1)
                {
                    (*matriz)[a][p]++;
                }
            }
        }
        archivo.close();
    }

	void AplicarProbabilidad(std::vector<std::vector<float>>* m, std::vector<float> a)
	{
		int f = m->size(), c = (*m)[0].size();

		for (int i = 0; i < f; i++)
		{
			for (int j = 0; j < c; j++)
			{
                (*m)[j][i] /= a[i];
			}
		}
	}
    void MostrarProbabilidades(std::vector<std::vector<float>> m)
    {
        int f = m.size(), c = m[0].size(), j;
        float promedio;

        std::cout << "  [";
        for (int i = 0; i < f; i++)
        {
            promedio = 0;
            for (j = 0; j < c; j++)
            {
                promedio += m[i][j];
            }
            std::cout << promedio / j;
            std::cout << ((i >= c - 1) ? "" : ", ");
        }
        std::cout << "]" << std::endl;
    }
    bool EsFuenteNula(std::vector<std::vector<float>> m)
    {
        int i, j = 0, filas = m.size(), size = m[0].size() - 1;
        bool fuenteNula = true;

        while (j < size && fuenteNula)
        {
            i = 0;
            while (i < filas && fuenteNula)
            {
                if (abs(m[i][j] - m[i][j + 1]) > TOLERACIA_FUENTE_NULA)
                {
                    fuenteNula = false;
                }
                i++;
            }
            j++;
        }

        return fuenteNula;
    }

    float CalcularEntropiaMemoriaNula(std::vector<std::vector<float>> distr)
    {
        int n = distr.size();

        int i, j;

        float entropia = 0.0f;

        for (i = 0; i < n; i++)
        {
            entropia += distr[i][0] * log2f(1.0 / distr[i][0]);
            /*for (j = 0; j < n; j++)
            {
                entropia += distr[i][0] * log2f(1.0 / distr[i][0]);
            }*/
        }

        return entropia;
    }
    float CalcularEntropiaOrdenN(std::vector<std::vector<float>> distr, int orden, bool mostrarSecuencia)
    {
        std::vector<int> contador(orden, 0);

        int n = distr.size();
        int cantidad = pow(n, orden);

        float entropia = 0.0f;

        int i, j;

        if (mostrarSecuencia)
        {
            std::cout << " Codigos\tProbabilidades" << std::endl;
        }

        for (i = 0; i < cantidad; i++)
        {
            float p = 1.0f;
            if (mostrarSecuencia)
            {
                std::cout << "  ";
            }
            for (j = 0; j < orden; j++)
            {
                p = p * distr[contador[j]][0];
                if (mostrarSecuencia)
                {
                    std::cout << contador[j];
                }
            }
            if (mostrarSecuencia)
            {
                std::cout << "\t\t " << p << std::endl;
            }
            j = orden - 1;
            while (j >= 0)
            {
                contador[j]++;
                if (contador[j] >= n)
                {
                    contador[j] = 0;
                }
                else
                {
                    j = 0;
                }
                j--;
            }
            entropia += p * log2f(1 / p);
        }

        contador.clear();
        return entropia;
    }
    float CalcularEntropiaMemoriaNoNula(std::vector<std::vector<float>> P, std::vector<float> V)
    {
        int n = P.size();

        int i, j;

        float entropia = 0.0f;

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                entropia += V[j] * P[i][j] * log2f(1.0 / P[i][j]);
            }
        }

        return entropia;
    }

    std::vector<float>* CalcularVectorEstacionario(std::vector<std::vector<float>> m)
    {
        int size = m.size();
        bool cond = true;

        int i;
        float maxTol = 1.0f;
        
        std::vector<float>* vectEst = new std::vector<float>(size);
        std::vector<float>* aux;

        for (i = 0; i < size; i++)
        {
            (*vectEst)[i] = 1.0f / size;
        }

        i = 0;
        while (i < MAX_ITERACIONES && cond)
        {
            aux = Math::Vector::Mult(*vectEst, m);
            if (Math::Vector::Distancia(*aux, *vectEst) <= TOLERACIA_ITERACIONES)
            {
                cond = false;
            }

            delete vectEst;
            vectEst = aux;

            i++;
        }

        return vectEst;
    }
}
