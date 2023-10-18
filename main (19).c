#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int num;
    struct no *ant;
    struct no *prox;
} Lista;

int vazia(Lista *l) {
    return (l == NULL);
}

void limparLista(Lista *l) {
    if (vazia(l)) return;
    
    Lista *atual = l;
    Lista *proximo;

    do {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    } while (atual != l);
}

void imprimir(Lista *l) {
    if (vazia(l)) return;

    Lista *atual = l;

    do {
        printf("%d ", atual->num);
        atual = atual->prox;
    } while (atual != l);

    printf("\n");
}

Lista* inserir_cabeca(Lista *l, int num) {
    Lista *aux = (Lista*) malloc(sizeof(Lista));
    aux->num = num;
    aux->ant = NULL;
    aux->prox = NULL;

    if (!vazia(l)) {
        aux->ant = l->ant;
        l->ant->prox = aux;
        l->ant = aux;
        aux->prox = l;
    } else {
        aux->ant = aux;
        aux->prox = aux;
        return aux;
    }

    return aux;
}

Lista* inserir_cauda(Lista *l, int num) {
    Lista *aux = (Lista*) malloc(sizeof(Lista));
    aux->num = num;
    aux->ant = NULL;
    aux->prox = NULL;

    if (!vazia(l)) {
        aux->ant = l->ant;
        l->ant->prox = aux;
        l->ant = aux;
        aux->prox = l;
    } else {
        aux->ant = aux;
        aux->prox = aux;
        return aux;
    }

    return l;
}

Lista* remover(Lista *l, int num) {
    if (l == NULL) {
        // Se a lista estiver vazia, não há nada para remover
        return NULL;
    }

    // Caso base: Se o elemento for encontrado na cabeça, remova-o
    if (l->num == num) {
        Lista *proximo = l->prox;

        if (l->prox == l) {
            // Se houver apenas um nó na lista, libere-o e retorne NULL
            free(l);
            return NULL;
        } else {
            // Caso contrário, ajuste os ponteiros para remover a cabeça
            l->ant->prox = l->prox;
            l->prox->ant = l->ant;
            free(l);
            return proximo; // Retorna o próximo nó como a nova cabeça da lista
        }
    }

    // Caso recursivo: Chama a função para o próximo nó
    l->prox = remover(l->prox, num);

    return l; // Retorna o nó atual (pode ter sido alterado ou não)
}

int conta_elementos(Lista *l) {
    if (l == NULL)
        return 0;

    int count = 0;
    Lista *current = l;

    do {
        count++;
        current = current->prox;
    } while (current != l);

    return count;
}

Lista* inverter(Lista *l) {
    if (vazia(l))
        return NULL;

    Lista *aux = NULL;
    Lista *atual = l;

    do {
        aux = inserir_cabeca(aux, atual->num);
        atual = atual->prox;
    } while (atual != l);

    return aux;
}

Lista* concatenar(Lista *l1, Lista *l2) {
    if (vazia(l1) && vazia(l2)) {
        return NULL;
    }

    Lista *aux = NULL;
    Lista *atual1 = l1;
    Lista *atual2 = l2;

    if (!vazia(l1)) {
        do {
            aux = inserir_cauda(aux, atual1->num);
            atual1 = atual1->prox;
        } while (atual1 != l1);
    }

    if (!vazia(l2)) {
        do {
            aux = inserir_cauda(aux, atual2->num);
            atual2 = atual2->prox;
        } while (atual2 != l2);
    }

    return aux;
}

Lista* intercalar(Lista *l1, Lista *l2) {
    if (vazia(l1) && vazia(l2)) {
        return NULL; // Não há o que ser feito
    }

    Lista *aux = NULL;
    Lista *atual_l1 = l1;
    Lista *atual_l2 = l2;

    do {
        if (atual_l1 != NULL) {
            aux = inserir_cauda(aux, atual_l1->num);
            atual_l1 = atual_l1->prox;
        }
        if (atual_l2 != NULL) {
            aux = inserir_cauda(aux, atual_l2->num);
            atual_l2 = atual_l2->prox;
        }

    } while (atual_l1 != l1 || atual_l2 != l2);

    return aux;
}

int main() {
    Lista *l1 = NULL;
    Lista *l2 = NULL;
    Lista *l3 = NULL;
    Lista *l4 = NULL;
    Lista *l5 = NULL;

    printf("Lista 1 é vazia? RESPOSTA: %d\n\n", vazia(l1));
    l1 = inserir_cabeca(l1, 10);
    l1 = inserir_cabeca(l1, 20);
    l1 = inserir_cabeca(l1, 30);
    l1 = inserir_cabeca(l1, 40);

    l2 = inserir_cauda(l2, 50);
    l2 = inserir_cauda(l2, 60);
    l2 = inserir_cauda(l2, 70);
    l2 = inserir_cauda(l2, 80);
    l2 = inserir_cauda(l2, 90);

    printf("Lista 1: ");
    imprimir(l1);
    printf("\n");

    printf("Lista 2: ");
    imprimir(l2);
    printf("\n");

    l1 = remover(l1, 10);
    l1 = remover(l1, 40);

    printf("Lista 1 com remoção: ");
    imprimir(l1);
    printf("\n");


    printf("Número de elementos em l2: %d\n", conta_elementos(l2));

    l3 = inverter(l2);

    printf("Lista 3 = Lista 2 invertida: ");
    imprimir(l3);
    printf("\n");

    l4 = intercalar(l1, l2);

    printf("Lista 4 = Lista 1 e 2 intercaladas: ");
    imprimir(l4);
    printf("\n");

    l5 = concatenar(l4, l2);

    printf("Lista 5 = Lista 4 e 2 concatenadas: ");
    imprimir(l5);
    printf("\n");

    printf("Lista 1 é vazia? RESPOSTA: %d\n\n", vazia(l1));

    limparLista(l1);
    limparLista(l2);
    limparLista(l3);
    limparLista(l4);
    limparLista(l5);
    l1 = NULL;
    l2 = NULL;
    l3 = NULL;
    l4 = NULL;
    l5 = NULL;

    printf("Lista 1 é vazia? RESPOSTA: %d\n\n", vazia(l1));

    return 0;
}
