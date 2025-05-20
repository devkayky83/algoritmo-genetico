#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
using namespace std;
class Individuo
{
private:
    vector<int> cromossomo;
    double x1, x2;
    int tamanho;

public:
    Individuo(int tamanho)
    {
        this->tamanho = tamanho;
        cromossomo.resize(tamanho);
    }

    void gerarIndividuo()
    {
        for (int i = 0; i < tamanho; i++)
        {
            cromossomo[i] = rand() % 2;
        }
    }

    int calcularDecimalX1()
    {
        int decimal = 0;

        for (int i = 0; i < tamanho / 2; i++)
        {
            decimal = decimal * 2 + cromossomo[i];
        }
        return decimal;
    }

    int calcularDecimalX2()
    {
        int decimal = 0;

        for (int i = tamanho / 2; i < tamanho; i++)
        {
            decimal = decimal * 2 + cromossomo[i];
        }
        return decimal;
    }

    double normalizarX1()
    {
        int decimalX1 = calcularDecimalX1();
        x1 = decimalX1 * (6.0 / ((pow(2, tamanho / 2)) - 1));

        return x1;
    }

    double normalizarX2()
    {
        int decimalX2 = calcularDecimalX2();
        x2 = decimalX2 * (6.0 / ((pow(2, tamanho / 2)) - 1));

        return x2;
    }

    double calcularFx()
    {
        normalizarX1();
        normalizarX2();

        double fx1 = 0.25 * pow(x1, 4) - 3 * pow(x1, 3) + 11 * pow(x1, 2) - 13 * x1;
        double fx2 = 0.25 * pow(x2, 4) - 3 * pow(x2, 3) + 11 * pow(x2, 2) - 13 * x2;

        return fx1 + fx2;
    }

    void mutacao(double taxa)
    {
        for (int i = 0; i < tamanho; i++)
        {
            double chance = (rand() % 100) / 100.0;

            if (chance < taxa)
            {
                cromossomo[i] = 1 - cromossomo[i];
            }
        }
    }

    void mostrarResultado()
    {
        cout << "Cromossomo: ";
        for (int bit : cromossomo)
            cout << bit;

        cout << "\nx1 = " << x1 << ", x2 = " << x2;
        cout << "\nf(x1, x2) = " << calcularFx() << "\n";
    }
};

int main()
{
    int tamanho;

    cout << "Digite o tamanho do vetor: ";
    cin >> tamanho;

    if (tamanho % 2 != 0)
    {
        cout << "O tamanho deve ser par para dividir em x1 e x2.\n";
        return 1;
    }

    Individuo ind(tamanho);
    ind.gerarIndividuo();
    ind.calcularFx();
    ind.mostrarResultado();

    return 0;
}
