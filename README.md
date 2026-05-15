# 🏥 Sistema de Triagem Médica (Protocolo de Manchester)

Este projeto é um simulador desenvolvido em **linguagem C** para gerir o fluxo de pacientes em uma Unidade de Pronto Atendimento (UPA), utilizando o Protocolo de Manchester para classificar a gravidade clínica.

## 🛠️ Estruturas de Dados Utilizadas
- **Fila de Prioridade (Lista Encadeada):** Organiza os pacientes com base no grau de emergência (0 a 4) e hora de chegada.
- **Pilha (LIFO):** Armazena o histórico dos pacientes recém-atendidos, permitindo a funcionalidade de "Desfazer Atendimento" em caso de erro médico.

## ✨ Funcionalidades
- Entrada de pacientes com classificação por cores (Emergência, Urgente, Pouco Urgente, etc.).
- **Regra de Aging (Antiestagnação):** A cada 5 novos pacientes na fila, o sistema aumenta a prioridade daqueles que estão aguardando há mais tempo.
- **Função Desfazer:** Retorna o último paciente atendido diretamente para o topo da fila com prioridade máxima.
- **Benchmark:** Gera e processa arquivos com 100, 1.000 e 10.000 atendimentos para calcular o tempo de execução e eficiência do algoritmo.

## 🚀 Como executar o projeto

1. Clone este repositório ou baixe os arquivos.
2. Abra o terminal na pasta do projeto e compile o código com o GCC:
```bash
gcc main.c prioridade.c historico.c utils.c -o simulador
