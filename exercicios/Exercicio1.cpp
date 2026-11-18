// Exercício 1: Validação de Árvore Binária de Busca
// Adaptado de LeetCode 98 (Validate Binary Search Tree)
//
// Entrada:
//   Linha 1: quantidade de nós (N)
//   Próximas N linhas: valor indiceDoFilhoEsquerdo indiceDoFilhoDireito
//   (os índices começam em 0, o nó 0 é a raiz, e -1 significa "sem filho")
// Saída:
//   True se a árvore for uma BST válida, False caso contrário.

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct NoArvore {
    int valor;
    NoArvore* esquerda;
    NoArvore* direita;
};

// Função recursiva que carrega o intervalo de valores permitido para o nó.
// O valor do nó precisa estar ESTRITAMENTE entre limiteInferior e limiteSuperior.
// Usamos long long porque os valores dos nós podem ser INT_MIN ou INT_MAX,
// e os limites iniciais precisam ficar "fora" dessa faixa.
bool validarSubarvore(NoArvore* no, long long limiteInferior, long long limiteSuperior) {
    // Um nó que não existe é considerado válido (caso base da recursão).
    if (no == nullptr) {
        return true;
    }

    // O valor do nó atual precisa respeitar as fronteiras impostas pelos ancestrais.
    if (no->valor <= limiteInferior || no->valor >= limiteSuperior) {
        return false;
    }

    // Subárvore esquerda: nenhum valor pode ser maior ou igual ao nó atual,
    // então o limite SUPERIOR passa a ser o valor do nó atual.
    bool esquerdaEhValida = validarSubarvore(no->esquerda, limiteInferior, no->valor);

    // Subárvore direita: nenhum valor pode ser menor ou igual ao nó atual,
    // então o limite INFERIOR passa a ser o valor do nó atual.
    bool direitaEhValida = validarSubarvore(no->direita, no->valor, limiteSuperior);

    return esquerdaEhValida && direitaEhValida;
}

// A raiz começa sem restrição nenhuma: de "menos infinito" a "mais infinito".
bool ehBSTValida(NoArvore* raiz) {
    long long menosInfinito = numeric_limits<long long>::min();
    long long maisInfinito = numeric_limits<long long>::max();
    return validarSubarvore(raiz, menosInfinito, maisInfinito);
}

int main() {
    int quantidadeDeNos;
    cin >> quantidadeDeNos;

    // Primeiro criamos todos os nós, depois ligamos os filhos pelos índices.
    vector<NoArvore*> nos(quantidadeDeNos);
    vector<int> indiceDoFilhoEsquerdo(quantidadeDeNos);
    vector<int> indiceDoFilhoDireito(quantidadeDeNos);

    for (int posicao = 0; posicao < quantidadeDeNos; posicao++) {
        int valor;
        cin >> valor >> indiceDoFilhoEsquerdo[posicao] >> indiceDoFilhoDireito[posicao];

        nos[posicao] = new NoArvore;
        nos[posicao]->valor = valor;
        nos[posicao]->esquerda = nullptr;
        nos[posicao]->direita = nullptr;
    }

    for (int posicao = 0; posicao < quantidadeDeNos; posicao++) {
        if (indiceDoFilhoEsquerdo[posicao] != -1) {
            nos[posicao]->esquerda = nos[indiceDoFilhoEsquerdo[posicao]];
        }
        if (indiceDoFilhoDireito[posicao] != -1) {
            nos[posicao]->direita = nos[indiceDoFilhoDireito[posicao]];
        }
    }

    NoArvore* raiz = nos[0];
    cout << (ehBSTValida(raiz) ? "True" : "False") << endl;

    // Liberar a memória de todos os nós criados.
    for (int posicao = 0; posicao < quantidadeDeNos; posicao++) {
        delete nos[posicao];
    }

    return 0;
}
