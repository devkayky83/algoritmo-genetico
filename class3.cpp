#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <utility>
using namespace std;
class Individuo
{
public:
    vector<int> cromossomo;
    double x1, x2;
    int tamanho;

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
            if ((rand() % 100) < (taxa * 100.0))
            {
                cromossomo[i] = 1 - cromossomo[i];
            }
        }
    }

    static pair<Individuo, Individuo> cruzamento(const Individuo &pai1, const Individuo &pai2)
    {
        int pontoCorte = rand() % pai1.tamanho;
        Individuo filho1(pai1.tamanho);
        Individuo filho2(pai2.tamanho);

        filho1.cromossomo = pai1.cromossomo;
        filho2.cromossomo = pai2.cromossomo;

        for (int i = pontoCorte; i < pai1.tamanho; i++)
        {
            swap(filho1.cromossomo[i], filho2.cromossomo[i]);
        }

        return {filho1, filho2};
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
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int tamanho;

    cout << "Digite o tamanho do vetor: ";
    cin >> tamanho;

    // if (tamanho % 2 != 0)
    // {
    //     cout << "O tamanho deve ser par para dividir em x1 e x2.\n";
    //     return 1;
    // }

    double taxaMutacao = 0.05;
    int populacaoTamanho = 10;
    int maxGeracoes = 1000;
    bool mostrarIndividuos = false;
    bool mostrarFilhos = false;

    vector<Individuo> populacao;

    for (int i = 0; i < populacaoTamanho; i++)
    {
        Individuo ind(tamanho);
        ind.gerarIndividuo();
        
        if (mostrarIndividuos)
        {
            cout << "Indivíduo " << i + 1 << " gerado:\n";
            ind.mostrarResultado();
            cout << "------------------------\n";
        }
        populacao.push_back(ind);
    }

    Individuo melhor = populacao[0];
    double melhorFx = melhor.calcularFx();

    for (int geracao = 1; geracao <= maxGeracoes; geracao++)
    {
        for (int i = 0; i < populacaoTamanho / 2; i++)
        {
            int idx1 = rand() % populacaoTamanho;
            int idx2 = rand() % populacaoTamanho;

            auto filhos = Individuo::cruzamento(populacao[idx1], populacao[idx2]);

            filhos.first.mutacao(taxaMutacao);
            filhos.second.mutacao(taxaMutacao);

            if (mostrarFilhos)
            {
                cout << "\nFilho 1 gerado: ";
                filhos.first.mostrarResultado();
                cout << "\nFilho 2 gerado: ";
                filhos.second.mostrarResultado();
            }

            double fx1 = filhos.first.calcularFx();
            double fx2 = filhos.second.calcularFx();

            if (fx1 < melhorFx)
            {
                melhor = filhos.first;
                melhorFx = fx1;
                cout << "Geração" << geracao << ": Nova melhor solução - f(x1,x2): " << melhorFx << "\n";
            }

            if (fx2 < melhorFx)
            {
                melhor = filhos.second;
                melhorFx = fx2;
                cout << "Geração" << geracao << ": Nova melhor solução - f(x1,x2): " << melhorFx << "\n";
            }

            populacao[idx1] = filhos.first;
            populacao[idx2] = filhos.second;
        }
    }

    cout << "\nMelhor solução encontrada:\n";
    melhor.mostrarResultado();

    return 0;
}
