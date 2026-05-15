#ifndef COMMON_H
#define COMMON_H
#include <time.h>

typedef enum {
    EMERGENCIA = 0,      // Vermelho
    MUITO_URGENTE = 1,   // Laranja
    URGENTE = 2,         // Amarelo
    POUCO_URGENTE = 3,   // Verde
    NAO_URGENTE = 4      // Azul
} Gravidade;

typedef struct {
    int id;
    char nome[100];
    Gravidade gravidade;
    int grau_prioridade; 
    time_t hora_chegada;
    time_t hora_atendimento;
} Paciente;

#endif