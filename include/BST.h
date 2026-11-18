#ifndef BST_HPP
#define BST_HPP

#include <iostream>
using namespace std;

// Cada nó da árvore guarda uma chave e o endereço dos seus dois filhos.
struct NoBST {
    int chave;
    NoBST* esquerda;
    NoBST* direita;
};

NoBST* criarNoBST(int chave);
NoBST* inserirNaBST(NoBST* raiz, int chave);
bool buscarNaBST(NoBST* raiz, int chave);
NoBST* encontrarMaiorNo(NoBST* raiz);
NoBST* removerPorCopia(NoBST* raiz, int chave);
NoBST* removerPorFusao(NoBST* raiz, int chave);
NoBST* encontrarSucessor(NoBST* raiz, int chave);
NoBST* encontrarAntecessor(NoBST* raiz, int chave);

void imprimirPreOrdemBST(NoBST* raiz);
void imprimirEmOrdemBST(NoBST* raiz);
void imprimirPosOrdemBST(NoBST* raiz);
void imprimirEmLarguraBST(NoBST* raiz);
void imprimirArvoreBSTDeLado(NoBST* raiz, int espacos);

int calcularAlturaBST(NoBST* raiz);
void liberarBST(NoBST* raiz);

#endif
