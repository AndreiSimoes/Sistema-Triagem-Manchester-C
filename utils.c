#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

void limpar_sistema(FilaPrioridade *f, Pilha *p) {
    // Limpar Fila
    Node *curr_f = f->head;
    while (curr_f) {
        Node *next = curr_f->next;
        free(curr_f->paciente);
        free(curr_f);
        curr_f = next;
    }
    free(f);

    // Limpar Pilha
    StackNode *curr_p = p->top;
    while (curr_p) {
        StackNode *next = curr_p->next;
        free(curr_p->paciente);
        free(curr_p);
        curr_p = next;
    }
    free(p);
    printf("[Sênior Log] Memória libertada com sucesso.\n");
}