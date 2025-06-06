#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <windows.h>
using namespace std;

const vector<int> moedas = {50, 20, 11, 5, 1}; 
const int TAMANHO_POP = 50;
const int MAX_GERACOES = 1000;
const double TAXA_MUTACAO = 0.1;

struct Individuo {
    vector<int> genes; // quantidade de cada moeda
    int nota; // menos moedas = melhor
    int valorTotal;

    Individuo() {
        genes.resize(moedas.size());
        for (int &g : genes)
            g = rand() % 6; // número aleatório de moedas de 0 a 5
        avaliarNota();
    }

    void avaliarNota(int alvo = -1) {
        valorTotal = 0;
        for (size_t i = 0; i < moedas.size(); i++) {
            valorTotal += genes[i] * moedas[i];
        }

        if (alvo == -1)
            return;

        if (valorTotal == alvo)
            nota = totalMoedas(); // quanto menos moedas, melhor
        else
            nota = 9999; // penalidade para soluções inválidas,
                         // significa que nunca será escolhido como o melhor se cair aqui
    }

    int totalMoedas() const {
        int soma = 0;
        for (int g : genes) soma += g;
        return soma;
    }
};

Individuo cruzamento(const Individuo &pai1, const Individuo &pai2) {
    Individuo filho;
    for (size_t i = 0; i < moedas.size(); i++) {
        filho.genes[i] = (rand() % 2) ? pai1.genes[i] : pai2.genes[i];
    }
    return filho;
}

void mutacao(Individuo &ind) {
    for (size_t i = 0; i < moedas.size(); i++) {
        if ((rand() % 100) < (TAXA_MUTACAO * 100)) {
            ind.genes[i] = rand() % 6;
        }
    }
}

// Percorre da moeda maior para a menor e pega o máximo possível de cada, sem garantir melhor caminho.
// void metodoGuloso(int valor) {
//     vector<int> resultado(moedas.size(), 0);
//     cout << "\nMétodo Guloso:\n";

//     int restante = valor;
//     for (size_t i = 0; i < moedas.size(); i++) {
//         resultado[i] = restante / moedas[i];
//         restante %= moedas[i];
//     }

//     int totalMoedas = 0;
//     for (size_t i = 0; i < resultado.size(); i++) {
//         if (resultado[i] > 0) {
//             cout << resultado[i] << " moeda(s) de " << moedas[i] << " centavos\n";
//             totalMoedas += resultado[i];
//         }
//     }
//     cout << "Total de moedas (guloso): " << totalMoedas << "\n";
// }

int main() {
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    srand(time(NULL));
    int valor;

    cout << "\nDigite o valor do troco (ex: 260 para R$2,60): ";
    cin >> valor;

    // metodoGuloso(valor);

// ---------------------------------------------------------------------------

    // Algoritmo Genético
    vector<Individuo> populacao(TAMANHO_POP);
    Individuo melhor;
    melhor.nota = 9999;

    for (int geracao = 0; geracao < MAX_GERACOES; geracao++) {
        for (Individuo &ind : populacao) {
            ind.avaliarNota(valor);
            if (ind.nota < melhor.nota) {
                melhor = ind;
            }
        }

        vector<Individuo> novaPopulacao;
        while (novaPopulacao.size() < TAMANHO_POP) {
            int idx1 = rand() % TAMANHO_POP;
            int idx2 = rand() % TAMANHO_POP;
            Individuo filho = cruzamento(populacao[idx1], populacao[idx2]);
            mutacao(filho);
            filho.avaliarNota(valor);
            novaPopulacao.push_back(filho);
        }
        populacao = novaPopulacao;
    }

    cout << "\nMelhor solução encontrada:\n";
    for (size_t i = 0; i < moedas.size(); i++) {
        if (melhor.genes[i] > 0) {
            cout << melhor.genes[i] << " moeda(s) de " << moedas[i] << " centavos\n";
        }
    }

    cout << "Total de moedas: " << melhor.totalMoedas() << "\n";
    return 0;
}
