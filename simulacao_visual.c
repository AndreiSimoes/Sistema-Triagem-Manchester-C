#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"
#include "prioridade.h"
#include "historico.h"
#include "utils.h"

// Função para deixar a gravidade escrita bonitinha na tela
const char* nome_gravidade(int g) {
    switch(g) {
        case 0: return "EMERGENCIA (Vermelho)";
        case 1: return "MUITO URGENTE (Laranja)";
        case 2: return "URGENTE (Amarelo)";
        case 3: return "POUCO URGENTE (Verde)";
        case 4: return "NAO URGENTE (Azul)";
        default: return "DESCONHECIDO";
    }
}

int main() {
    printf("\n======================================================\n");
    printf("        SIMULADOR VISUAL - TRIAGEM MANCHESTER         \n");
    printf("======================================================\n\n");

    // Vamos ler aquele arquivo pequeno "teste.txt" que criamos lá no começo
    FILE *file = fopen("teste.txt", "r");
    if (!file) {
        printf("Erro: Arquivo teste.txt nao encontrado!\n");
        return 1;
    }

    FilaPrioridade *fila = criar_fila();
    Pilha *pilha = criar_pilha();
    char comando;

    while (fscanf(file, " %c", &comando) != EOF) {
        if (comando == 'E') {
            Paciente *novo = malloc(sizeof(Paciente));
            fscanf(file, "%d \"%[^\"]\" %u %ld", 
                   &novo->id, novo->nome, (unsigned int*)&novo->gravidade, &novo->hora_chegada);
            novo->grau_prioridade = (int)novo->gravidade;
            
            printf("[ENTRADA] Paciente '%s' chegou na recepcao.\n", novo->nome);
            printf("          -> Triagem: %s\n\n", nome_gravidade(novo->gravidade));
            inserir_na_fila(fila, novo);
            
        } else if (comando == 'A') {
            Paciente *atendido = remover_da_fila(fila);
            if (atendido) {
                atendido->hora_atendimento = time(NULL);
                printf("[ATENDIMENTO] O medico chamou o paciente: '%s'\n", atendido->nome);
                printf("              -> Indo para a sala de atendimento...\n\n");
                push_historico(pilha, atendido);
            } else {
                printf("[ATENDIMENTO] O medico chamou, mas a fila esta vazia.\n\n");
            }
            
        } else if (comando == 'D') {
            Paciente *errado = pop_historico(pilha);
            if (errado) {
                printf("[ALERTA - DESFAZER] Ops! Erro no atendimento do paciente '%s'.\n", errado->nome);
                printf("                    -> Retornando para o TOPO da fila com prioridade MAXIMA!\n\n");
                errado->grau_prioridade = -1; // Regra Sênior
                inserir_na_fila(fila, errado);
            } else {
                printf("[DESFAZER] Nenhum atendimento recente para desfazer.\n\n");
            }
        }
    }

    fclose(file);
    printf("======================================================\n");
    printf("           FIM DA SIMULACAO DOS PACIENTES             \n");
    printf("======================================================\n");
    
    limpar_sistema(fila, pilha);
    return 0;
}