#include <iostream>
#include "BST.h"
#include "AVL.h"
using namespace std;

int main() {
    // ================= BST =================
    cout << "===== BST: inserindo 15, 7, 20, 3, 10, 25 =====" << endl;
    NoBST* arvoreBST = nullptr;
    int chavesDaBST[] = {15, 7, 20, 3, 10, 25};
    for (int posicao = 0; posicao < 6; posicao++) {
        arvoreBST = inserirNaBST(arvoreBST, chavesDaBST[posicao]);
    }

    imprimirArvoreBSTDeLado(arvoreBST, 0);

    cout << "Pre-ordem:   "; imprimirPreOrdemBST(arvoreBST);   cout << endl;
    cout << "Em ordem:    "; imprimirEmOrdemBST(arvoreBST);    cout << endl;
    cout << "Pos-ordem:   "; imprimirPosOrdemBST(arvoreBST);   cout << endl;
    cout << "Em largura:  "; imprimirEmLarguraBST(arvoreBST);  cout << endl;

    NoBST* sucessorDoDez = encontrarSucessor(arvoreBST, 10);
    NoBST* antecessorDoDez = encontrarAntecessor(arvoreBST, 10);
    cout << "Sucessor do 10: " << sucessorDoDez->chave << endl;
    cout << "Antecessor do 10: " << antecessorDoDez->chave << endl;
    cout << "Buscar 10: " << (buscarNaBST(arvoreBST, 10) ? "achou" : "nao achou") << endl;
    cout << "Buscar 99: " << (buscarNaBST(arvoreBST, 99) ? "achou" : "nao achou") << endl;

    cout << endl << "===== BST: remover a raiz (40) por copia =====" << endl;
    NoBST* arvoreParaRemover = nullptr;
    int chavesParaRemover[] = {40, 20, 60, 10, 30, 50, 70, 25};
    for (int posicao = 0; posicao < 8; posicao++) {
        arvoreParaRemover = inserirNaBST(arvoreParaRemover, chavesParaRemover[posicao]);
    }
    arvoreParaRemover = removerPorCopia(arvoreParaRemover, 40);
    imprimirArvoreBSTDeLado(arvoreParaRemover, 0);
    cout << "Em ordem: "; imprimirEmOrdemBST(arvoreParaRemover); cout << endl;

    // ============ BST x AVL com 1..100 em ordem crescente ============
    cout << endl << "===== Inserindo 1..100 em ordem crescente =====" << endl;
    NoBST* arvoreDegenerada = nullptr;
    NoAVL* arvoreBalanceada = nullptr;
    for (int chave = 1; chave <= 100; chave++) {
        arvoreDegenerada = inserirNaBST(arvoreDegenerada, chave);
        arvoreBalanceada = inserirNaAVL(arvoreBalanceada, chave);
    }
    cout << "Altura da BST: " << calcularAlturaBST(arvoreDegenerada) << " (vira uma lista, O(N))" << endl;
    cout << "Altura da AVL: " << obterAltura(arvoreBalanceada) << " (O(log N))" << endl;
    cout << "AVL esta balanceada? " << (arvoreAVLEstaBalanceada(arvoreBalanceada) ? "sim" : "nao") << endl;

    // ================= AVL: os 4 casos =================
    cout << endl << "===== AVL: os 4 casos (todos terminam com 20 na raiz) =====" << endl;
    int casoLL[] = {30, 20, 10};
    int casoRR[] = {10, 20, 30};
    int casoLR[] = {30, 10, 20};
    int casoRL[] = {10, 30, 20};
    int* todosOsCasos[] = {casoLL, casoRR, casoLR, casoRL};
    string nomesDosCasos[] = {"LL (30,20,10)", "RR (10,20,30)", "LR (30,10,20)", "RL (10,30,20)"};

    for (int caso = 0; caso < 4; caso++) {
        NoAVL* arvoreDoCaso = nullptr;
        for (int posicao = 0; posicao < 3; posicao++) {
            arvoreDoCaso = inserirNaAVL(arvoreDoCaso, todosOsCasos[caso][posicao]);
        }
        cout << "Caso " << nomesDosCasos[caso] << " -> pre-ordem: ";
        imprimirPreOrdemAVL(arvoreDoCaso);
        cout << endl;
        liberarAVL(arvoreDoCaso);
    }

    // ================= AVL: exercício das aulas =================
    cout << endl << "===== AVL: inserindo 40, 20, 10, 25, 30 =====" << endl;
    NoAVL* arvoreDoExercicio = nullptr;
    int chavesDoExercicio[] = {40, 20, 10, 25, 30};
    for (int posicao = 0; posicao < 5; posicao++) {
        arvoreDoExercicio = inserirNaAVL(arvoreDoExercicio, chavesDoExercicio[posicao]);
    }
    imprimirArvoreAVLDeLado(arvoreDoExercicio, 0);
    cout << "Pre-ordem: "; imprimirPreOrdemAVL(arvoreDoExercicio); cout << endl;
    cout << "Em ordem:  "; imprimirEmOrdemAVL(arvoreDoExercicio);  cout << endl;

    // ================= Liberar a memória =================
    liberarBST(arvoreBST);
    liberarBST(arvoreParaRemover);
    liberarBST(arvoreDegenerada);
    liberarAVL(arvoreBalanceada);
    liberarAVL(arvoreDoExercicio);

    return 0;
}
