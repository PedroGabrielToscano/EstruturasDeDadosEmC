#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------
   TAD de Lista Encadeada Simples em C
   ------------------------------------------------------ */

typedef int TipoItem;

typedef struct no {
    TipoItem info;
    struct no* prox;
} Lista;

/* ---------- 1. Criar lista vazia  ---------- */
Lista* criarListaVazia() {
    return NULL;
}

/* ---------- 2. Inserir no início  ---------- */
Lista* insere_inicio(Lista *l, TipoItem info) {
    Lista* aux = (Lista*) malloc(sizeof(Lista));
    aux->info = info;
    aux->prox = l;
    return aux;
}

/* ---------- 3. Inserir no final  ----------- */
Lista* insere_final(Lista *l, TipoItem info) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->info = info;
    novo->prox = NULL;
    if(l == NULL) {
        return novo;
    }
    Lista* p = l;
    while(p->prox != NULL) {
        p = p->prox;
    }
    p->prox = novo;
    return l;
}

/* ---------- 4. Retirar (primeira ocorrência) ----------- */
Lista* retirar(Lista *l, TipoItem info) {
    Lista* ant = l;
    Lista* p = l;
    
    while(p != NULL && p->info != info) {
        ant = p;
        p = p->prox;
    }
    if(p != NULL) {
        // Achou o elemento
        if(p == l) {
            // Remove do início
            l = l->prox;
        } else {
            ant->prox = p->prox;
        }
        free(p);
    } else {
        printf("Elemento %d nao encontrado\n", info);
    }
    return l;
}

/* ---------- 5. Imprimir lista ---------- */
void imprime_lista(Lista *l) {
    if(l == NULL) {
        printf("Lista vazia\n");
        return;
    }
    Lista* p = l;
    printf("[");
    while(p != NULL) {
        printf("%d", p->info);
        if(p->prox != NULL) {
            printf(", ");
        }
        p = p->prox;
    }
    printf("]\n");
}

/* ---------- 6. pertence (auxiliar para qtd_distintos) ---------- */
int pertence(Lista *l, TipoItem info) {
    if(l == NULL) {
        return 0;
    }
    if(l->info == info) {
        return 1;
    }
    return pertence(l->prox, info);
}

/* ---------- 7. qtd_distintos (recursivo) ---------- 
   Conta cada valor apenas na sua última ocorrência.
*/
int qtd_distintos(Lista *l) {
    if(l == NULL) {
        return 0;
    }
    if(pertence(l->prox, l->info)) {
        // Se o valor atual aparece mais à frente, não contamos agora
        return qtd_distintos(l->prox);
    } else {
        // Se não aparece mais, contamos +1
        return 1 + qtd_distintos(l->prox);
    }
}

/* ---------- 8. elimina_repetidos ----------
   Remove duplicatas, mantendo a primeira ocorrência.
*/
Lista* elimina_repetidos(Lista *l) {
    Lista *p = l, *q, *temp;
    while(p != NULL) {
        q = p;
        while(q->prox != NULL) {
            if(q->prox->info == p->info) {
                // Remove duplicado
                temp = q->prox;
                q->prox = q->prox->prox;
                free(temp);
            } else {
                q = q->prox;
            }
        }
        p = p->prox;
    }
    return l;
}

/* ---------- 9. qtd_menores (recursivo) ----------
   Retorna a quantidade de elementos menores que 'a'.
*/
int qtd_menores(Lista *l, int a) {
    if(l == NULL) {
        return 0;
    }
    if(l->info < a) {
        return 1 + qtd_menores(l->prox, a);
    } else {
        return qtd_menores(l->prox, a);
    }
}

/* ---------- 10. obter_sublista_intervalo (por valor) ----------
   Retorna uma nova lista com os elementos cujo valor está em [a, b].
   A lista original não é modificada; mantém a mesma ordem.
*/
Lista* obter_sublista_intervalo(Lista *l, int a, int b) {
    Lista* nova = criarListaVazia();
    Lista* p = l;
    while(p != NULL) {
        if(p->info >= a && p->info <= b) {
            nova = insere_final(nova, p->info);
        }
        p = p->prox;
    }
    return nova;
}

/* ---------- 11. somar_intervalo (recursivo, por valor) ----------
   Retorna a soma dos valores que estão em [limInf, limSup].
*/
int somar_intervalo(Lista *l, int limInf, int limSup) {
    if(l == NULL) {
        return 0;
    }
    if(l->info >= limInf && l->info <= limSup) {
        return l->info + somar_intervalo(l->prox, limInf, limSup);
    } else {
        return somar_intervalo(l->prox, limInf, limSup);
    }
}

/* ---------- 12. remove_multiplos (recursivo) ----------
   Remove nós cujo valor é múltiplo de 'a'.
*/
Lista* remove_multiplos(Lista *l, int a) {
    if(l == NULL) {
        return NULL;
    }
    // Se o valor do nó atual for múltiplo de 'a', removemos esse nó
    if(l->info % a == 0) {
        Lista* temp = l->prox;
        free(l);
        return remove_multiplos(temp, a);
    } else {
        // Caso contrário, mantemos o nó atual e chamamos recursivamente
        l->prox = remove_multiplos(l->prox, a);
        return l;
    }
}

/* ---------- 13. obter_sublista (por posições) ----------
   Retorna uma nova lista com os elementos que ocupam as posições [pos1, pos2].
   A posição 0 corresponde à cabeça da lista.
*/
Lista* obter_sublista(Lista *l, int pos1, int pos2) {
    if(pos1 > pos2) {
        // Intervalo inválido
        return criarListaVazia();
    }
    Lista* nova = criarListaVazia();
    Lista* p = l;
    int i = 0;
    
    // Percorre a lista até chegar no fim ou até pos2
    while(p != NULL && i <= pos2) {
        if(i >= pos1) {
            nova = insere_final(nova, p->info);
        }
        p = p->prox;
        i++;
    }
    return nova;
}

/* ------------------------------------------------------
   Função principal (main) com exemplos de uso
   ------------------------------------------------------ */
int main() {
    /* =====================================================
       Exemplo 1: Lista com elementos repetidos
       ===================================================== */
    Lista* l1 = criarListaVazia();
    // l1 = [7, 11, 5, 11, 3, 8, 7, 5, 9, 11, 3, 3]
    int valores1[] = {7, 11, 5, 11, 3, 8, 7, 5, 9, 11, 3, 3};
    int n1 = sizeof(valores1)/sizeof(valores1[0]);
    for(int i = 0; i < n1; i++){
        l1 = insere_final(l1, valores1[i]);
    }
    
    printf("Lista 1 original:\n");
    imprime_lista(l1);
    
    // 1) qtd_distintos
    int dist = qtd_distintos(l1);
    printf("Quantidade de elementos distintos: %d\n", dist);
    
    // 2) elimina_repetidos
    l1 = elimina_repetidos(l1);
    printf("Lista 1 apos eliminar repetidos:\n");
    imprime_lista(l1);
    
    // 3) qtd_menores (ex: < 8)
    int menores = qtd_menores(l1, 8);
    printf("Quantidade de elementos < 8: %d\n", menores);
    
    // 4) somar_intervalo (ex: [5, 11])
    int somaInt = somar_intervalo(l1, 5, 11);
    printf("Soma dos valores em [5, 11]: %d\n", somaInt);
    
    // 5) remove_multiplos (ex: multiplos de 7)
    l1 = remove_multiplos(l1, 7);
    printf("Lista 1 apos remover multiplos de 7:\n");
    imprime_lista(l1);
    
    // 6) obter_sublista_intervalo (ex: [3, 9])
    Lista* subVal = obter_sublista_intervalo(l1, 3, 9);
    printf("Sublista de l1 com valores em [3, 9]:\n");
    imprime_lista(subVal);

    // 7) obter_sublista (por posicoes, ex: [0, 2])
    Lista* subPos = obter_sublista(l1, 0, 2);
    printf("Sublista de l1 (posicoes [0, 2]):\n");
    imprime_lista(subPos);

    /* =====================================================
       Exemplo 2: Lista para testar retirar e inserir
       ===================================================== */
    Lista* l2 = criarListaVazia();
    // l2 = [11, 7, 5, 9, 2, 6, 8, 1, 3, 15]
    int valores2[] = {11, 7, 5, 9, 2, 6, 8, 1, 3, 15};
    int n2 = sizeof(valores2)/sizeof(valores2[0]);
    for(int i = 0; i < n2; i++){
        l2 = insere_final(l2, valores2[i]);
    }
    
    printf("\nLista 2 original:\n");
    imprime_lista(l2);

    // retirar (ex: retirar 9)
    printf("Retirando 9...\n");
    l2 = retirar(l2, 9);
    imprime_lista(l2);

    // inserir no inicio
    printf("Inserindo 100 no inicio...\n");
    l2 = insere_inicio(l2, 100);
    imprime_lista(l2);

    // obter_sublista (posicoes [3, 7])
    Lista* subPos2 = obter_sublista(l2, 3, 7);
    printf("Sublista de l2 (posicoes [3, 7]):\n");
    imprime_lista(subPos2);

    /* =====================================================
       Final
       ===================================================== */
    printf("\nFim dos testes.\n");
    return 0;
}
