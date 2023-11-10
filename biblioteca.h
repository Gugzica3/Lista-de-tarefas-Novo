//
// Created by gug on 19/09/2023.
//

#ifndef PROJETO1_BIBLIOTECA_H
#define PROJETO1_BIBLIOTECA_H

#define MAX_TAREFAS 100

struct Tarefa {
    int prioridade;
    char descricao[300];
    char categoria[100];
    int ndtarefa;
    char estado[300];
};

void salvarTarefa(struct Tarefa tarefas[], int nTarefas);
void lerTarefas(struct Tarefa tarefas[], int *nTarefas);
void cadastrarTarefa(struct Tarefa tarefas[], int *nTarefas);
void listarTarefas(struct Tarefa tarefas[], int *nTarefas);
void deletarTarefa(struct Tarefa tarefas[], int *nTarefas, int indice);
void editar(struct Tarefa *tarefas, const int *nTarefas);
void fprioridade(struct Tarefa tarefas[], const int *nTarefas);
void festado(struct Tarefa tarefas[], int *nTarefas);
void fcategoria(struct Tarefa tarefas[],int *nTarefas);
void fcateridade (struct Tarefa tarefas[],int *nTarefas);
void exportaprio(struct Tarefa tarefas[], int *nTarefas);
void exportacat(struct Tarefa tarefas[], int *nTarefas);
void exportacatprio(struct Tarefa tarefas[], int *nTarefas);
void exportar(struct Tarefa tarefas[], int *nTarefas);
#endif //PROJETO1_BIBLIOTECA_H
