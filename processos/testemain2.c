#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"

//#define tam 2201
#define MAX_LINHA 1024

int main() {
    ids2 *process = NULL;
    int i = 0, capacidade = 100;
    FILE *processos = fopen("processos.csv", "r");
    if (processos == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    process = (ids2 *)malloc(capacidade * sizeof(ids2));
    if (process == NULL) {
        perror("Erro ao alocar memória");
        fclose(processos);
        return 1;
    }

    char linha[MAX_LINHA];
    char cabecalho[MAX_LINHA];  

  
    if (fgets(cabecalho, sizeof(cabecalho), processos) == NULL) {
        perror("Erro ao ler o cabeçalho");
        fclose(processos);
        free(process);
        return 1;
    }

    printf("Cabeçalho: %s\n", cabecalho);  

    while (fgets(linha, sizeof(linha), processos) != NULL) {
        if (i >= capacidade) {
            capacidade *= 2;
            ids2 *temp = (ids2 *)realloc(process, capacidade * sizeof(ids2));
            if (temp == NULL) {
                perror("Erro ao realocar memória");
                free(process);
                fclose(processos);
                return 1;
            }
            process = temp;
        }

        int classe_aspas = 0, assunto_aspas = 0, campo_agora = 0, j = 0;
        char classe_char[50] = {0};
        char assunto_char[50] = {0};

        process[i].classe[0] = 0;
        process[i].classe[1] = 0;
        process[i].classe[2] = 0;
        process[i].classe[3] = 0;
        process[i].classe[4] = 0;        
        process[i].assunto[0] = 0;
        process[i].assunto[1] = 0;
        process[i].assunto[2] = 0;
        process[i].assunto[3] = 0;
        process[i].assunto[4] = 0;
        char classe_str[50], assunto_str[50];

        char *token=NULL;

        fgets(linha, sizeof(linha), processos);
        
        token = strtok(linha, ","); // ID
        process[i].id = atoll(token);
        
        token = strtok(NULL, ","); // Numero
        strcpy(process[i].numero, token);
        
        token = strtok(NULL, "-"); // Ano
        process[i].ano = atoi(token);
        
        token = strtok(NULL, "-"); // Mês
        process[i].mes = atoi(token);
        
        token = strtok(NULL, " "); // Dia
        process[i].dia = atoi(token);
        
        token = strtok(NULL, ":"); // Hora
        process[i].hora = atoi(token);
        
        token = strtok(NULL, ":"); // Minuto
        process[i].minuto = atoi(token);
        
        token = strtok(NULL, "."); // Segundo
        process[i].segundo = atoi(token);
        
        token = strtok(NULL, "}"); // Classe (string)
        strcpy(classe_str, token);
        
        token = strtok(NULL, "}"); // Assunto (string)
        strcpy(assunto_str, token);
        
        token = strtok(NULL, ","); // Ano eleição
        process[i].ano_eleicao = atoi(token); 

        remover_aspas(process[i].numero);
        limpar_formatacao(classe_str);
        limpar_formatacao(assunto_str);

        int k = 0;
        token = strtok(classe_str, ",");
        while (token != NULL && k < 4) {
            process[i].classe[k++] = atoi(token);
            token = strtok(NULL, ",");
        }

        int z = 0;
        token = strtok(assunto_str, ",");
        while (token != NULL && z < 4) {
            process[i].assunto[z++] = atoi(token);
            token = strtok(NULL, ",");
        }

        i++;

        }     

    fclose(processos);

    int escolha = 0;

    printf("________________________________________\n");
    printf("Analisando o arquivo processos.csv...\n");
    printf("________________________________________\n");
    printf("Escolha uma das 6 opcoes para analisar o arquivo:\n");
    printf("[1] = imprimir\n[2] = ordernar em forma crescente\n[3] = ordernar em forma decrescente\n[4] = listar processos com 2 assuntos\n[5] = listar todos os tipos de assuntos\n[6] = listar o numero de processos em cada classe\n");
    scanf("%d",&escolha);
    
    switch (escolha)
    {
    case 1:
        printarray(process, i);
        break;
    
    case 2:
        ordem_crescente(process,i);
        printf("Arquivo de ordem crescente criado com sucesso! De uma olhada!");
        break;

    case 3:
        ordem_decrescente(process,i);
        printf("Arquivo de ordem decrescente criado com sucesso! De uma olhada!");
        break;

    case 4:
        dois_assuntos(process, i);
        break;

    case 5:
        tipos_assuntos(process, i);
        break;

    case 6:
        listar_processos_classes(process,i);
        break;
    }
    
    free(process);

    return 0;
    }