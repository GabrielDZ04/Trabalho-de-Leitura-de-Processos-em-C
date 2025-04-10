#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"

#define tam 15
#define MAX_LINHA 512

int main() {
    ids2 *process=NULL;
    int i = 0, capacidade=100;
    FILE *processos = fopen("processos.csv", "r");
    if (processos == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    process = (ids2 *)malloc(capacidade * sizeof(ids2));
    if (process == NULL) {
        perror("Erro ao alocar memória");
        return 1;
    }

    char linha[MAX_LINHA];
    if (fgets(linha, sizeof(linha), processos) == NULL) {
        perror("Erro ao ler o cabeçalho");
        fclose(processos);
        return 1;
    }

    while (fgets(linha, sizeof(linha), processos) != NULL && i < tam) {
        if(i >= capacidade) {
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
        
        char classe_str[50];
        char assunto_str[50];

        int classe_aspas=0, assunto_aspas=0, campo_agora=0, j=0;

        while (linha[j] != '\0') {
            if(linha[j]==','){
                campo_agora++;
            }
            if(linha[j]=='"' && linha[j]=='{'){
                if (campo_agora==3){
                    classe_aspas++;
                }

                else if(campo_agora==4){
                assunto_aspas++;
                }
            }

            j++;
        }

        if (classe_aspas==1 && assunto_aspas==0){
            sscanf(linha, "%lld,%49[^,],%49[^,],\"%49[^\"]\",%49[^,],%d",
                &process[i].id, 
                process[i].numero, 
                process[i].data_ajuizamento,
                classe_str, 
                assunto_str, 
                &process[i].ano_eleicao);
        } else if (assunto_aspas==1 && classe_aspas==0){
            sscanf(linha, "%lld,%49[^,],%49[^,],%49[^,],\"%49[^\"]\",%d",
                &process[i].id, 
                process[i].numero, 
                process[i].data_ajuizamento,
                classe_str, 
                assunto_str, 
                &process[i].ano_eleicao);
            
        } else if (assunto_aspas==1 && classe_aspas==1){
            sscanf(linha, "%lld,%49[^,],%49[^,],\"%49[^\"]\",\"%49[^\"]\",%d",
                &process[i].id, 
                process[i].numero, 
                process[i].data_ajuizamento,
                classe_str, 
                assunto_str, 
                &process[i].ano_eleicao);
            
        } else {
            sscanf(linha, "%lld,%49[^,],%49[^,],%49[^,],%49[^,],%d",
                &process[i].id, 
                process[i].numero, 
                process[i].data_ajuizamento,
                classe_str, 
                assunto_str, 
                &process[i].ano_eleicao);
            
        }

        remover_aspas(process[i].numero);

        sscanf(classe_str, "%d,%d", &process[i].classe[0], &process[i].classe[1]);
        sscanf(assunto_str, "%d,%d", &process[i].assunto[0], &process[i].assunto[1]);

        i++;
    }

    

    fclose(processos);
    printarray2(process,i);
    free(process);
   
    return 0;
}