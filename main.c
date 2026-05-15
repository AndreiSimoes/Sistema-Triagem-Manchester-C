#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "common.h"
#include "prioridade.h"
#include "historico.h"
#include "utils.h"

// Função que processa um arquivo específico e retorna o tempo gasto
double testar_arquivo(const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) {
        printf("Erro: Nao foi possivel abrir o arquivo %s\n", nome_arquivo);
        return -1.0;
    }

    FilaPrioridade *fila = criar_fila();
    Pilha *pilha = criar_pilha();
    char comando;

    // Marca o relógio inicial
    clock_t inicio = clock(); 

    while (fscanf(file, " %c", &comando) != EOF) {
        if (comando == 'E') {
            Paciente *novo = malloc(sizeof(Paciente));
            fscanf(file, "%d \"%[^\"]\" %u %ld", 
                   &novo->id, novo->nome, (unsigned int*)&novo->gravidade, &novo->hora_chegada);
            novo->grau_prioridade = (int)novo->gravidade;
            inserir_na_fila(fila, novo);
        } else if (comando == 'A') {
            Paciente *atendido = remover_da_fila(fila);
            if (atendido) {
                atendido->hora_atendimento = time(NULL);
                push_historico(pilha, atendido);
            }
        } else if (comando == 'D') {
            Paciente *errado = pop_historico(pilha);
            if (errado) {
                errado->grau_prioridade = -1; // Sênior: Volta ao início com prioridade máxima
                inserir_na_fila(fila, errado);
            }
        }
    }

    // Marca o relógio final
    clock_t fim = clock(); 

    fclose(file);
    
    // Libera a memória para não vazar e agradar o Valgrind
    limpar_sistema(fila, pilha); 

    // Calcula a diferença de tempo e converte para segundos
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

int main() {
    printf("Iniciando testes de performance...\n\n");

    // Testa os três arquivos que o seu gerador criou
    double tempo_100 = testar_arquivo("teste_100.txt");
    double tempo_1000 = testar_arquivo("teste_1000.txt");
    double tempo_10000 = testar_arquivo("teste_10000.txt");

    // Imprime a tabela de resultados exigida no trabalho
    printf("\n======================================================\n");
    printf("           TABELA DE TEMPO DE EXECUCAO                \n");
    printf("======================================================\n");
    printf("| %-20s | %-12s | %-12s |\n", "Arquivo", "Operacoes", "Tempo (s)");
    printf("------------------------------------------------------\n");
    
    if (tempo_100 >= 0)
        printf("| %-20s | %-12d | %-12.6f |\n", "teste_100.txt", 100, tempo_100);
    if (tempo_1000 >= 0)
        printf("| %-20s | %-12d | %-12.6f |\n", "teste_1000.txt", 1000, tempo_1000);
    if (tempo_10000 >= 0)
        printf("| %-20s | %-12d | %-12.6f |\n", "teste_10000.txt", 10000, tempo_10000);
        
    printf("======================================================\n");

    return 0;
}