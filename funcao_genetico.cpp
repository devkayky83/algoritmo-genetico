#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
using namespace std;

vector<int> entradas = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
vector<int> saidas_esperadas = {6, 2, 0, 0, 2, 6, 12, 20, 30, 42, 56};

class Individuo {
public:
    double a, b, c;
    double erro;

    Individuo() {
        a = (rand() % 2001 - 1000) / 100.0;
        b = (rand() % 2001 - 1000) / 100.0;
        c = (rand() % 2001 - 1000) / 100.0;
        calcularErro();
    }

    void calcularErro() {
        erro = 0;
        for (size_t i = 0; i < entradas.size(); i++) {
            double x = entradas[i];
            double y = a * x * x + b * x + c;
            double e = y - saidas_esperadas[i];
            erro += e * e;
        }
    }

    static Individuo cruzar(const Individuo& p1, const Individuo& p2) {
        Individuo f;
        f.a = (p1.a + p2.a) / 2.0;
        f.b = (p1.b + p2.b) / 2.0;
        f.c = (p1.c + p2.c) / 2.0;
        f.mutar();
        f.calcularErro();
        return f;
    }

    void mutar(double taxa = 0.1) {
        if ((rand() % 100) < taxa * 100) a += ((rand() % 201 - 100) / 100.0);
        if ((rand() % 100) < taxa * 100) b += ((rand() % 201 - 100) / 100.0);
        if ((rand() % 100) < taxa * 100) c += ((rand() % 201 - 100) / 100.0);
    }

    void print() const {
        cout << "f(x) = " << a << "*x^2 + " << b << "*x + " << c;
        cout << " | Erro: " << erro << endl;
    }
};

int main() {
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    srand(time(0));

    const int populacaoTam = 30;
    const int geracoes = 5000;

    vector<Individuo> populacao;

    for (int i = 0; i < populacaoTam; i++) {
        populacao.push_back(Individuo());
    }

    Individuo melhor = populacao[0];

    for (int g = 0; g < geracoes; g++) {
        sort(populacao.begin(), populacao.end(), [](Individuo& a, Individuo& b) {
            return a.erro < b.erro;
        });

        if (populacao[0].erro < melhor.erro) {
            melhor = populacao[0];
            cout << "Geração " << g << " - Melhor: ";
            melhor.print();
        }

        vector<Individuo> novaGeracao;

        for (int i = 0; i < populacaoTam / 2; i++) {
            Individuo filho = Individuo::cruzar(populacao[i], populacao[i + 1]);
            novaGeracao.push_back(filho);
        }

        while (novaGeracao.size() < populacaoTam) {
            novaGeracao.push_back(Individuo());
        }

        populacao = novaGeracao;
    }

    cout << "\nMelhor função encontrada:\n";
    melhor.print();

    cout << "\nSaídas:\n";
    for (int v : saidas_esperadas) cout << v << " ";
    cout << endl;

    return 0;
}