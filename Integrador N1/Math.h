#ifndef MATH_H
#define MATH_H

#include <vector>

namespace Math {

    class Vector
    {
    public:
        static void Mostrar(std::vector<float> v);
        static float Distancia(std::vector<float> a, std::vector<float> b);
        static std::vector<float>* Mult(std::vector<float> v, std::vector<std::vector<float>> m);
    };

    class Matriz
    {
    public:
        static void Mostrar(std::vector<std::vector<float>> m);
        static void MostrarColumna(std::vector<std::vector<float>> m, int columna);
    };
}
#endif