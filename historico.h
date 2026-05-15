#ifndef HISTORICO_H
#define HISTORICO_H

#include "common.h"

typedef struct StackNode {
    Paciente *paciente;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} Pilha;

Pilha* criar_pilha();
void push_historico(Pilha *s, Paciente *p);
Paciente* pop_historico(Pilha *s);

#endif