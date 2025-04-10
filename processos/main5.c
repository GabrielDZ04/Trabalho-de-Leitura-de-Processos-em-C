#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"
#include "funcoes.h"

#define MAX_REGISTROS 100

int main() {
    FILE *arquivo = fopen("processos.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    ids pessoas[MAX_REGISTROS];
    int count = 0;
    char c;
    int index;

    while ((c = fgetc(arquivo)) != EOF && count < MAX_REGISTROS) {
        // Ler ID
        pessoas[count].id = 0;
        while (isdigit(c)) {
            pessoas[count].id = pessoas[count].id * 10 + (c - '0');
            c = fgetc(arquivo);
        }

        // Ler Número (pode estar entre aspas)
        index = 0;
        if (c == '"') c = fgetc(arquivo); // Ignora aspas iniciais
        while (c != ',' && c != EOF) {
            if (c == '"') { // Ignora aspas finais
                c = fgetc(arquivo);
                break;
            }
            if (index < sizeof(pessoas[count].numero) - 1) {
                pessoas[count].numero[index++] = c;
            }
            c = fgetc(arquivo);
        }
        pessoas[count].numero[index] = '\0';

        // Ler Data (formato: YYYY-MM-DD HH:MM:SS.sss)
        if (c == ',') c = fgetc(arquivo); // Ignora vírgula
        if (c != EOF) {
            int ano, mes, dia, hora, minuto, segundo;
            int lidos = sscanf(&c, "%d-%d-%d %d:%d:%d", &ano, &mes, &dia, &hora, &minuto, &segundo);
            if (lidos == 6) {
                pessoas[count].ano = ano;
                pessoas[count].mes = mes;
                pessoas[count].dia = dia;
                pessoas[count].hora = hora;
                pessoas[count].minuto = minuto;
                pessoas[count].segundo = segundo;
            }
            // Avança até a próxima vírgula ou final de linha
            while (c != ',' && c != '\n' && c != EOF) c = fgetc(arquivo);
        }

        // Ler Números dentro de chaves { } para classe
        pessoas[count].classe_num = 0;
        if (c == '"') c = fgetc(arquivo); // Ignora aspas antes das chaves
        if (c == '{') {
            while ((c = fgetc(arquivo)) != '}' && c != EOF) {
                if (isdigit(c)) {
                    int num = 0;
                    while (isdigit(c)) {
                        num = num * 10 + (c - '0');
                        c = fgetc(arquivo);
                    }
                    pessoas[count].classe[pessoas[count].classe_num++] = num;
                }
                if (c == ',') c = fgetc(arquivo); // Pula vírgulas
            }
        }

        // Ler Números dentro de chaves { } para assunto
        pessoas[count].assunto_num = 0;
        if (c == '"') c = fgetc(arquivo); // Ignora aspas antes das chaves
        if (c == '{') {
            while ((c = fgetc(arquivo)) != '}' && c != EOF) {
                if (isdigit(c)) {
                    int num = 0;
                    while (isdigit(c)) {
                        num = num * 10 + (c - '0');
                        c = fgetc(arquivo);
                    }
                    pessoas[count].assunto[pessoas[count].assunto_num++] = num;
                }
                if (c == ',') c = fgetc(arquivo); // Pula vírgulas
            }
        }

        // Ler Ano de Eleição
        if (c == ',') c = fgetc(arquivo); // Ignora vírgula
        if (c != EOF) {
            pessoas[count].ano_eleicao = 0;
            while (isdigit(c)) {
                pessoas[count].ano_eleicao = pessoas[count].ano_eleicao * 10 + (c - '0');
                c = fgetc(arquivo);
            }
        }

        // Avançar para a próxima linha
        while (c != '\n' && c != EOF) c = fgetc(arquivo);

        count++;
    }

    fclose(arquivo);

    // Exibir os dados lidos
    printarray(pessoas, count);

    return 0;
}
