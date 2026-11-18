// Exercício 3: Simulador de AVL com contagem de rotações
// Inspirado em problemas de inserção em AVL (por exemplo, "Self Balancing Tree", do HackerRank)
//
// Entrada:
//   Linha 1: quantidade de chaves (N)
//   Linha 2: as N chaves, na ordem em que são inseridas na AVL
// Saída:
//   Linha 1: o percurso em pré-ordem da AVL final
//   Linha 2: quantas vezes ocorreu cada caso: LL=.. RR=.. LR=.. RL=..
//            (uma rotação dupla conta como UMA ocorrência de LR ou de RL)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct NoAVL {
    int chave;
    int altura;
    NoAVL* esquerda;
    NoAVL* direita;
};

// Guarda quantas vezes cada caso de desbalanceamento foi corrigido.
struct ContadorDeRotacoes {
    int casosLL = 0;
    int casosRR = 0;
    int casosLR = 0;
    int casosRL = 0;
};

NoAVL* criarNo(int chave) {
    NoAVL* novoNo = new NoAVL;
    novoNo->chave = chave;
    novoNo->altura = 0;  // todo nó novo é uma folha
    novoNo->esquerda = nullptr;
    novoNo->direita = nullptr;
    return novoNo;
}

// Nó que não existe vale -1; folha vale 0.
int obterAltura(NoAVL* no) {
    if (no == nullptr) {
        return -1;
    }
    return no->altura;
}

// Altura do nó = 1 + a maior altura entre os dois filhos.
void atualizarAltura(NoAVL* no) {
    no->altura = 1 + max(obterAltura(no->esquerda), obterAltura(no->direita));
}

// FB = altura da esquerda - altura da direita.
int calcularFatorDeBalanceamento(NoAVL* no) {
    if (no == nullptr) {
        return 0;
    }
    return obterAltura(no->esquerda) - obterAltura(no->direita);
}

// Rotação à direita: o filho esquerdo (y) sobe e o nó desbalanceado (z) desce para a direita.
NoAVL* rotacaoParaDireita(NoAVL* noDesbalanceado) {
    NoAVL* filhoEsquerdo = noDesbalanceado->esquerda;   // y
    NoAVL* subarvoreDoMeio = filhoEsquerdo->direita;    // T, troca de dono

    filhoEsquerdo->direita = noDesbalanceado;
    noDesbalanceado->esquerda = subarvoreDoMeio;

    // Primeiro atualiza quem desceu, depois quem subiu.
    atualizarAltura(noDesbalanceado);
    atualizarAltura(filhoEsquerdo);
    return filhoEsquerdo;
}

// Rotação à esquerda: espelho da rotação à direita.
NoAVL* rotacaoParaEsquerda(NoAVL* noDesbalanceado) {
    NoAVL* filhoDireito = noDesbalanceado->direita;     // y
    NoAVL* subarvoreDoMeio = filhoDireito->esquerda;    // T, troca de dono

    filhoDireito->esquerda = noDesbalanceado;
    noDesbalanceado->direita = subarvoreDoMeio;

    atualizarAltura(noDesbalanceado);
    atualizarAltura(filhoDireito);
    return filhoDireito;
}

// Confere o nó, identifica qual dos 4 casos ocorreu, conta e aplica a rotação.
NoAVL* balancearNo(NoAVL* no, ContadorDeRotacoes& contador) {
    atualizarAltura(no);
    int fatorDeBalanceamento = calcularFatorDeBalanceamento(no);

    // Pesado para a esquerda (FB = +2)
    if (fatorDeBalanceamento > 1) {
        if (calcularFatorDeBalanceamento(no->esquerda) < 0) {
            // Filho pende para a direita: caso LR (rotação dupla).
            contador.casosLR++;
            no->esquerda = rotacaoParaEsquerda(no->esquerda);   // 1º: esquerda no filho
        } else {
            contador.casosLL++;                                  // linha reta: caso LL
        }
        return rotacaoParaDireita(no);                           // direita no nó
    }

    // Pesado para a direita (FB = -2)
    if (fatorDeBalanceamento < -1) {
        if (calcularFatorDeBalanceamento(no->direita) > 0) {
            // Filho pende para a esquerda: caso RL (rotação dupla).
            contador.casosRL++;
            no->direita = rotacaoParaDireita(no->direita);      // 1º: direita no filho
        } else {
            contador.casosRR++;                                  // linha reta: caso RR
        }
        return rotacaoParaEsquerda(no);                          // esquerda no nó
    }

    return no;  // já estava equilibrado
}

// Insere como numa BST e, na volta da recursão, balanceia cada nó do caminho.
NoAVL* inserirNaAVL(NoAVL* raiz, int chave, ContadorDeRotacoes& contador) {
    if (raiz == nullptr) {
        return criarNo(chave);
    }

    if (chave < raiz->chave) {
        raiz->esquerda = inserirNaAVL(raiz->esquerda, chave, contador);
    } else if (chave > raiz->chave) {
        raiz->direita = inserirNaAVL(raiz->direita, chave, contador);
    } else {
        return raiz;  // chave repetida: ignora
    }

    return balancearNo(raiz, contador);
}

// Coleta as chaves em pré-ordem (raiz, esquerda, direita).
void coletarPreOrdem(NoAVL* raiz, vector<int>& chaves) {
    if (raiz == nullptr) {
        return;
    }
    chaves.push_back(raiz->chave);
    coletarPreOrdem(raiz->esquerda, chaves);
    coletarPreOrdem(raiz->direita, chaves);
}

void liberarAVL(NoAVL* raiz) {
    if (raiz == nullptr) {
        return;
    }
    liberarAVL(raiz->esquerda);
    liberarAVL(raiz->direita);
    delete raiz;
}

int main() {
    int quantidadeDeChaves;
    cin >> quantidadeDeChaves;

    NoAVL* raiz = nullptr;
    ContadorDeRotacoes contador;

    for (int posicao = 0; posicao < quantidadeDeChaves; posicao++) {
        int chave;
        cin >> chave;
        raiz = inserirNaAVL(raiz, chave, contador);
    }

    vector<int> chaves;
    coletarPreOrdem(raiz, chaves);

    for (size_t posicao = 0; posicao < chaves.size(); posicao++) {
        if (posicao > 0) {
            cout << " ";
        }
        cout << chaves[posicao];
    }
    cout << endl;

    cout << "LL=" << contador.casosLL
         << " RR=" << contador.casosRR
         << " LR=" << contador.casosLR
         << " RL=" << contador.casosRL << endl;

    liberarAVL(raiz);
    return 0;
}
