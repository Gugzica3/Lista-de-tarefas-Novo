//
// Created by gug on 19/09/2023.
//

#include "biblioteca.h"
#include <stdio.h>
#include <string.h>

void salvarTarefa(struct Tarefa tarefas[], int nTarefas) {
    FILE *arquivo;
    arquivo = fopen("tarefas.bin", "wb");

    if (arquivo != NULL) {
        fwrite(tarefas, sizeof(struct Tarefa), nTarefas, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo .\n");
    }
}
// Na função SALVAR-TAREFA abre o arquivo "tarefas.bin" em modo de escrita binária ,escreve as tarefas no arquivo usando fwrite e fecha o arquivo.
// Se o arquivo não puder ser aberto, uma mensagem de erro é exibida.



void lerTarefas(struct Tarefa tarefas[], int *nTarefas) {
    FILE *arquivo;
    arquivo = fopen("tarefas.bin", "rb");

    if (arquivo != NULL) {
        fseek(arquivo, 0, SEEK_END);
        long tamanhoArquivo = ftell(arquivo);
        *nTarefas = tamanhoArquivo / sizeof(struct Tarefa);

        fseek(arquivo, 0, SEEK_SET);
        fread(tarefas, sizeof(struct Tarefa), *nTarefas, arquivo); // Lê os dados do arquivo
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo para leitura.\n");
    }
}
//A função "lerTarefas" abre o arquivo "tarefas.bin", olha para as tarefas dentro dele,
// lê cada uma das tarefas dentro do arquivo
// ele move o indicador de posição do arquivo para determinar o seu tamanho,
// divide pelo tamanho da "struct Tarefa" para obter o número de tarefas,
// lendo essas tarefas no array "tarefas" e, finalmente, fechando o arquivo.



void cadastrarTarefa(struct Tarefa tarefas[], int *nTarefas) {
    if (*nTarefas < MAX_TAREFAS) {
        struct Tarefa novaTarefa;
        printf("Qual a prioridade da tarefa (0-10): ");
        scanf("%d", &novaTarefa.prioridade);

        printf("Descreva a tarefa: ");
        scanf(" %[^\n]", novaTarefa.descricao);

        printf("Informe a categoria da tarefa: ");
        scanf(" %[^\n]", novaTarefa.categoria);

        int Hestado = 0;
        //Segura o estado em formato de número para o cliente não ter que escrever o estado da tarefa
        printf("Informe a estado da tarefa:\n 1.Completo\n 2.Em andamento\n 3.Nao iniciado\n  ");
        scanf("%d", &Hestado);

        if (Hestado == 1) {
            strcpy(novaTarefa.estado, "Completo");
        } else if (Hestado == 2) {
            strcpy(novaTarefa.estado, "Em andamento");
        } else if (Hestado == 3) {
            strcpy(novaTarefa.estado, "Nao iniciado");
        }


        novaTarefa.ndtarefa = *nTarefas + 1;

        tarefas[*nTarefas] = novaTarefa;
        (*nTarefas)++;
        salvarTarefa(tarefas, *nTarefas);
        printf("Tarefa cadastrada com sucesso!\n");
    } else {
        printf("A lista de tarefas está cheia. Não é possível cadastrar mais tarefas.\n");
    }
}
//A função verifica se a lista de tarefas não está cheia (MAX_TAREFAS).
// Se houver espaço disponível salvamos uma nova tarefa aumentamndo o contador de tarefas em 1 para saber que temos mais uma tarefa na lista.



void listarTarefas(struct Tarefa tarefas[], int *nTarefas) {
    printf("Lista de Tarefas:\n");
    for (int i = 0; i < *nTarefas; i++) {
        printf("Tarefa %d\n", tarefas[i].ndtarefa);
        printf("Prioridade: %d\n", tarefas[i].prioridade);
        printf("Descricao: %s\n", tarefas[i].descricao);
        printf("Categoria: %s\n", tarefas[i].categoria);
        printf("Estado: %s\n", tarefas[i].estado);
        printf("\n");
    }
    int opcao;
    while (1) {
        printf("Escolha uma opcao:\n");
        printf("1. Editar tarefa\n");
        printf("2. Filtrar por prioridade\n");
        printf("3. Filtrar por estado\n");
        printf("4. Filtrar por categoria\n");
        printf("5. Filtrar por categoria e prioridade\n");
        printf("6. Sair\n");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                editar(tarefas, nTarefas);
                return;
            case 2:
                fprioridade(tarefas, nTarefas);
                return;
            case 3:
                festado(tarefas, nTarefas);
                return;
            case 4:
                fcategoria(tarefas, nTarefas);
                return;
            case 5:
                fcateridade(tarefas, nTarefas);
                return;
            case 6:
                return;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                return;
        }

    }
}

//Essa função mostra uma lista de tarefas. Ela imprime cada tarefa na tela, uma por uma.
// Para cada tarefa, mostra a prioridade, a descrição e a categoria.



void deletarTarefa(struct Tarefa tarefas[], int *nTarefas, int indice) {
    if (indice >= 0 && indice < *nTarefas) {
        for (int i = indice; i < *nTarefas - 1; i++) {
            tarefas[i] = tarefas[i + 1];
        }
        (*nTarefas)--;
        salvarTarefa(tarefas, *nTarefas); // Salva as tarefas no arquivo após deletar uma
        printf("Tarefa deletada com sucesso!\n");
    } else {
        printf("Índice de tarefa inválido.\n");
    }
}

//Primeiro ela verifica se o número que você escolheu para a tarefa está dentro dos limites da lista.
// Se estiver, ela remove a tarefa, deslocando todas as outras tarefas uma posição para trás, preenchendo o espaço vazio.
// Em seguida, ela diminui o contador de tarefas em 1 para refletir a exclusão e salva a lista atualizada no arquivo

//FILTROS


//Edita as tarefas
void editar(struct Tarefa *tarefas, const int *nTarefas) {
    int op;
    int tarefaedit;
    int nestado;
    printf("Qual o id da tarefa que voce quer editar?\n");
    scanf("%d", &tarefaedit);
    // - 1 pois o id da tarefa anteriormente foi adicionado 1 para fins de embelezamento
    tarefaedit = tarefaedit - 1;

    printf("Qual funcao voce quer editar?\n");
    printf("1. editar prioridade\n");
    printf("2. editar estado\n");
    printf("3. editar categoria\n");
    printf("4. editar descricao\n");
    printf("5. voltar\n");
    scanf("%d", &op);

    switch (op) {
        case 1:
            printf("Qual a nova prioridade?");
            scanf("%d", &tarefas[tarefaedit].prioridade);
            return;
        case 2:
            printf("Informe o novo estado da tarefa:\n 1.Completo\n 2.Em andamento\n 3.Nao iniciado\n  ");
            scanf("%d", &nestado);

            if (nestado == 1) {
                strcpy(tarefas[tarefaedit].estado, "Completo");
            } else if (nestado == 2) {
                strcpy(tarefas[tarefaedit].estado, "Em andamento");
            } else if (nestado == 3) {
                strcpy(tarefas[tarefaedit].estado, "Nao iniciado");
            }
            return;
        case 3:
            printf("Qual a nova categoria?");
            scanf("%s", tarefas[tarefaedit].categoria);
            return;
        case 4:
            printf("Qual a nova descricao?");
            scanf("%s", tarefas[tarefaedit].descricao);
            return;
    }
}


// filtra por prioridade
void fprioridade(struct Tarefa tarefas[], const int *nTarefas) {
    int filtro;
    printf("Qual prioridade voce quer filtrar?\n");
    scanf("%d", &filtro);
    for (int i = 0; i < *nTarefas; i++) {
        if (tarefas[i].prioridade == filtro) {
            printf("Tarefa %d\n", tarefas[i].ndtarefa);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Descricao: %s\n", tarefas[i].descricao);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Estado: %s\n", tarefas[i].estado);
            printf("\n");
        }

    }

}

// filtra por estado
void festado(struct Tarefa tarefas[], int *nTarefas) {
    int filtro;
    char filtroL[20];
    printf("Qual estado voce quer filtrar?\n 1.Completo\n 2.Em andamento\n 3.Nao iniciado\n");
    scanf("%d", &filtro);

    if (filtro == 1) {
        strcpy(filtroL, "Completo");
    } else if (filtro == 2) {
        strcpy(filtroL, "Em andamento");
    } else if (filtro == 3) {
        strcpy(filtroL, "Nao iniciado");
    }

    for (int i = 0; i < *nTarefas; i++) {
        if (strcmp(tarefas[i].estado, filtroL) == 0) {
            printf("Tarefa %d\n", tarefas[i].ndtarefa);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Descricao: %s\n", tarefas[i].descricao);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Estado: %s\n", tarefas[i].estado);
            printf("\n");
        }
    }
}

// filtra por categoria
void fcategoria(struct Tarefa tarefas[], int *nTarefas) {

    char filtro[100];

    printf("Qual categoria voce quer filtrar?\n");
    scanf("%s", filtro);
    getchar();

    for (int i = 0; i < *nTarefas; i++) {
        if (strcmp(tarefas[i].categoria, filtro) == 0) {
            printf("Tarefa %d\n", tarefas[i].ndtarefa);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Descricao: %s\n", tarefas[i].descricao);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Estado: %s\n", tarefas[i].estado);
            printf("\n");
        }
    }
}

// cateridade = categoria-prioridade
void fcateridade(struct Tarefa tarefas[], int *nTarefas) {

    char filtro[100];

    printf("Qual categoria voce quer filtrar?\n");
    scanf("%s", filtro);
    getchar();

    int filtroP;
    printf("Qual prioridade voce quer filtrar?\n");
    scanf("%d", &filtroP);

    for (int i = 0; i < *nTarefas; i++) {
        if (strcmp(tarefas[i].categoria, filtro) == 0 && tarefas[i].prioridade == filtroP) {
            printf("Tarefa %d\n", tarefas[i].ndtarefa);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Descricao: %s\n", tarefas[i].descricao);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Estado: %s\n", tarefas[i].estado);
            printf("\n");
        }
    }
}

// EXPORTAÇÕES
void exportaprio(struct Tarefa tarefas[], int *nTarefas) {
    int filtro;
    printf("Qual prioridade voce quer exportar?\n");
    scanf("%d", &filtro);

    FILE *arqprio;
    arqprio = fopen("prioridade.txt", "wb");

    if (arqprio != NULL) {
        for (int i = 0; i < *nTarefas; i++) {
            if (tarefas[i].prioridade == filtro) {
                fprintf(arqprio, "%d, %s, %s, %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado,
                        tarefas[i].descricao);
            }
        }
        fclose(arqprio);
        printf("Tarefas com prioridade %d exportadas com sucesso para o arquivo 'prioridade.txt'.\n", filtro);
    }
    else {
        printf("Erro ao criar o arquivo de exportacao.\n");
    }
}

void exportacat(struct Tarefa tarefas[], int *nTarefas) {
    char filtro[100];
    printf("Qual categoria voce quer exportar?\n");
    scanf("%s", filtro);

    FILE *arqcat;
    arqcat = fopen("categoria.txt", "wb");

    if (arqcat != NULL) {
        for (int i = 0; i < *nTarefas; i++) {
            if (strcmp(tarefas[i].categoria, filtro) == 0) {
                fprintf(arqcat, "%d, %s, %s, %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado,
                        tarefas[i].descricao);
            }
        }
        fclose(arqcat);
        printf("Tarefas com categorias %s exportadas com sucesso para o arquivo 'categoria.txt'.\n", filtro);
    } else {
        printf("Erro ao criar o arquivo de exportacao.\n");
    }
}


void exportacatprio(struct Tarefa tarefas[], int *nTarefas) {
    char filtroC[100];
    printf("Qual categoria voce quer exportar?\n");
    scanf("%s", filtroC);

    int filtroP;
    printf("Qual prioridade voce quer exportar?\n");
    scanf("%d", &filtroP);


    FILE *arqcat;
    arqcat = fopen("categoria_e_prioridade.txt", "wb");

    if (arqcat != NULL) {
        for (int i = 0; i < *nTarefas; i++) {
            if (tarefas[i].prioridade == filtroP && strcmp(tarefas[i].categoria, filtroC) == 0) {
                fprintf(arqcat, "%d, %s, %s, %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado,
                        tarefas[i].descricao);
            }
        }
        fclose(arqcat);
        printf("Tarefas com prioridade %d e categorias %s exportadas com sucesso para o arquivo 'categoria_e_prioridade.txt'.\n",
               filtroP, filtroC);
    } else {
        printf("Erro ao criar o arquivo de exportacao.\n");
    }
}

void exportar(struct Tarefa tarefas[], int *nTarefas) {
    int opcao;
    printf("Qual funcao voce quer editar?\n");
    printf("1. Exportar prioridade\n");
    printf("2. Exportar categoria\n");
    printf("3. Exportar categoria e prioridade\n");
    printf("4. Sair\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            exportaprio(tarefas, nTarefas);
            return;
        case 2:
            exportacat(tarefas, nTarefas);
            return;
        case 3:
            exportacatprio(tarefas, nTarefas);
            return;
        case 4:
            return;
    }
}
