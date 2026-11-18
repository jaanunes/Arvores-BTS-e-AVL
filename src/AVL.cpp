#include "AVL.h"
#include <queue>
#include <string>

NoAVL* criarNoAVL(int chave) {
    NoAVL* novoNo = new NoAVL;
    novoNo->chave = chave;
    novoNo->altura = 0;  // todo nó novo é uma folha
    novoNo->esquerda = nullptr;
    novoNo->direita = nullptr;
    return novoNo;
}

// ---------------------------------------------------------
// Altura e Fator de Balanceamento
// ---------------------------------------------------------

// Nó que não existe vale -1; folha vale 0.
int obterAltura(NoAVL* no) {
    if (no == nullptr) {
        return -1;
    }
    return no->altura;
}

// Altura do nó = 1 + a maior altura entre os dois filhos.
void atualizarAltura(NoAVL* no) {
    int alturaDaEsquerda = obterAltura(no->esquerda);
    int alturaDaDireita = obterAltura(no->direita);
    no->altura = 1 + max(alturaDaEsquerda, alturaDaDireita);
}

// FB = altura da esquerda - altura da direita.
// Positivo: pesado para a esquerda. Negativo: pesado para a direita.
int calcularFatorDeBalanceamento(NoAVL* no) {
    if (no == nullptr) {
        return 0;
    }
    return obterAltura(no->esquerda) - obterAltura(no->direita);
}

// ---------------------------------------------------------
// Rotações
// ---------------------------------------------------------

// Caso LL: o filho da esquerda sobe e o nó desbalanceado desce para a direita.
NoAVL* rotacaoParaDireita(NoAVL* noDesbalanceado) {
    NoAVL* filhoEsquerdo = noDesbalanceado->esquerda;     // este vai subir
    NoAVL* subarvoreDoMeio = filhoEsquerdo->direita;      // este troca de dono

    filhoEsquerdo->direita = noDesbalanceado;             // o pai desce para a direita
    noDesbalanceado->esquerda = subarvoreDoMeio;          // a subárvore do meio vira filho esquerdo do pai

    // Atualizar as alturas: primeiro quem desceu, depois quem subiu.
    atualizarAltura(noDesbalanceado);
    atualizarAltura(filhoEsquerdo);

    return filhoEsquerdo;  // nova raiz desta subárvore
}

// Caso RR: espelho da rotação para a direita.
NoAVL* rotacaoParaEsquerda(NoAVL* noDesbalanceado) {
    NoAVL* filhoDireito = noDesbalanceado->direita;
    NoAVL* subarvoreDoMeio = filhoDireito->esquerda;

    filhoDireito->esquerda = noDesbalanceado;
    noDesbalanceado->direita = subarvoreDoMeio;

    atualizarAltura(noDesbalanceado);
    atualizarAltura(filhoDireito);

    return filhoDireito;
}

// ---------------------------------------------------------
// Balancear: confere o nó e aplica a rotação necessária
// ---------------------------------------------------------
NoAVL* balancearNo(NoAVL* no) {
    atualizarAltura(no);
    int fatorDeBalanceamento = calcularFatorDeBalanceamento(no);

    // Pesado para a esquerda (FB = +2)
    if (fatorDeBalanceamento > 1) {
        // Caso LR: o filho esquerdo pende para a direita ("cotovelo").
        // Primeiro rotaciona o filho para a esquerda.
        if (calcularFatorDeBalanceamento(no->esquerda) < 0) {
            no->esquerda = rotacaoParaEsquerda(no->esquerda);
        }
        // Caso LL (ou segundo passo do LR)
        return rotacaoParaDireita(no);
    }

    // Pesado para a direita (FB = -2)
    if (fatorDeBalanceamento < -1) {
        // Caso RL: o filho direito pende para a esquerda.
        if (calcularFatorDeBalanceamento(no->direita) > 0) {
            no->direita = rotacaoParaDireita(no->direita);
        }
        // Caso RR (ou segundo passo do RL)
        return rotacaoParaEsquerda(no);
    }

    return no;  // já estava equilibrado
}

// ---------------------------------------------------------
// Inserção: insere como na BST e balanceia na volta da recursão
// ---------------------------------------------------------
NoAVL* inserirNaAVL(NoAVL* raiz, int chave) {
    if (raiz == nullptr) {
        return criarNoAVL(chave);
    }

    if (chave < raiz->chave) {
        raiz->esquerda = inserirNaAVL(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = inserirNaAVL(raiz->direita, chave);
    } else {
        return raiz;  // chave repetida
    }

    // Subindo de volta: confere e corrige cada nó do caminho.
    return balancearNo(raiz);
}

// ---------------------------------------------------------
// Remoção: igual à remoção por cópia da BST, mas balanceando na volta
// ---------------------------------------------------------
NoAVL* removerDaAVL(NoAVL* raiz, int chave) {
    if (raiz == nullptr) {
        return nullptr;
    }

    if (chave < raiz->chave) {
        raiz->esquerda = removerDaAVL(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = removerDaAVL(raiz->direita, chave);
    } else {
        if (raiz->esquerda == nullptr) {
            NoAVL* filhoDaDireita = raiz->direita;
            delete raiz;
            return filhoDaDireita;
        }
        if (raiz->direita == nullptr) {
            NoAVL* filhoDaEsquerda = raiz->esquerda;
            delete raiz;
            return filhoDaEsquerda;
        }

        // Dois filhos: acha o antecessor (maior da esquerda).
        NoAVL* antecessor = raiz->esquerda;
        while (antecessor->direita != nullptr) {
            antecessor = antecessor->direita;
        }
        raiz->chave = antecessor->chave;
        raiz->esquerda = removerDaAVL(raiz->esquerda, antecessor->chave);
    }

    return balancearNo(raiz);
}

bool buscarNaAVL(NoAVL* raiz, int chave) {
    NoAVL* noAtual = raiz;
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

// Confere se TODOS os nós têm FB entre -1 e +1.
bool arvoreAVLEstaBalanceada(NoAVL* raiz) {
    if (raiz == nullptr) {
        return true;
    }
    int fatorDeBalanceamento = calcularFatorDeBalanceamento(raiz);
    if (fatorDeBalanceamento > 1 || fatorDeBalanceamento < -1) {
        return false;
    }
    return arvoreAVLEstaBalanceada(raiz->esquerda) && arvoreAVLEstaBalanceada(raiz->direita);
}

// ---------------------------------------------------------
// Percursos
// ---------------------------------------------------------
void imprimirPreOrdemAVL(NoAVL* raiz) {
    if (raiz == nullptr) {
        return;
    }
    cout << raiz->chave << " ";
    imprimirPreOrdemAVL(raiz->esquerda);
    imprimirPreOrdemAVL(raiz->direita);
}

void imprimirEmOrdemAVL(NoAVL* raiz) {
    if (raiz == nullptr) {
        return;
    }
    imprimirEmOrdemAVL(raiz->esquerda);
    cout << raiz->chave << " ";
    imprimirEmOrdemAVL(raiz->direita);
}

void imprimirPosOrdemAVL(NoAVL* raiz) {
    if (raiz == nullptr) {
        return;
    }
    imprimirPosOrdemAVL(raiz->esquerda);
    imprimirPosOrdemAVL(raiz->direita);
    cout << raiz->chave << " ";
}

void imprimirEmLarguraAVL(NoAVL* raiz) {
    if (raiz == nullptr) {
        return;
    }
    queue<NoAVL*> fila;
    fila.push(raiz);
    while (!fila.empty()) {
        NoAVL* noAtual = fila.front();
        fila.pop();
        cout << noAtual->chave << " ";
        if (noAtual->esquerda != nullptr) {
            fila.push(noAtual->esquerda);
        }
        if (noAtual->direita != nullptr) {
            fila.push(noAtual->direita);
        }
    }
}

void imprimirArvoreAVLDeLado(NoAVL* raiz, int espacos) {
    if (raiz == nullptr) {
        return;
    }
    imprimirArvoreAVLDeLado(raiz->direita, espacos + 6);
    cout << string(espacos, ' ') << raiz->chave << endl;
    imprimirArvoreAVLDeLado(raiz->esquerda, espacos + 6);
}

void liberarAVL(NoAVL* raiz) {
    if (raiz == nullptr) {
        return;
    }
    liberarAVL(raiz->esquerda);
    liberarAVL(raiz->direita);
    delete raiz;
}
