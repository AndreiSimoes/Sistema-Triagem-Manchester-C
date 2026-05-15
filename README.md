# 🏥 Sistema de Triagem Médica (Protocolo de Manchester)

Este projeto é um simulador desenvolvido em **linguagem C** para gerir o fluxo de pacientes em uma Unidade de Pronto Atendimento (UPA), utilizando o Protocolo de Manchester para classificar a gravidade clínica.

## 🛠️ Estruturas de Dados Utilizadas
- **Fila de Prioridade (Lista Encadeada):** Organiza os pacientes com base no grau de emergência (0 a 4) e hora de chegada.
- **Pilha (LIFO):** Armazena o histórico dos pacientes recém-atendidos, permitindo a funcionalidade de "Desfazer Atendimento" em caso de erro médico.

## ✨ Funcionalidades
- Entrada de pacientes com classificação por cores (Emergência, Urgente, Pouco Urgente, etc.).
- **Regra de Aging (Antiestagnação):** A cada 5 novos pacientes na fila, o sistema aumenta a prioridade daqueles que estão aguardando há mais tempo, evitando que casos leves nunca sejam atendidos.
- **Função Desfazer:** Retorna o último paciente atendido diretamente para o topo da fila com prioridade máxima.

---

## 📊 Análise de Performance

O sistema possui um módulo de testes de carga nativo para medir a eficiência da nossa **Fila de Prioridade**. Como usamos uma Lista Encadeada simples, a inserção é ordenada (o algoritmo procura o lugar exato de acordo com a gravidade e o tempo de espera).

| Arquivo de Teste | Quantidade de Operações | Tempo Médio de Execução (s) |
| :--- | :--- | :--- |
| `teste_100.txt` | 100 | ~ 0.000000 |
| `teste_1000.txt` | 1.000 | ~ 0.002000 |
| `teste_10000.txt` | 10.000 | ~ 0.157000 |

**🔬 Conclusão do Teste:** A linguagem C é extremamente rápida, rodando 100 pacientes em tempo virtualmente nulo. No entanto, o tempo salta no arquivo de 10.000 pacientes porque a fila cresce significativamente. Toda vez que um paciente novo entra, o programa precisa "caminhar" por mais nós da fila para encontrar a posição correta dele, demonstrando na prática o que chamamos de **complexidade $O(N)$** no pior caso da inserção.

---

## 🛠️ Como Compilar e Executar

Para rodar este projeto na sua máquina, você precisa ter um compilador de linguagem C instalado (como o **GCC**).

**Passo 1: Baixar o código**
Faça o clone deste repositório ou baixe os arquivos (`.c` e `.h`) e coloque-os em uma única pasta.

**Passo 2: Abrir o Terminal**
Abra o terminal (ou Prompt de Comando/PowerShell do VS Code) dentro da pasta onde você salvou os arquivos.

**Passo 3: Compilar o programa principal**
Digite o comando abaixo e aperte `Enter`. 
*(Entendendo o comando: O `gcc` chama o compilador para juntar todos os arquivos listados. O trecho `-o simulador` diz para ele transformar tudo isso em um programa executável chamado `simulador`).*
```bash
gcc main.c prioridade.c historico.c utils.c -o simulador
```

**Passo 4: Rodar o programa** 
Após compilar, digite o comando abaixo para ver o programa ler os arquivos e gerar a tabela de performance de tempo:
```bash
./simulador
```

## 🌟 BÔNUS

Se você quiser ver o sistema funcionando na prática (os pacientes entrando na recepção, sendo chamados pelo médico e a função "desfazer" acontecendo passo a passo na tela), nós temos um módulo visual!

Compile e rode usando estes comandos:
```bash
gcc simulacao_visual.c prioridade.c historico.c utils.c -o visual
./visual
```
