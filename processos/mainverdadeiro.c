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

        while (linha[j] != '\0') {
            if (linha[j] == ',') {
                campo_agora++;
            }
            if (linha[j] == '"' && linha[j + 1] == '{') {
                if (campo_agora == 3) {
                    classe_aspas++;
                } 
                
                else if (campo_agora == 4) {
                    assunto_aspas++;
                }
                else if (campo_agora >=5) {
                    assunto_aspas++;
                }
            }
            j++;
        }

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
        char classe_str[50], assunto_str[50], anoeleicao_str[10];

        if (classe_aspas == 1 && assunto_aspas == 0) {
            sscanf(linha, "%lld,%49[^,],%d-%d-%d %d:%d:%d.000,\"{%49[^\"]}\",%49[^,],%9s",
                       &process[i].id,
                       process[i].numero,
                       &process[i].ano,
                       &process[i].mes,
                       &process[i].dia,
                       &process[i].hora,
                       &process[i].minuto,
                        &process[i].segundo,
                       classe_str,
                        assunto_str,
                       anoeleicao_str);
            }
        else if (assunto_aspas == 1 && classe_aspas == 0) {
            sscanf(linha, "%lld,%49[^,],%d-%d-%d %d:%d:%d.000,%49[^,],\"{%49[^\"]}\",%9s",
                       &process[i].id,
                       process[i].numero,
                       &process[i].ano,
                       &process[i].mes,
                       &process[i].dia,
                       &process[i].hora,
                       &process[i].minuto,
                       &process[i].segundo,
                       classe_str,
                        assunto_str,
                        anoeleicao_str);
            }
        else if (assunto_aspas == 1 && classe_aspas == 1) {
            sscanf(linha, "%lld,%49[^,],%d-%d-%d %d:%d:%d.000,\"{%49[^}]}\",\"{%49[^}]}\",%9s",
                       &process[i].id,
                       process[i].numero,
                       &process[i].ano,
                       &process[i].mes,
                       &process[i].dia,
                       &process[i].hora,
                       &process[i].minuto,
                       &process[i].segundo,
                       classe_str,
                        assunto_str,
                       anoeleicao_str);
            }
        else if(assunto_aspas == 0 && classe_aspas == 0) {
            sscanf(linha, "%lld,%49[^,],%d-%d-%d %d:%d:%d.000,%49[^,],%49[^,],%9s",
                       &process[i].id,
                       process[i].numero,
                       &process[i].ano,
                       &process[i].mes,
                       &process[i].dia,
                       &process[i].hora,
                       &process[i].minuto,
                       &process[i].segundo,
                       classe_str,
                        assunto_str,
                       anoeleicao_str);
            }

        process[i].ano_eleicao = atoi(anoeleicao_str);
        remover_aspas(process[i].numero);
        limpar_formatacao(classe_str);
        limpar_formatacao(assunto_str);

        int k = 0;
        char *token = strtok(classe_str, ",");
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
    printf("[1] = imprimir\n[2] = ordernar em forma crescente por ID\n[3] = ordernar em forma decrescente por data de ajuizamento\n[4] = listar processos com 2 assuntos\n[5] = listar todos os tipos de assuntos\n[6] = listar o numero de processos em cada classe\n");
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