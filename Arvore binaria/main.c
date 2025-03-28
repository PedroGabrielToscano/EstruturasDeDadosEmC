#include <stdlib.h>
#include <stdio.h>

struct no{
    int info;
    struct no* esq;
    struct no* dir;
};

typedef struct no* arvore;

//Verifica se uma arvore esta vazia
int vazia(arvore r){ return (r == NULL);}

//percorrimento in-ordem
void in_ordem(arvore r){
    if(!vazia(r)){
       in_ordem(r->esq);
       printf("%d ", r->info);
       in_ordem(r->dir);
    }
}


void pre_ordem(arvore r){
    if(!vazia(r)){
       printf("[%d,", r->info);
        pre_ordem(r->esq);
       printf(",");
       pre_ordem(r->dir);
       printf("]");
    }else printf("[]");
}


arvore inserir(arvore r, int info){
    if(vazia(r)){
        r = (struct no*)malloc(sizeof(struct no));
        r->info = info;
        r->dir = NULL;
        r->esq = NULL;
    }else if(info<r->info){
        r->esq = inserir(r->esq, info);
    }else{
        r->dir = inserir(r->dir, info);
    }
    return r;
}

void imprimir_intervalo(arvore r, int a, int b) {
    if (!vazia(r)) {
        // Se o valor atual for maior que 'a', percorre a subárvore esquerda
        if (a < r->info) {
            imprimir_intervalo(r->esq, a, b);
        }
        
        // Se o valor atual estiver dentro do intervalo, imprime
        if (a <= r->info && r->info <= b) {
            printf("%d ", r->info);
        }
        
        // Se o valor atual for menor que 'b', percorre a subárvore direita
        if (r->info < b) {
            imprimir_intervalo(r->dir, a, b);
        }
    }
}

int conta_no_interno(arvore r){
    if(!vazia(r)){
        int count = 0;
        
        if((r->esq != NULL)||(r->dir != NULL)){
            count = 1;
        }
        
        count += conta_no_interno(r->esq);
        count += conta_no_interno(r->dir);
        
        return count;
    }
    else return 0;
}
    

// Função para determinar a altura da árvore
int altura(arvore r) {
    if (r == NULL)
        return 0;
    else {
        // Calcula a altura das subárvores esquerda e direita
        int altura_esq = altura(r->esq);
        int altura_dir = altura(r->dir);

        // Retorna o maior valor entre as duas alturas mais 1 (para o nó atual)
        if (altura_esq > altura_dir)
            return altura_esq + 1;
        else
            return altura_dir + 1;
    }
}

// Função para imprimir os nós em um nível específico
void imprimir_nivel(arvore r, int nivel) {
    if (r == NULL)
        return;
    if (nivel == 1)
        printf("%d ", r->info);
    else if (nivel > 1) {
        imprimir_nivel(r->esq, nivel - 1);
        imprimir_nivel(r->dir, nivel - 1);
    }
}


// Função para imprimir a árvore por níveis usando recursão
void imprimir_por_niveis_recursivo(arvore r) {
    int h = altura(r);
    int i;
    for (i = 1; i <= h; i++) {
        imprimir_nivel(r, i);
        printf("\n"); 
    }
}


int conta_no_FilhoUnico(arvore r){
    if(!vazia(r)){
        int count = 0;
        
        if(((r->esq != NULL)&&(r->dir == NULL))||((r->esq == NULL)&&(r->dir != NULL))){
            count = 1;
        }
        
        count += conta_no_FilhoUnico(r->esq);
        count += conta_no_FilhoUnico(r->dir);
        
        return count;
    }else return 0;
    
}


int chave_seguinte(arvore r, int x){
    if(vazia(r)) return -1;
    if(r->info > x){
        int prox = chave_seguinte(r->esq, x);
        if(prox != -1 && prox < r->info) return prox;
        return r->info;
    }
    return chave_seguinte(r->dir, x);
}


// Função para calcular a soma de todos os elementos da árvore
int Soma(arvore r) {
    if (vazia(r)) {
        return 0; // Caso base: árvore vazia, soma é 0
    } else {
        // Soma o valor do nó atual com as somas das subárvores esquerda e direita
        return r->info + Soma(r->esq) + Soma(r->dir);
    }
}



int Soma_Intervalo(arvore r, int a, int b) {
    if (vazia(r)) {
        return 0; // Caso base: árvore vazia, soma é 0
    }
    
    // Inicializa a soma
    int soma = 0;
    
    // Se o valor do nó atual for maior que a, pode haver nós na subárvore esquerda dentro do intervalo
    if (r->info > a) {
        soma += Soma_Intervalo(r->esq, a, b);
    }
    
    // Se o valor do nó atual estiver dentro do intervalo, adiciona à soma
    if (r->info >= a && r->info <= b) {
        soma += r->info;
    }
    
    // Se o valor do nó atual for menor que b, pode haver nós na subárvore direita dentro do intervalo
    if (r->info < b) {
        soma += Soma_Intervalo(r->dir, a, b);
    }
    
    return soma;
}






int main(){
    arvore r = NULL;
    r = inserir(r, 20);
    r = inserir(r, 30);
    r = inserir(r, 10);
    r = inserir(r, 5);
    r = inserir(r, 35);
    r = inserir(r, 28);
    r = inserir(r, 25);
    r = inserir(r, 40);
    r = inserir(r, 1);
    
    printf("In ordem:");
    in_ordem(r);
    printf("\n");
    
    printf("Intervalo:");
    imprimir_intervalo( r, 10, 28);
    printf("\n");
    
    int tot = conta_no_interno(r);
    printf("no interno: %d\n", tot);
    
    printf("pre ordem formatado:");
    pre_ordem(r);
    printf("\n");
    
    printf("por nivel:\n");
    imprimir_por_niveis_recursivo(r);
    printf("\n");
    
    int filho = conta_no_FilhoUnico(r);
    printf("filho: %d\n", filho);
    
    int seguinte = chave_seguinte(r, 30);
     printf("Seguinte: %d\n", seguinte);
    
    int soma = Soma(r);
     printf("Soma: %d\n", soma);
     
       int soma_intervalo = Soma_Intervalo(r, 9, 28);
     printf("Soma Intervalo: %d\n", soma_intervalo);
     
    return 0;
}