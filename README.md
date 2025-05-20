# Algoritmo Genético de Minimização

Este código implementa um algoritmo genético em C++ para resolver problemas de **otimização**, com foco na **minimização de funções matemáticas**.

---

# Função a Ser Minimizada

$$
f(x_1, x_2) = 0{,}25x_1^4 - 3x_1^3 + 11x_1^2 - 13x_1 + 0{,}25x_2^4 - 3x_2^3 + 11x_2^2 - 13x_2
$$

## Metodologia

O algoritmo segue os seguintes passos:

1. **Criar população inicial** (aleatória)
2. Para cada geração:
   - a. Calcular **f(x)** para cada indivíduo
   - b. Selecionar os **melhores (pais)**
   - c. Realizar o **cruzamento** para gerar filhos
   - d. Aplicar **mutação** nos filhos
   - e. Formar a **nova população**
3. Exibir a **melhor solução final**

---

## Como Executar

### C++ - PowerShell (Windows)

```bash
g++ class.cpp -o class
./class.exe
