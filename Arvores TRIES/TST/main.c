#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noTST{
    char letra;
    int valor;
    struct noTST *menor;
    struct noTST *igual;
    struct noTST *maior;
} noTST;

typedef noTST* arvoreTST;

void inserir(arvoreTST *raiz, char *str, int valor){
    if(*str){
        if(*raiz == NULL){
            *raiz = (noTST*) malloc(sizeof(noTST));
            (*raiz)->letra = *str;
            (*raiz)->valor = -1;
            (*raiz)->igual = NULL;
            (*raiz)->menor = NULL;
            (*raiz)->maior = NULL;
            inserir(&(*raiz)->igual, str+1, valor);
            if(*(str+1) == '\0')
                (*raiz)->valor = valor;
        }
        else{
            if(*str < (*raiz)->letra)
                inserir(&(*raiz)->menor, str, valor);
            else
                if(*str > (*raiz)->letra)
                    inserir(&(*raiz)->maior, str, valor);
                else{
                    inserir(&(*raiz)->igual, str+1, valor);
                    if(*(str+1) == '\0')
                        (*raiz)->valor = valor;
                }
        }
    }
}

int buscar(arvoreTST raiz, char *str){
    if(*str){
        if(raiz != NULL){
            if(raiz->letra == *str){
                if(*(str+1) == '\0' && raiz->valor != -1)
                    return raiz->valor;
                return buscar(raiz->igual, str+1);
            }
            if(*str < raiz->letra)
                return buscar(raiz->menor, str);
            if(*str > raiz->letra)
                return buscar(raiz->maior, str);
        }
    }
    return -1;
}

void remover(arvoreTST *raiz, char *str){
    if(*str){ // talvez retirar esta verificacao, ja esta sendo verificado na ultima letra da palavra!!!
        if(*raiz != NULL){
            if(*str < (*raiz)->letra)
                remover(&(*raiz)->menor, str);
            else
                if(*str > (*raiz)->letra)
                    remover(&(*raiz)->maior, str);
                else
                    if((*raiz)->letra == *str){
                        if(*(str+1) == '\0' && (*raiz)->valor != -1)
                            (*raiz)->valor = -1;
                        else
                            remover(&(*raiz)->igual, str+1);
                    }
            if(((*raiz)->menor == NULL) && ((*raiz)->igual == NULL) && ((*raiz)->maior == NULL) && ((*raiz)->valor == -1)){
                free(*raiz);
                *raiz = NULL;
            }
        }
    }
}

void imprimirDicionarioAux(arvoreTST raiz, char *base, char *str){
    if(raiz != NULL){
        imprimirDicionarioAux(raiz->menor, base, str);
        *str = raiz->letra;
        if(raiz->valor != -1){
            *(str+1) = '\0';
            printf("%s\n", base);
        }
        imprimirDicionarioAux(raiz->igual, base, str+1);
        imprimirDicionarioAux(raiz->maior, base, str);
    }
}

void prefixoMaisLongoAux(arvoreTST r,char * str, char * prefix,int idx){
    if(*str){
        if(r != NULL){
            if(/*M*/r->letra == *str/*N*/){
                prefix[idx] = *str;  //prefix[0,1] = CA
                prefix[idx+1] = '\0'; //prefix[2] = \0
                if(*(str+1) == '\0') printf("%s\n",prefix);
                prefixoMaisLongoAux(r->igual, str+1,prefix,idx+1);   
            }
            else{ //CANELA
                if(*str /*N*/ > r->letra /*M*/){
                    prefixoMaisLongoAux(r->maior,str,prefix,idx);
                }
                else{
                    prefixoMaisLongoAux(r->menor,str,prefix,idx);
                }
            }
        }else{
            printf("%s\n",prefix);
        }
    }
}

void prefixoMaisLongo(arvoreTST r, char * str){
    char prefix[100] = "\0";
    prefixoMaisLongoAux(r,str,prefix,0);
}

void imprimirDicionario(arvoreTST raiz){
    char str[50] = "\0";
    imprimirDicionarioAux(raiz, str, str);
}

int main(){
    arvoreTST raiz = NULL;

    inserir(&raiz, "PALMEIRAS", 9);
    inserir(&raiz, "DADINHO", 10);
    inserir(&raiz, "DAD", 123);
    inserir(&raiz, "PALMEIRA", 11);
    inserir(&raiz, "PALESTRA", 12);

    inserir(&raiz, "PAI", 1);
    inserir(&raiz, "PAIS", 2);
    inserir(&raiz, "PATA", 3);
    inserir(&raiz, "CAMA", 4);       //C
    inserir(&raiz, "RAIO", 5);       //A
    inserir(&raiz, "RISO", 6);       //M
    inserir(&raiz, "RUA", 7);        //A
    inserir(&raiz, "TETO", 8);

    //imprimirDicionario(raiz);
    //printf("\n");

    //printf("string = %d\n", buscar(raiz, "DADINHO"));

    /*remover(&raiz, "RUA");
    remover(&raiz, "PAI");
    remover(&raiz, "PAIS");
    remover(&raiz, "PATA");
    remover(&raiz, "CAMA");
    remover(&raiz, "RAIO");
    remover(&raiz, "RISO");
    remover(&raiz, "TETO");*/

    //printf("string = %d\n", buscar(raiz, "DAD"));
    
    prefixoMaisLongo(raiz,"CANELA");

    //imprimirDicionario(raiz);
    //printf("\n");

    return 0;
}