#include <stdlib.h>
#include "historico.h"

Pilha* criar_pilha() {
    Pilha *p = malloc(sizeof(Pilha));
    p->top = NULL;
    return p;
}

void push_historico(Pilha *s, Paciente *p) {
    StackNode *novo = malloc(sizeof(StackNode));
    novo->paciente = p;
    novo->next = s->top;
    s->top = novo;
}

Paciente* pop_historico(Pilha *s) {
    if (!s->top) return NULL;
    StackNode *temp = s->top;
    Paciente *p = temp->paciente;
    s->top = temp->next;
    free(temp);
    return p;
}