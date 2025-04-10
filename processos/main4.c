#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"
#include "funcoes.h"

#define MAX_LINHA 512
#define MAX_NOME 50
#define INITIAL_CAPACITY 1024

int main() {
    ids *process = NULL;
    int contador = 0;
    int capacidade = INITIAL_CAPACITY;
    char c;

    // Allocate initial memory for the process array
    process = (ids *)malloc(capacidade * sizeof(ids));
    if (process == NULL) {
        perror("Erro ao alocar memória");
        return 1;
    }

    FILE *processos = fopen("processos.csv", "r+");
    if (processos == NULL) {
        perror("Erro ao abrir o arquivo");
        free(process);
        return 1;
    }

    char linha[MAX_LINHA];

    while ((c = fgetc(processos)) != EOF) {
        if (contador >= capacidade) {
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

        // Initialize the fields of the current process
        process[contador].id = 0;
        process[contador].ano = 0;
        process[contador].mes = 0;
        process[contador].dia = 0;
        process[contador].hora = 0;
        process[contador].minuto = 0;
        process[contador].segundo = 0;
        process[contador].classe_num = 0;
        process[contador].assunto_num = 0;
        process[contador].ano_eleicao = 0;
        memset(process[contador].numero, 0, sizeof(process[contador].numero));

        // Parse ID
        while (isdigit(c)) {
            process[contador].id = process[contador].id * 10 + (c - '0');
            c = fgetc(processos);
        }

        // Parse Numero (quoted string)
        if (c == ',') c = fgetc(processos); // Skip comma
        parse_quoted_string(processos, process[contador].numero, MAX_NOME);

        // Parse Data (YYYY-MM-DD HH:MM:SS.sss)
        if (c == ',') c = fgetc(processos); // Skip comma
        if (isdigit(c)) {
            process[contador].ano = 0;
            for (size_t i = 0; i < 4; i++) {
                process[contador].ano = process[contador].ano * 10 + (c - '0');
                c = fgetc(processos);
            }
            c = fgetc(processos); // Skip '-'

            process[contador].mes = 0;
            for (size_t i = 0; i < 2; i++) {
                process[contador].mes = process[contador].mes * 10 + (c - '0');
                c = fgetc(processos);
            }
            c = fgetc(processos); // Skip '-'

            process[contador].dia = 0;
            for (size_t i = 0; i < 2; i++) {
                process[contador].dia = process[contador].dia * 10 + (c - '0');
                c = fgetc(processos);
            }
            c = fgetc(processos); // Skip space

            process[contador].hora = 0;
            for (size_t i = 0; i < 2; i++) {
                process[contador].hora = process[contador].hora * 10 + (c - '0');
                c = fgetc(processos);
            }
            c = fgetc(processos); // Skip ':'

            process[contador].minuto = 0;
            for (size_t i = 0; i < 2; i++) {
                process[contador].minuto = process[contador].minuto * 10 + (c - '0');
                c = fgetc(processos);
            }
            c = fgetc(processos); // Skip ':'

            process[contador].segundo = 0;
            for (size_t i = 0; i < 2; i++) {
                process[contador].segundo = process[contador].segundo * 10 + (c - '0');
                c = fgetc(processos);
            }
            c = fgetc(processos); // Skip comma
        }

        // Parse Classe (array)
        if (c == ',') c = fgetc(processos); // Skip comma
        parse_array(processos, process[contador].classe, &process[contador].classe_num);

        // Parse Assunto (array)
        if (c == ',') c = fgetc(processos); // Skip comma
        parse_array(processos, process[contador].assunto, &process[contador].assunto_num);

        // Parse Ano Eleicao (optional)
        if (c == ',') c = fgetc(processos); // Skip comma
        process[contador].ano_eleicao = 0;
        while (isdigit(c)) {
            process[contador].ano_eleicao = process[contador].ano_eleicao * 10 + (c - '0');
            c = fgetc(processos);
        }

        contador++;
        while (c != EOF && c != '\n') {
            c = fgetc(processos);
        }
    }

    printarray(process, contador);
    fclose(processos);
    free(process);

    return 0;
}
