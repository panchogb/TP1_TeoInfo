#include "Math.h"

#include <iostream>
#include <iomanip>

namespace Math {

#pragma region Vector
    void Vector::Mostrar(std::vector<float> v)
    {
        int size = v.size();
        std::cout << "  [";
        for (int i = 0; i < size; i++)
        {
            std::cout << std::fixed;
            std::cout << std::setprecision(4);
            std::cout << v[i];
            std::cout << ((i >= size - 1) ? "" : ", ");
        }
        std::cout << "]" << std::endl;
    }

    float  Vector::Distancia(std::vector<float> a, std::vector<float> b)
    {
        int size = a.size();
        float dist = 0.0f;
        for (int i = 0; i < size; i++)
        {
            dist += powf(a[i] - b[i], 2.0f);
        }
        return sqrtf(dist);
    }
    std::vector<float>* Vector::Mult(std::vector<float> v, std::vector<std::vector<float>> m)
    {
        std::vector<float>* nv = new std::vector<float>(v.size(), 0);

        int f = m.size(), c = m[0].size();

        for (int i = 0; i < f; i++)
        {
            for (int j = 0; j < c; j++)
            {
                (*nv)[i] += m[i][j] * v[j];
            }
        }

        return nv;
    }
#pragma endregion

#pragma region Matriz
    void Matriz::Mostrar(std::vector<std::vector<float>> m)
    {
        int sizeF = m.size(), sizeC = m[0].size();
        for (int i = 0; i < sizeF; i++)
        {
            std::cout << "  [";
            for (int j = 0; j < sizeC; j++)
            {
                std::cout << std::fixed;
                std::cout << std::setprecision(4);
                std::cout << m[i][j];
                std::cout << ((j >= sizeC - 1) ? "" : ", ");
            }
            std::cout << "]" << std::endl;
        }
    }
    void Matriz::MostrarColumna(std::vector<std::vector<float>> m, int columna)
    {
        int sizeF = m.size(), sizeC = m[0].size();

        std::cout << "  [";
        for (int i = 0; i < sizeF; i++)
        {
            std::cout << std::fixed;
            std::cout << std::setprecision(4);
            std::cout << m[i][columna];
            std::cout << ((i >= sizeF - 1) ? "" : ", ");
        }
        std::cout << "]" << std::endl;
    }
#pragma endregion
}