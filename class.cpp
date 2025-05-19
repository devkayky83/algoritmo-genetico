#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

class Individuo
{
public:
    int cromossomo[10];
    double x1, x2;
    double fx;

    Individuo();
    void GerarIndividuo();
    int CalcularDecimalX1();
    int CalcularDecimalX2();
    void NormalizarX1();
    void NormalizarX2();
    void CalcularFx();
    void Mutacao();
};

void Individuo::GerarIndividuo()
{
    for (int i = 0; i < 10; i++)
    {
        this->cromossomo[i] = rand() % 2;
    }
}

int Individuo::CalcularDecimalX1()
{
    int decimal = 0;
    for (int i = 0; i < 5; i++)
    {
        decimal += this->cromossomo[i] * pow(2, 4 - i);
    }
    return decimal;
}

int Individuo::CalcularDecimalX2()
{
    int decimal = 0;
    for (int i = 5; i < 10; i++)
    {
        decimal += this->cromossomo[i] * pow(2, 9 - i);
    }
    return decimal;
}

void Individuo::NormalizarX1()
{
    x1 = CalcularDecimalX1() * 6.0 / 31.0;
}

void Individuo::NormalizarX2()
{
    x2 = CalcularDecimalX2() * 6.0 / 31.0;
}

void Individuo::CalcularFx()
{
    NormalizarX1();
    NormalizarX2();

    fx = 0.25 * pow(x1, 4) - 3 * pow(x1, 3) + 11 * pow(x1, 2) - 13 * x1 +
         0.25 * pow(x2, 4) - 3 * pow(x2, 3) + 11 * pow(x2, 2) - 13 * x2;
}

void Individuo::Mutacao()
{
    int posicao = rand() % 10;
    this->cromossomo[posicao] = !this->cromossomo[posicao];
}

Individuo::Individuo()
{
    GerarIndividuo();
    CalcularFx();
}

int main()
{
    srand(time(0));
    Individuo ind;

    cout << "x1 = " << ind.x1 << "\n";
    cout << "x2 = " << ind.x2 << "\n";
    cout << "fx = " << ind.fx << "\n";

    return 0;
}
