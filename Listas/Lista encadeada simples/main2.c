#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int info;
    struct no *prox;
}Lista;

Lista * insere_na_cabeça(Lista *l, int info){
    Lista *aux = (Lista*) malloc(sizeof(Lista));
    aux->info = info;
    aux->prox = l;
    return aux;
}

void printLista(Lista *l){
    if(l != NULL){
        printf("%d ",l->info);
        return printLista(l->prox);
    }
}

Lista * insere_no_final(Lista *l, int info){
    Lista *aux = (Lista*) malloc(sizeof(Lista));
    aux->info = info;
    Lista *p = l;
    aux->prox = NULL;
    if(l == NULL){
        l = aux;
        return l;
    }
    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = aux;
    
    return l;
}

Lista * insere_pos(Lista *l,int info,int pos){
    Lista *aux = (Lista *) malloc(sizeof(Lista));
    Lista *p = l;
    Lista *ant = NULL;
    int cont = 0;
    aux->info = info;
    if(pos == 0){
        aux->prox = l;
        return aux;
    }
    
    while(p != NULL && cont < pos){ //5 3 1 12
        ant = p;                    //ant = 3
        p = p->prox;                // p = 1
        cont++;                    //cont = 2
    } 
    
    aux->prox = p;                  //aux->prox = 1 12
    if(ant != NULL){
        ant->prox = aux;            //3-10-1-12
    }
    
    return l;
}

Lista * remover(Lista *l,int info){
    Lista * ant = l;
    Lista * p = l;
    
    while(p != NULL && p->info != info){
        ant = p;
        p = p->prox;   
    }
    
    if(p != NULL){
        if(p == l) l = l->prox;
        else{
            ant->prox = p->prox;
        }
        free(p);
    }
    
    return l;
    
}

Lista * removerTodasOcorrencias(Lista * l,int info){
    Lista * aux; 
    
    while(l != NULL && l->info == info){
        aux = l;
        l = l->prox;
        free(aux);
    }
    
    Lista* p = (l != NULL) ? l->prox : NULL;
    Lista * ant = l;
    
    while(p != NULL){
        if(p->info == info){
            aux = p;
            ant->prox = p->prox;
            p = p->prox;
            free(aux);
        }
        ant = p;
        p = p->prox;
    }
    
    return l;
}

int qtd_total(Lista * l){
    int qtd = 0;
    while(l != NULL){
        qtd++;
        l = l->prox;
    }
    
    return qtd;
}

int qtd_total_recursivo(Lista * l){
    int qtd = 0;
    if(l != NULL){
        qtd ++;
        qtd += qtd_total_recursivo(l->prox);
    }
    
    return qtd;
}

int pertence(Lista * l, int info){
    while(l != NULL){
        if(l->info == info) return 1;
        l = l->prox;
    }
    
    return 0;
}

int qtd_distintos(Lista * l){
    Lista * aux = (Lista*) malloc(sizeof(Lista));
    aux = NULL;
    Lista *p = l;
    int qtd = 0;
    while(p != NULL){
        if(!pertence(aux,p->info)){
            aux = insere_na_cabeça(aux,p->info);
        }
        p = p->prox;
    }
    
    while(aux != NULL){
        qtd++;
        aux = aux->prox;
    }
    
    return qtd;
}

int qtd_distintos_recursivo(Lista * l){
    Lista * aux = (Lista*) malloc(sizeof(Lista));
    aux = NULL;
    int qtd = 0;
    while(l != NULL){
        if(!pertence(aux,l->info)){ // 3 5 7 8 2
            aux = insere_na_cabeça(aux,l->info);
        }
        l = l->prox;
    }
    
    if(aux != NULL){
        qtd++;
        qtd += qtd_distintos_recursivo(aux->prox);
    }
    
    return qtd;
}

Lista * removeRepetidos(Lista * l){
    Lista * aux = (Lista*) malloc(sizeof(Lista));
    Lista *p = l;
    Lista *ant = NULL;
    while(p != NULL){
        if(!pertence(aux,p->info)){
            aux = insere_na_cabeça(aux,p->info);
        }else{
            ant->prox = p->prox;
            free(p);
            p = ant->prox;
        }
        
        ant = p;
        p = p->prox;
    }
    
    return l;
}

Lista * remocaoRepetidos(Lista *l) {
    Lista *p = l;
    
    
    while (p != NULL) {
        Lista *q = p;
        while (q->prox != NULL) {
            if (q->prox->info == p->info) {
                Lista *tmp = q->prox;
                q->prox = tmp->prox;
                free(tmp);
            } else {
                q = q->prox;
            }
        }
        p = p->prox;
    }

    return l;
}

int contaOcorrencias(Lista * l,int info){
    int qtd=0;
    while(l != NULL){
        if(l->info == info){
            qtd++;
        }
        l = l->prox;
    }
    
    return qtd;
}

int contaOcorrenciasRecursivo(Lista * l,int info){
    int qtd = 0;
    if(l == NULL) return 0;
    
    if(l->info == info){
        qtd++;
    }
    
    qtd += contaOcorrenciasRecursivo(l->prox,info);
    
    return qtd;
}

Lista * removeRepetidosInformado(Lista *l, int info){
    
    Lista *p = l;
    Lista *ant = NULL;
    int cont = 0;
    
    while(p != NULL){
        if(p->info == info){
            if(cont == 0){
                cont++;
                ant = p;
                p = p->prox;
            }else{
                ant->prox = p->prox;
                free(p);
                p = ant->prox;
            }  
        }else{
            ant = p;
            p = p->prox;
        }
    }
    
    return l;
}

int estaContido(Lista *l1, Lista *l2){
    if(l1 == NULL || l2 == NULL) return 0;
    
    while(l2 != NULL){
        if(pertence(l1,l2->info)){
            l2 = l2->prox;
        }else{
            return 0;
        }
    }
    
    return 1;
}

Lista * somar(Lista *l1, Lista *l2){
    Lista * aux = (Lista*) malloc(sizeof(Lista));
    aux = NULL;
    int soma;
    
    while(l1 != NULL || l2 != NULL){
        if(l1 != NULL && l2 != NULL){
            soma = l1->info + l2->info;
            aux = insere_no_final(aux,soma);
            l1 = l1->prox;
            l2 = l2->prox;
        }
        if(l1 == NULL && l2 != NULL){
            soma = l2->info;
            aux = insere_no_final(aux,soma);
            l2 = l2->prox;
        }
        if(l1 != NULL && l2 == NULL){
            soma = l1->info;
            aux = insere_no_final(aux,soma);
            l1 = l1->prox;
        }
    }
    
    return aux;
}

Lista * multiplicar(Lista *l1, Lista *l2){
    Lista * aux = (Lista*) malloc(sizeof(Lista*));
    int mult;
    aux = NULL;
    
    while(l1 != NULL || l2!=NULL){
        if(l1 != NULL && l2 != NULL){
            mult = l1->info * l2->info;
            aux = insere_no_final(aux,mult);
             l1 = l1->prox;
             l2 = l2->prox;
        }
        if(l1 == NULL && l2 != NULL){
            aux = insere_no_final(aux,l2->info);
            l2 = l2->prox;
        }
        if(l1 != NULL && l2 == NULL){
            aux = insere_no_final(aux,l1->info);
            l1 = l1->prox;
        }
    }
    
    return aux;
}

Lista * intersecao(Lista *l1, Lista *l2){
    Lista * aux = (Lista*) malloc(sizeof(Lista));
    aux = NULL;
    
    while(l1 != NULL){
        if(pertence(l2,l1->info)){
            aux = insere_no_final(aux,l1->info);
            l1 = l1->prox;
        }else{
            l1 = l1->prox;
        }
        
    }
    
    return aux;
}

Lista * insereOrdenado(Lista *l,int info){
    Lista * aux = (Lista*) malloc(sizeof(Lista));
    aux->info = info;
    Lista *p = l;
    Lista *ant = NULL;
    
    if(l == NULL){
        aux->prox = NULL;
        l = aux;
        return aux;
    }
    
    if(aux->info < l->info){
        aux->prox = l;
        return aux;
    }
    
    while(p != NULL){
        if(aux->info < p->info){
            ant->prox = aux;
            aux->prox = p;
            return l;
        }
        
        ant = p;
        p = p->prox;
    }
    
    ant->prox = aux;
    aux = NULL;
    return l;
}

Lista * inverter(Lista * l){
    Lista * aux = (Lista*) malloc(sizeof(Lista));
    aux = NULL;
    
    while(l != NULL){
        aux = insere_na_cabeça(aux,l->info); 
        l = l->prox;
    }
    
    return aux;
}

Lista * intercalar(Lista * l1, Lista * l2){
    Lista * aux = (Lista*) malloc(sizeof(Lista));
    aux = NULL;
    
    while(l1 != NULL || l2 != NULL){
        if(l1 != NULL){
            aux = insere_no_final(aux,l1->info);
            l1 = l1->prox;
        }
        if(l2 != NULL){
            aux = insere_no_final(aux,l2->info);
            l2 = l2->prox;
        }
    }
    
    return aux;
}

Lista * concatenar(Lista * l1, Lista * l2){
    while(l2 != NULL){
        l1 = insere_no_final(l1,l2->info);
        l2 = l2->prox;
    }
    
    return l1;
}

Lista * concatenarSemFuncao(Lista * l1, Lista * l2){
    Lista *p = l1;
    
    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = l2;
    
    
    return l1;
}


int main()
{
    Lista *l,*l2,*l3;
    l = NULL;
    l2 = NULL;
    l3 = NULL;
    
    l = insere_na_cabeça(l,1); //5 3 1 12 7 12 1 6 8 3
    l = insere_na_cabeça(l,3); 
    l = insere_na_cabeça(l,1);
    l = insere_no_final(l,3);
    l = insere_no_final(l,7);
    l = insere_no_final(l,3);
    l = insere_no_final(l,1);
    l = insere_no_final(l,6);
    l = insere_no_final(l,2);
    //l = insere_pos(l,2,2);
    
    //l2 = insere_na_cabeça(l2,3);
    l2 = insere_no_final(l2,6);
    l2 = insere_no_final(l2,12);
    l2 = insere_no_final(l2,10);
    l2 = insere_no_final(l2,14);
    
    l3 = insereOrdenado(l3,1);
    l3 = insereOrdenado(l3,10);
    l3 = insereOrdenado(l3,4);
    
    //l = remover(l,23);
    
    /* removeRepetidos
    printLista(l);
    printf("\n\n%d\n",qtd_total(l));
    printf("%d\n",qtd_distintos(l));
    printf("%d\n\n",qtd_distintos_recursivo(l));
    l = removeRepetidos(l);
    //l = insere_pos(l,10,2);
    */
    
    /* removeRepetidosInformado
    printLista(l);
    l = removeRepetidosInformado(l,1);
    printf("\n\n");
    */
    
    printLista(l);
    printf("\n\n");
    printLista(removerTodasOcorrencias(l,1));
    //printLista(remocaoRepetidos(l));
    //printf("\n\n");
    //printLista(l2);
    //printf("\n\n");
    //printLista(somar(l,l2));
    //printf("\n\n");
    //printLista(multiplicar(l,l2));
    //printf("\n\n");
    //printLista(intersecao(l,l2));
    //printf("\n\n");
    //printLista(l3);
    //printf("\n\n");
    //printLista(inverter(l));
    //printf("\n\n");
    //printLista(intercalar(l,l2));
    //printf("\n\n");
    //printLista(concatenar(l,l2));
    //printf("\n\n");
    //printLista(concatenarSemFuncao(l,l2));
    
    
    
    //printf("\n\n%d\n",qtd_total(l));
    //printf("%d\n",qtd_distintos(l));
    //printf("%d\n",qtd_distintos_recursivo(l));
    //printf("%d\n",contaOcorrenciasRecursivo(l,1));
    //printf("%d\n",qtd_total_recursivo(l));
    /*if(estaContido(l,l2)){
        printf("Esta contido");
    }else printf("nao esta contido");*/
    
    return 0;
}
