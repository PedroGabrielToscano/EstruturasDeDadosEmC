#include <stdio.h>

// Função de busca linear
int busca_linear(int arr[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {
        if (arr[i] == chave) {
            return i;
        }
    }
    return -1;
}

// Função de busca binária (para arrays ordenados)
int busca_binaria(int arr[], int tamanho, int chave) {
    int e = 0;
    int d = tamanho - 1, m;
    while (e <= d) {
        m = (e + d) / 2;
        if (chave < arr[m]) {
            d = m - 1;
        } else if (chave > arr[m]) {
            e = m + 1;
        } else {
            return m;
        }
    }
    return -1;
}

int main() {
    // Array ordenado para a busca binária
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int tamanho = sizeof(arr) / sizeof(arr[0]);
    int chave;
    
    printf("Digite um número para buscar: ");
    scanf("%d", &chave);

    // Busca Linear
    int indice_linear = busca_linear(arr, tamanho, chave);
    if (indice_linear != -1) {
        printf("Busca Linear: %d encontrado na posição %d\n", chave, indice_linear);
    } else {
        printf("Busca Linear: %d não encontrado.\n", chave);
    }

    // Busca Binária
    int indice_binaria = busca_binaria(arr, tamanho, chave);
    if (indice_binaria != -1) {
        printf("Busca Binária: %d encontrado na posição %d\n", chave, indice_binaria);
    } else {
        printf("Busca Binária: %d não encontrado.\n", chave);
    }

    return 0;
}
