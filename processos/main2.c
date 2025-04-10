#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"

#define tam 18392

int main() {
    ids2 id[tam];
    int i = 0;
    FILE *processos = fopen("processos.csv", "r");
    if (processos == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char linha[1024];
    if (fgets(linha, sizeof(linha), processos) == NULL) { // LÃª o cabeÃ§alho
        perror("Erro ao ler o cabeÃ§alho");
        fclose(processos);
        return 1;
    }

    while (fgets(linha, sizeof(linha), processos) != NULL) {
        char *token;

        // Pegar o ID (removendo a aspas inicial)
        token = strtok(linha, ",");
        if (token == NULL) continue;
        sscanf(token, "\"%d", &id[i].id);  

        // Pegar o nÃºmero do processo
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        sscanf(token, "\"\"%20[^\"]\"\"", id[i].numero);

        // Pegar a data de ajuizamento
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(id[i].data_ajuizamento, token, sizeof(id[i].data_ajuizamento) - 1);
        id[i].data_ajuizamento[sizeof(id[i].data_ajuizamento) - 1] = '\0';

        // Pegar o id_classe (removendo as chaves {})
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        sscanf(token, "{%d", &id[i].id_classe);

        // Pegar o id_assunto (removendo as chaves {})
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        sscanf(token, "{%d}", &id[i].id_assunto);

        // Pegar o ano_eleicao
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        id[i].ano_eleicao = atoi(token);

        i++;  // Incrementa o contador de registros lidos
    }

    fclose(processos);

    // Chamar a ordenaÃ§Ã£o e imprimir
    ordem_crescente2(id, i);
    printarray2(id, i);

    return 0;
}