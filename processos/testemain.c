#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"

#define tam 4
#define MAX_LINHA 512

int main() {
    ids *process=NULL;
    int i = 0, capacidade=100;
    FILE *processos = fopen("processos.csv", "r+");
    if (processos == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    process = (ids *)malloc(capacidade * sizeof(ids));
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
            ids *temp = (ids *)realloc(process, capacidade * sizeof(ids));
            if (temp == NULL) {
                perror("Erro ao realocar memória");
                free(process);
                fclose(processos);
                return 1;
            }
            process = temp;
        }
        printf("Lendo linha %d: %s", i + 1, linha); // Debug: Imprime a linha lida
        
        char quant_classe[50];
        char quant_assunto[50];

        process[i].classe_quant = 0;
        process[i].assunto_quant = 0;



        // Nesse if, as classes e assuntos possuem somente 1 negocio dentro das chaves
        int valoresLidos = sscanf(linha, "%lld,%49[^,],%d-%d-%d %d:%d:%d.000,%49[^,],%49[^,],%d",
            &process[i].id, process[i].numero, &process[i].ano, &process[i].mes,
            &process[i].dia, &process[i].hora, &process[i].minuto, &process[i].segundo,
            quant_classe, quant_assunto, &process[i].ano_eleicao);

            //printf("%s 1 vez em\n", quant_classe);
            //printf("%s 1 vez em\n", quant_assunto); 
 
            char ultimo = quant_assunto[strlen(quant_assunto) - 1];
        // Nesse if, somente as classes possuem mais de 1 negocio dentro das chaves 
        if (quant_assunto[0] == '"') {
            printf("Erro na leitura da linha (tentando formato simples)...\n");
            valoresLidos = sscanf(linha, "%lld,%49[^,],%d-%d-%d %d:%d:%d.000,%49[^,],\"%49[^\"]\",%d",
                &process[i].id, process[i].numero, &process[i].ano, &process[i].mes,
            &process[i].dia, &process[i].hora, &process[i].minuto, &process[i].segundo,
                quant_classe, quant_assunto, &process[i].ano_eleicao);

                printf("%s 2 vez em\n", quant_classe);  
                printf("%s 2 vez em\n", quant_assunto); 
                char ultimo = quant_assunto[strlen(quant_assunto) - 1];
        }

        if (quant_classe[0] == '"' && ultimo != '}') {
            printf("Erro na leitura da linha (tentando formato complexa)...\n");
            valoresLidos = sscanf(linha, "%lld,%49[^,],%d-%d-%d %d:%d:%d.000,\"%49[^\"]\",%49[^,],%d",
                &process[i].id, process[i].numero, &process[i].ano, &process[i].mes,
            &process[i].dia, &process[i].hora, &process[i].minuto, &process[i].segundo,
                quant_classe, quant_assunto, &process[i].ano_eleicao);

                printf("%s 3 vez em\n", quant_classe); 
                printf("%s 3 vez em\n", quant_assunto);
                char ultimo = quant_assunto[strlen(quant_assunto) - 1];
        }

        if (quant_assunto[0] == '"' && ultimo != '}') {
            printf("Erro na leitura da linha (tentando formato super complexa)...\n");
            valoresLidos = sscanf(linha, "%lld,%49[^,],%d-%d-%d %d:%d:%d.000,\"%49[^\"]\",\"%49[^\"]\",%d",
                &process[i].id, process[i].numero, &process[i].ano, &process[i].mes,
            &process[i].dia, &process[i].hora, &process[i].minuto, &process[i].segundo,
                quant_classe, quant_assunto, &process[i].ano_eleicao);

                printf("%s 4 vez em\n", quant_classe); 
                printf("%s 4 vez em\n", quant_assunto);
                char ultimo = quant_assunto[strlen(quant_assunto) - 1];
        }

        


        // Remover as chaves {} dos valores (tanto para quant_classe quanto quant_assunto)
        if (quant_classe[0] == '{') {
            memmove(quant_classe, quant_classe + 1, strlen(quant_classe)); // Remove '{'
            quant_classe[strlen(quant_classe) - 1] = '\0'; // Remove '}'
        }
        if (quant_assunto[0] == '{') {
            memmove(quant_assunto, quant_assunto + 1, strlen(quant_assunto)); // Remove '{'
            quant_assunto[strlen(quant_assunto) - 1] = '\0'; // Remove '}'
        }

        // Tokenizar e preencher a classe (ajustando a leitura)
        if (strlen(quant_classe) > 0) {
            char *token = strtok(quant_classe, ",");
            while (token != NULL && process[i].classe_quant < 50) {  // Limitar ao tamanho máximo de 50
                process[i].classe[process[i].classe_quant] = atoi(token);  // Converter para inteiro
                process[i].classe_quant++;
                token = strtok(NULL, ",");
            }
        }

        // Tokenizar e preencher o assunto (ajustando a leitura)
        if (strlen(quant_assunto) > 0) {
            char *token = strtok(quant_assunto, ",");
            while (token != NULL && process[i].assunto_quant < 50) {  // Limitar ao tamanho máximo de 50
                process[i].assunto[process[i].assunto_quant] = atoi(token);  // Converter para inteiro
                process[i].assunto_quant++;
                token = strtok(NULL, ",");
            }
        }

        

        i++;
    }

    

    fclose(processos);
    printarray2(process, i);
    
   
    return 0;
}