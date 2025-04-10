#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"

#define tam 10
#define MAX_LINHA 512  // Aumentado para prevenir buffer overflow

void processar_numeros(const char *entrada, int *saida, int *quantidade) {
    char temp[50];
    strcpy(temp, entrada);

    // Remover '{' e '}'
    if (temp[0] == '{') {
        memmove(temp, temp + 1, strlen(temp));
        temp[strlen(temp) - 1] = '\0';
    }

    // Tokenizar e converter nÃºmeros
    char *token = strtok(temp, ",");
    *quantidade = 0;
    while (token != NULL && *quantidade < 50) {
        saida[*quantidade] = atoi(token);
        (*quantidade)++;
        token = strtok(NULL, ",");
    }
}

int main() {
    ids process[tam];
    int i = 0;
    FILE *processos = fopen("processos.csv", "r");
    if (processos == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char linha[MAX_LINHA]; // Buffer aumentado
    if (fgets(linha, sizeof(linha), processos) == NULL) { 
        perror("Erro ao ler o cabeÃ§alho");
        fclose(processos);
        return 1;
    }

    while (fgets(linha, sizeof(linha), processos) != NULL && i < tam) {
        char quant_classe[50] = "";
        char quant_assunto[50] = "";

        process[i].classe_quant = 0;
        process[i].assunto_quant = 0;

        // Lendo os valores com sscanf
        int valoresLidos = sscanf(linha, "%lld,\"%49[^\"]\",%49[^,],\"%49[^\"]\",%49[^,],%d",
            &process[i].id, process[i].numero, process[i].data_ajuizamento,
            quant_classe, quant_assunto, &process[i].ano_eleicao);

        if (valoresLidos < 6) {
            printf("Formato de linha incorreto ou incompleto (linha %d), pulando...\n", i + 1);
            continue;
        }

        // Processar classe
        processar_numeros(quant_classe, process[i].classe, &process[i].classe_quant);

        // Processar assunto
        processar_numeros(quant_assunto, process[i].assunto, &process[i].assunto_quant);

        i++;
    }

    fclose(processos);
    ordem_crescente(process, i);
    printarray(process, i);

    return 0;
}