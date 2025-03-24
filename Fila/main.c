#include <stdio.h>
#include <stdlib.h>

typedef int tipoitem;

struct no {
    tipoitem info;
    struct no *prox;
};

typedef struct {
    struct no *inicio;
    struct no *fim;
} Fila;

// Verifica se a fila está vazia
int vazia(Fila *f) {
    return (f->inicio == NULL);
}

// Insere um elemento na fila
void enfileira(Fila *f, tipoitem valor) {
    struct no *novo = (struct no *)malloc(sizeof(struct no));
    if (!novo) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    novo->info = valor;
    novo->prox = NULL;
    
    if (vazia(f)) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

// Remove um elemento da fila e retorna o seu valor
int remove_da_fila(Fila *f) {
    if (vazia(f)) {
        printf("Fila vazia!\n");
        return -1;  // Ou outro valor que indique erro
    }
    
    struct no *aux = f->inicio;
    int c = aux->info;  // Valor a ser retornado

    if (f->inicio != f->fim) {
        f->inicio = aux->prox;
    } else {
        f->inicio = f->fim = NULL;
    }

    free(aux);
    return c;
}

int main() {
    Fila f = {NULL, NULL};  // Inicializa a fila

    // Enfileira alguns elementos
    enfileira(&f, 10);
    enfileira(&f, 20);
    enfileira(&f, 30);
    enfileira(&f, 40);

    printf("Removendo elementos da fila:\n");
    while (!vazia(&f)) {
        int removido = remove_da_fila(&f);
        printf("Removido: %d\n", removido);
    }

    return 0;
}
