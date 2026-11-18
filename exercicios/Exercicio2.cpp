// Exercício 2: Operações e Percursos em BST
// Adaptado de Beecrowd 1200 (Operações em ABP I)
//
// Comandos (um por linha, até o fim da entrada):
//   I X       insere o caractere X
//   P X       pesquisa o caractere X
//   INFIXA    imprime em ordem (esquerda, raiz, direita)
//   PREFIXA   imprime em pré-ordem (raiz, esquerda, direita)
//   POSFIXA   imprime em pós-ordem (esquerda, direita, raiz)

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct NoArvore {
    char chave;
    NoArvore* esquerda;
    NoArvore* direita;
};

NoArvore* criarNo(char chave) {
    NoArvore* novoNo = new NoArvore;
    novoNo->chave = chave;
    novoNo->esquerda = nullptr;
    novoNo->direita = nullptr;
    return novoNo;
}

// Inserção recursiva: desce até achar um lugar vazio e cria o nó ali.
// A função devolve a raiz da subárvore, e o resultado é gravado de volta no filho.
NoArvore* inserir(NoArvore* raiz, char chave) {
    if (raiz == nullptr) {
        return criarNo(chave);
    }
    if (chave < raiz->chave) {
        raiz->esquerda = inserir(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = inserir(raiz->direita, chave);
    }
    return raiz;
}

// Busca iterativa: a cada comparação descarta uma das duas subárvores.
bool pesquisar(NoArvore* raiz, char chave) {
    NoArvore* noAtual = raiz;
    while (noAtual != nullptr) {
        if (chave == noAtual->chave) {
            return true;
        }
        if (chave < noAtual->chave) {
            noAtual = noAtual->esquerda;
        } else {
            noAtual = noAtual->direita;
        }
    }
    return false;
}

// Os percursos guardam as chaves numa lista, para podermos imprimir
// separadas por um único espaço, sem espaço sobrando no final da linha.
void coletarInfixa(NoArvore* raiz, vector<char>& chaves) {
    if (raiz == nullptr) {
        return;
    }
    coletarInfixa(raiz->esquerda, chaves);
    chaves.push_back(raiz->chave);              // raiz no meio
    coletarInfixa(raiz->direita, chaves);
}

void coletarPrefixa(NoArvore* raiz, vector<char>& chaves) {
    if (raiz == nullptr) {
        return;
    }
    chaves.push_back(raiz->chave);              // raiz primeiro
    coletarPrefixa(raiz->esquerda, chaves);
    coletarPrefixa(raiz->direita, chaves);
}

void coletarPosfixa(NoArvore* raiz, vector<char>& chaves) {
    if (raiz == nullptr) {
        return;
    }
    coletarPosfixa(raiz->esquerda, chaves);
    coletarPosfixa(raiz->direita, chaves);
    chaves.push_back(raiz->chave);              // raiz por último
}

void imprimirChaves(const vector<char>& chaves) {
    for (size_t posicao = 0; posicao < chaves.size(); posicao++) {
        if (posicao > 0) {
            cout << " ";
        }
        cout << chaves[posicao];
    }
    cout << endl;
}

void liberarArvore(NoArvore* raiz) {
    if (raiz == nullptr) {
        return;
    }
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    delete raiz;
}

int main() {
    NoArvore* raiz = nullptr;
    string comando;

    // Lê comando por comando até acabar a entrada.
    while (cin >> comando) {
        if (comando == "I") {
            char chave;
            cin >> chave;
            raiz = inserir(raiz, chave);
        } else if (comando == "P") {
            char chave;
            cin >> chave;
            if (pesquisar(raiz, chave)) {
                cout << chave << " existe" << endl;
            } else {
                cout << chave << " nao existe" << endl;
            }
        } else if (comando == "INFIXA") {
            vector<char> chaves;
            coletarInfixa(raiz, chaves);
            imprimirChaves(chaves);
        } else if (comando == "PREFIXA") {
            vector<char> chaves;
            coletarPrefixa(raiz, chaves);
            imprimirChaves(chaves);
        } else if (comando == "POSFIXA") {
            vector<char> chaves;
            coletarPosfixa(raiz, chaves);
            imprimirChaves(chaves);
        }
    }

    liberarArvore(raiz);
    return 0;
}
