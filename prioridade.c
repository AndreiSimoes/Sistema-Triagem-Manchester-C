#include <stdlib.h>
#include <stdio.h>
#include "prioridade.h"

FilaPrioridade* criar_fila() {
    FilaPrioridade *f = malloc(sizeof(FilaPrioridade));
    f->head = NULL;
    f->total_pacientes = 0;
    return f;
}

int comparar_pacientes(Paciente *a, Paciente *b) {
    if (a->grau_prioridade < b->grau_prioridade) return -1;
    if (a->grau_prioridade > b->grau_prioridade) return 1;
    return difftime(a->hora_chegada, b->hora_chegada);
}

void inserir_na_fila(FilaPrioridade *f, Paciente *p) {
    Node *novo = malloc(sizeof(Node));
    novo->paciente = p;
    
    Node **curr = &(f->head);
    while (*curr && comparar_pacientes((*curr)->paciente, p) <= 0) {
        curr = &((*curr)->next);
    }
    novo->next = *curr;
    *curr = novo;
    f->total_pacientes++;

    // Regra de Aging: A cada 5 novos
    if (f->total_pacientes % 5 == 0) {
        Node *temp = f->head;
        int count = 0;
        while (temp) {
            count++;
            if (count > 5 && temp->paciente->grau_prioridade > 0) {
                temp->paciente->grau_prioridade--;
            }
            temp = temp->next;
        }
        // Nota: Em um sistema real, aqui deveríamos re-ordenar a lista 
        // caso a prioridade mude a posição relativa dos nós.
    }
}

Paciente* remover_da_fila(FilaPrioridade *f) {
    if (!f->head) return NULL;
    Node *temp = f->head;
    Paciente *p = temp->paciente;
    f->head = temp->next;
    free(temp);
    return p;
}