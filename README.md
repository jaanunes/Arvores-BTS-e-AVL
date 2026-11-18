# Árvores BST e AVL em C++

Implementação própria e completa de **Árvore Binária de Busca (BST)** e **Árvore AVL**, desenvolvida para o seminário de Estruturas de Dados.

**Alunos:** Janaína, Mateus e Sâmara
**Disciplina:** Estruturas de Dados
**Instituição:** IFTM Campus Patrocínio, Tecnologia em Análise e Desenvolvimento de Sistemas

## O que o projeto contém

### BST (Árvore Binária de Busca)
- Inserção e busca
- Percursos em profundidade: pre-order, in-order e post-order
- Percurso em largura (level-order), usando uma fila
- Sucessor e antecessor
- Remoção por cópia e remoção por fusão
- Cálculo da altura (nó nulo = -1, folha = 0)
- Complexidade: O(log N) no caso médio e O(N) no pior caso (degeneração em lista)

### AVL
- Altura guardada em cada nó e cálculo do fator de balanceamento: `FB = altura(esquerda) - altura(direita)`
- Rotações simples (à direita e à esquerda) e duplas
- Os quatro casos de desbalanceamento: Esquerda-Esquerda, Direita-Direita, Esquerda-Direita e Direita-Esquerda
- Inserção e remoção com rebalanceamento
- Verificação de balanceamento da árvore inteira
- Complexidade: O(log N) garantido, mesmo no pior caso

## Estrutura de pastas

```
.
├── include/
│   ├── BST.hpp      declarações e struct NoBST
│   └── AVL.hpp      declarações e struct NoAVL
├── src/
│   ├── BST.cpp      implementação da BST
│   ├── AVL.cpp      implementação da AVL
├── main.cpp         programa de demonstração e testes
├── Makefile
└── README.md
```

## O que o programa demonstra

O `main.cpp` mostra, na tela:

1. A BST com as chaves 15, 7, 20, 3, 10, 25, desenhada de lado, com os quatro percursos, sucessor, antecessor e busca.
2. A remoção por cópia da raiz de uma BST.
3. A inserção das chaves 1 a 100 em ordem crescente, comparando a altura da BST (99, vira uma lista) com a da AVL (6).
4. Os quatro casos de rotação da AVL, todos terminando com o 20 na raiz.
5. O exemplo 40, 20, 10, 25, 30 na AVL, que resulta no pre-order `20 10 30 25 40`.

## Decisões de implementação

- Chaves duplicadas são ignoradas na inserção.
- Funções recursivas devolvem a raiz da subárvore e o resultado é gravado de volta no filho (`raiz->esquerda = inserir(...)`), o que religa a árvore.
- Na AVL, a inserção é a da BST seguida de `balancearNo` na volta da recursão, corrigindo primeiro o nó mais baixo com |FB| = 2.
- Na AVL, a remoção usa o antecessor (remoção por cópia) e também rebalanceia na volta, podendo exigir mais de uma rotação.
- Código simples: `struct` e funções, `using namespace std` e nomes sem abreviações.

