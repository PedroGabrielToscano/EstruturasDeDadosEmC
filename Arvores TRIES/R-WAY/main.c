#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_ALFABETO 26
#define ASCII_BASE 97

typedef struct no {
    struct no *filho[TAM_ALFABETO];
    int valor;
} noTRIE;

typedef noTRIE *TRIE;

typedef struct {
    TRIE raiz;
} arvTRIE;

noTRIE *criarNo() {
    noTRIE *novo = (noTRIE *)malloc(sizeof(noTRIE));
    novo->valor = 0;
    for (int i = 0; i < TAM_ALFABETO; i++)
        novo->filho[i] = NULL;
    return novo;
}

void inserir(arvTRIE *r, char *str, int valor) {
    if (!r->raiz)
        r->raiz = criarNo();

    noTRIE *p = r->raiz;
    while (*str) {
        int idx = *str - ASCII_BASE;
        if (!p->filho[idx])
            p->filho[idx] = criarNo();
        p = p->filho[idx];
        str++;
    }
    p->valor = valor;
}

int buscar(arvTRIE *r, char *str) {
    if (!r->raiz)
        return 0;

    noTRIE *p = r->raiz;
    while (*str) {
        int idx = *str - ASCII_BASE;
        if (!p->filho[idx])
            return 0;
        p = p->filho[idx];
        str++;
    }
    return p->valor;
}

int removerAux(noTRIE *p, char *str) {
    if (!p)
        return 0;

    if (*str) {
        int idx = *str - ASCII_BASE;
        if (removerAux(p->filho[idx], str + 1)) {
            free(p->filho[idx]);
            p->filho[idx] = NULL;
        }
    } else {
        if (p->valor) {
            p->valor = 0;
            for (int i = 0; i < TAM_ALFABETO; i++) {
                if (p->filho[i])
                    return 0;
            }
            return 1;
        }
    }
    return 0;
}

void remover(arvTRIE *r, char *str) {
    if (r->raiz)
        removerAux(r->raiz, str);
}

void imprimirAux(noTRIE *p, char *prefixo, int n) {
    if (!p)
        return;

    if (p->valor)
        printf("%s\n", prefixo);

    for (int i = 0; i < TAM_ALFABETO; i++) {
        if (p->filho[i]) {
            prefixo[n] = i + ASCII_BASE;
            prefixo[n + 1] = '\0';
            imprimirAux(p->filho[i], prefixo, n + 1);
        }
    }
}

void imprimir_dicionario(arvTRIE *r) {
    char buffer[100];
    imprimirAux(r->raiz, buffer, 0);
}

int contarPalavrasAux(noTRIE *p){
    if(!p) return 0;
    
    int cont = 0;
    if(p->valor) cont++;
    
    for(int i = 0; i< TAM_ALFABETO;i++){
        if(p->filho[i]) cont += contarPalavrasAux(p->filho[i]);
    }
    
    return cont;
}

int contarPalavras(arvTRIE *r){
    contarPalavrasAux(r->raiz);
}




int main() {
    arvTRIE trie = {NULL};

    inserir(&trie, "casa", 1);
    inserir(&trie, "carro", 2);
    inserir(&trie, "cadeira", 3);
    inserir(&trie, "jogo",4);
    inserir(&trie, "arame",5);
    inserir(&trie, "zanzibar",6);
    inserir(&trie, "romulo",72);
    
    printf("Buscar 'zanzibar': %d\n", buscar(&trie, "zanzibar"));
    
    printf("Buscar 'casa': %d\n", buscar(&trie, "casa"));
    printf("Buscar 'carro': %d\n", buscar(&trie, "carro"));
    printf("Buscar 'cadeira': %d\n", buscar(&trie, "cadeira"));

    printf("\nDicionário:\n");
    imprimir_dicionario(&trie);
    imprimir_dicionario(&trie);
    
    printf("%d\n",contarPalavras(&trie));

    printf("\nRemovendo 'carro'\n");
    remover(&trie, "carro");
    imprimir_dicionario(&trie);

    return 0;
}
