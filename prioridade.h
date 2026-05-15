#ifndef PRIORIDADE_H
#define PRIORIDADE_H

#include "common.h"

typedef struct Node Node;
typedef struct FilaPrioridade FilaPrioridade;

struct Node {
    Paciente *paciente;
    struct Node *next;
};

struct FilaPrioridade {
    Node *head;
    int total_pacientes;
};

FilaPrioridade* criar_fila();
void inserir_na_fila(FilaPrioridade *f, Paciente *p);
Paciente* remover_da_fila(FilaPrioridade *f);

#endif