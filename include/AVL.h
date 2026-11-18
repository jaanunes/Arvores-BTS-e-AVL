#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
using namespace std;

// Igual ao nó da BST, mas guarda também a altura do nó.
struct NoAVL {
    int chave;
    int altura;
    NoAVL* esquerda;
    NoAVL* direita;
};

NoAVL* criarNoAVL(int chave);
int obterAltura(NoAVL* no);
void atualizarAltura(NoAVL* no);
int calcularFatorDeBalanceamento(NoAVL* no);

NoAVL* rotacaoParaDireita(NoAVL* noDesbalanceado);
NoAVL* rotacaoParaEsquerda(NoAVL* noDesbalanceado);
NoAVL* balancearNo(NoAVL* no);

NoAVL* inserirNaAVL(NoAVL* raiz, int chave);
NoAVL* removerDaAVL(NoAVL* raiz, int chave);
bool buscarNaAVL(NoAVL* raiz, int chave);
bool arvoreAVLEstaBalanceada(NoAVL* raiz);

void imprimirPreOrdemAVL(NoAVL* raiz);
void imprimirEmOrdemAVL(NoAVL* raiz);
void imprimirPosOrdemAVL(NoAVL* raiz);
void imprimirEmLarguraAVL(NoAVL* raiz);
void imprimirArvoreAVLDeLado(NoAVL* raiz, int espacos);
void liberarAVL(NoAVL* raiz);

#endif
