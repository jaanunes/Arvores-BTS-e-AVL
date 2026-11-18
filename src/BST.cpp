#include "BST.h"
#include <queue>
#include <string>
#include  <algorithm>

// ---------------------------------------------------------
// Criar um nó novo, sem filhos
// ---------------------------------------------------------
NoBST* criarNoBST(int chave) {
    NoBST* novoNo = new NoBST;
    novoNo->chave = chave;
    novoNo->esquerda = nullptr;
    novoNo->direita = nullptr;
    return novoNo;
}

// ---------------------------------------------------------
// Inserção: desce comparando até achar um lugar vazio
// ---------------------------------------------------------
NoBST* inserirNaBST(NoBST* raiz, int chave) {
    // Lugar vazio: criamos o nó aqui.
    if (raiz == nullptr) {
        return criarNoBST(chave);
    }

    if (chave < raiz->chave) {
        // Menor: vai para a esquerda e guarda o resultado de volta.
        raiz->esquerda = inserirNaBST(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        // Maior: vai para a direita.
        raiz->direita = inserirNaBST(raiz->direita, chave);
    }
    // Se for igual, não faz nada (ignora chave repetida).

    return raiz;
}

// ---------------------------------------------------------
// Busca: mesma descida da inserção, mas sem criar nó
// ---------------------------------------------------------
bool buscarNaBST(NoBST* raiz, int chave) {
    NoBST* noAtual = raiz;

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

// ---------------------------------------------------------
// Maior nó de uma árvore: vai sempre para a direita
// ---------------------------------------------------------
NoBST* encontrarMaiorNo(NoBST* raiz) {
    NoBST* noAtual = raiz;
    while (noAtual->direita != nullptr) {
        noAtual = noAtual->direita;
    }
    return noAtual;
}

// ---------------------------------------------------------
// Sucessor: menor chave que é MAIOR que a chave dada
// Descendo da raiz, guardamos o último nó em que fomos para a esquerda.
// ---------------------------------------------------------
NoBST* encontrarSucessor(NoBST* raiz, int chave) {
    NoBST* noAtual = raiz;
    NoBST* possivelSucessor = nullptr;

    while (noAtual != nullptr) {
        if (chave < noAtual->chave) {
            possivelSucessor = noAtual;
            noAtual = noAtual->esquerda;
        } else {
            noAtual = noAtual->direita;
        }
    }

    return possivelSucessor;  // nullptr se não existir
}

// ---------------------------------------------------------
// Antecessor: maior chave que é MENOR que a chave dada (espelho do sucessor)
// ---------------------------------------------------------
NoBST* encontrarAntecessor(NoBST* raiz, int chave) {
    NoBST* noAtual = raiz;
    NoBST* possivelAntecessor = nullptr;

    while (noAtual != nullptr) {
        if (chave > noAtual->chave) {
            possivelAntecessor = noAtual;
            noAtual = noAtual->direita;
        } else {
            noAtual = noAtual->esquerda;
        }
    }

    return possivelAntecessor;  // nullptr se não existir
}

// ---------------------------------------------------------
// Remoção por cópia
// ---------------------------------------------------------
NoBST* removerPorCopia(NoBST* raiz, int chave) {
    if (raiz == nullptr) {
        return nullptr;  // chave não existe
    }

    if (chave < raiz->chave) {
        raiz->esquerda = removerPorCopia(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = removerPorCopia(raiz->direita, chave);
    } else {
        // Achamos o nó que será removido.

        // Caso 1 e 2: sem filho esquerdo (folha ou só filho direito).
        if (raiz->esquerda == nullptr) {
            NoBST* filhoDaDireita = raiz->direita;
            delete raiz;
            return filhoDaDireita;
        }

        // Caso 2: sem filho direito (só filho esquerdo).
        if (raiz->direita == nullptr) {
            NoBST* filhoDaEsquerda = raiz->esquerda;
            delete raiz;
            return filhoDaEsquerda;
        }

        // Caso 3: dois filhos. Copiamos o antecessor para este nó
        // e depois removemos o nó original do antecessor.
        NoBST* antecessor = encontrarMaiorNo(raiz->esquerda);
        raiz->chave = antecessor->chave;
        raiz->esquerda = removerPorCopia(raiz->esquerda, antecessor->chave);
    }

    return raiz;
}

// ---------------------------------------------------------
// Remoção por fusão
// ---------------------------------------------------------
NoBST* removerPorFusao(NoBST* raiz, int chave) {
    if (raiz == nullptr) {
        return nullptr;
    }

    if (chave < raiz->chave) {
        raiz->esquerda = removerPorFusao(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = removerPorFusao(raiz->direita, chave);
    } else {
        if (raiz->esquerda == nullptr) {
            NoBST* filhoDaDireita = raiz->direita;
            delete raiz;
            return filhoDaDireita;
        }
        if (raiz->direita == nullptr) {
            NoBST* filhoDaEsquerda = raiz->esquerda;
            delete raiz;
            return filhoDaEsquerda;
        }

        // Dois filhos: pendura a subárvore direita inteira no nó mais
        // à direita da subárvore esquerda. A esquerda assume o lugar do nó.
        NoBST* antecessor = encontrarMaiorNo(raiz->esquerda);
        antecessor->direita = raiz->direita;
        NoBST* novaRaizDaSubarvore = raiz->esquerda;
        delete raiz;
        return novaRaizDaSubarvore;
    }

    return raiz;
}

// ---------------------------------------------------------
// Percursos em profundidade
// ---------------------------------------------------------
void imprimirPreOrdemBST(NoBST* raiz) {
    if (raiz == nullptr) {
        return;
    }
    cout << raiz->chave << " ";            // raiz primeiro
    imprimirPreOrdemBST(raiz->esquerda);
    imprimirPreOrdemBST(raiz->direita);
}

void imprimirEmOrdemBST(NoBST* raiz) {
    if (raiz == nullptr) {
        return;
    }
    imprimirEmOrdemBST(raiz->esquerda);
    cout << raiz->chave << " ";            // raiz no meio
    imprimirEmOrdemBST(raiz->direita);
}

void imprimirPosOrdemBST(NoBST* raiz) {
    if (raiz == nullptr) {
        return;
    }
    imprimirPosOrdemBST(raiz->esquerda);
    imprimirPosOrdemBST(raiz->direita);
    cout << raiz->chave << " ";            // raiz por último
}

// ---------------------------------------------------------
// Percurso em largura: usa uma fila
// ---------------------------------------------------------
void imprimirEmLarguraBST(NoBST* raiz) {
    if (raiz == nullptr) {
        return;
    }

    queue<NoBST*> fila;
    fila.push(raiz);

    while (!fila.empty()) {
        NoBST* noAtual = fila.front();  // primeiro da fila
        fila.pop();                     // tira da fila
        cout << noAtual->chave << " ";

        // Só entram na fila os filhos de quem acabou de sair.
        if (noAtual->esquerda != nullptr) {
            fila.push(noAtual->esquerda);
        }
        if (noAtual->direita != nullptr) {
            fila.push(noAtual->direita);
        }
    }
}

// ---------------------------------------------------------
// Desenho da árvore "deitada" (raiz à esquerda, direita em cima)
// ---------------------------------------------------------
void imprimirArvoreBSTDeLado(NoBST* raiz, int espacos) {
    if (raiz == nullptr) {
        return;
    }
    imprimirArvoreBSTDeLado(raiz->direita, espacos + 6);
    cout << string(espacos, ' ') << raiz->chave << endl;
    imprimirArvoreBSTDeLado(raiz->esquerda, espacos + 6);
}

// ---------------------------------------------------------
// Altura: árvore vazia = -1, folha = 0
// ---------------------------------------------------------
int calcularAlturaBST(NoBST* raiz) {
    if (raiz == nullptr) {
        return -1;
    }
    int alturaDaEsquerda = calcularAlturaBST(raiz->esquerda);
    int alturaDaDireita = calcularAlturaBST(raiz->direita);
    return 1 + max(alturaDaEsquerda, alturaDaDireita);
}

// ---------------------------------------------------------
// Liberar a memória: primeiro os filhos, depois o pai
// ---------------------------------------------------------
void liberarBST(NoBST* raiz) {
    if (raiz == nullptr) {
        return;
    }
    liberarBST(raiz->esquerda);
    liberarBST(raiz->direita);
    delete raiz;
}
