#include <stdio.h>
#include <stdlib.h>

typedef int TipoItem;

// Estrutura para lista encadeada
struct no {
    TipoItem info;
    struct no* prox;
};

// Estrutura de lista com cabeça para implementação de pilha
typedef struct {
    struct no* topo;
} Pilha;

// Função para empilhar (push)
void push(Pilha *p, TipoItem x) {
    struct no* aux = (struct no*)malloc(sizeof(struct no));
    aux->info = x;
    aux->prox = p->topo;
    p->topo = aux;
}

// Função para desempilhar (pop)
// Retorna -1 se a pilha estiver vazia
TipoItem pop(Pilha *p) {
    if(p->topo == NULL) {
        return -1;
    }
    struct no *aux = p->topo;
    TipoItem x = aux->info;
    p->topo = aux->prox;
    free(aux);
    return x;
}

// Função principal para teste
int main() {
    Pilha p;
    p.topo = NULL;

    // Empilhando valores
    push(&p, 10);
    push(&p, 20);
    push(&p, 30);

    // Desempilhando valores
    printf("Valor desempilhado: %d\n", pop(&p));
    printf("Valor desempilhado: %d\n", pop(&p));
    printf("Valor desempilhado: %d\n", pop(&p));

    // Tentando desempilhar de uma pilha vazia
    printf("Tentativa de desempilhar de pilha vazia: %d\n", pop(&p));

    return 0;
}
