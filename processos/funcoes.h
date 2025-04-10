#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void ordem_crescente(ids2 *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].id > arr[j + 1].id) {
                ids2 temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    FILE *csv_crescente = fopen("processos_crescentes.csv", "w");
    FILE *processos = fopen("processos.csv", "r");

    char cabecalho[512];  
    if (fgets(cabecalho, sizeof(cabecalho), processos) == NULL) {
        perror("Erro ao ler o cabeçalho");
        fclose(processos);
    }
    fprintf(csv_crescente,"%s\n", cabecalho);
    fclose(processos); 

        for (int i = 0; i < n; i++) {
            fprintf(csv_crescente,"Registro %d:\n", i + 1);
            fprintf(csv_crescente,"ID: %lld\n", arr[i].id);
            fprintf(csv_crescente,"Numero: %s\n", arr[i].numero);
            fprintf(csv_crescente,"Data: %d-%d-%d %d:%d:%d\n", arr[i].ano,arr[i].mes,arr[i].dia,arr[i].hora,arr[i].minuto,arr[i].segundo);
    
            fprintf(csv_crescente,"Classe:");
            for (size_t j = 0; j < 4; j++)
            {
                if (arr[i].classe[j]==0){
                    continue;
                }
                else{
                    fprintf(csv_crescente,"%d ", arr[i].classe[j]);
                }
                
            }
    
            fprintf(csv_crescente,"\n");
    
            fprintf(csv_crescente,"Assunto:");
            for (size_t j = 0; j < 4; j++)
            {
                if (arr[i].assunto[j]==0){
                    continue;
                }
                else{
                    fprintf(csv_crescente,"%d ", arr[i].assunto[j]);
                }
                
            }
            
            fprintf(csv_crescente,"\n");
    
            if (arr[i].ano_eleicao==0)
            {
                fprintf(csv_crescente,"Ano Eleicao: 0\n");
            }
            else{
                fprintf(csv_crescente,"Ano eleicao: %d\n",arr[i].ano_eleicao);
            }
            
    
            int meses = (arr[i].mes - 1) * 30;
            int dias = arr[i].dia;
            int dias_passados = meses + dias;
            int dias_ano = 365 - dias_passados;
            int dias_restantes = (2025-(arr[i].ano+1)) * 365 + dias_ano;
            int dias_tramitado = (2025 - arr[i].ano_eleicao) * 365;
    
            if (arr[i].ano_eleicao==0)
            {
                fprintf(csv_crescente,"Dias tramitado: 0\n");
            }
            
            else{
                fprintf(csv_crescente,"Dias tramatido: %d\n",dias_tramitado);
            }
            fprintf(csv_crescente,"\n");
            fprintf(csv_crescente,"\n");
        }

    fclose(csv_crescente);
}

void ordem_decrescente(ids2 *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (
                arr[j].ano < arr[j + 1].ano ||
                (arr[j].ano == arr[j + 1].ano && arr[j].mes < arr[j + 1].mes) ||
                (arr[j].ano == arr[j + 1].ano && arr[j].mes == arr[j + 1].mes && arr[j].dia < arr[j + 1].dia) ||
                (arr[j].ano == arr[j + 1].ano && arr[j].mes == arr[j + 1].mes && arr[j].dia == arr[j + 1].dia && arr[j].hora < arr[j + 1].hora) ||
                (arr[j].ano == arr[j + 1].ano && arr[j].mes == arr[j + 1].mes && arr[j].dia == arr[j + 1].dia && arr[j].hora == arr[j + 1].hora && arr[j].minuto < arr[j + 1].minuto) ||
                (arr[j].ano == arr[j + 1].ano && arr[j].mes == arr[j + 1].mes && arr[j].dia == arr[j + 1].dia && arr[j].hora == arr[j + 1].hora && arr[j].minuto == arr[j + 1].minuto && arr[j].segundo < arr[j + 1].segundo)
            ) {
                ids2 temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    FILE *csv_decrescente = fopen("processos_decrescentes.csv", "w");
    FILE *processos = fopen("processos.csv", "r");

    char cabecalho[512];  
    if (fgets(cabecalho, sizeof(cabecalho), processos) == NULL) {
        perror("Erro ao ler o cabeçalho");
        fclose(processos);
    }
    fprintf(csv_decrescente,"%s\n", cabecalho);  
    fclose(processos);

        for (int i = 0; i < n; i++) {
            fprintf(csv_decrescente,"Registro %d:\n", i + 1);
            fprintf(csv_decrescente,"ID: %lld\n", arr[i].id);
            fprintf(csv_decrescente,"Numero: %s\n", arr[i].numero);
            fprintf(csv_decrescente,"Data: %d-%d-%d %d:%d:%d\n", arr[i].ano,arr[i].mes,arr[i].dia,arr[i].hora,arr[i].minuto,arr[i].segundo);
    
            fprintf(csv_decrescente,"Classe:");
            for (size_t j = 0; j < 4; j++)
            {
                if (arr[i].classe[j]==0){
                    continue;
                }
                else{
                    fprintf(csv_decrescente,"%d ", arr[i].classe[j]);
                }
            }
    
            fprintf(csv_decrescente,"\n");
    
            fprintf(csv_decrescente,"Assunto:");
            for (size_t j = 0; j < 4; j++)
            {
                if (arr[i].assunto[j]==0){
                    continue;
                }
                else{
                    fprintf(csv_decrescente,"%d ", arr[i].assunto[j]);
                }
                
            }
            
            fprintf(csv_decrescente,"\n");
    
            if (arr[i].ano_eleicao==0)
            {
                fprintf(csv_decrescente,"Ano Eleicao: 0\n");
            }
            else{
                fprintf(csv_decrescente,"Ano eleicao: %d\n",arr[i].ano_eleicao);
            }
            
    
            int meses = (arr[i].mes - 1) * 30;
            int dias = arr[i].dia;
            int dias_passados = meses + dias;
            int dias_ano = 365 - dias_passados;
            int dias_restantes = (2025-(arr[i].ano+1)) * 365 + dias_ano;
            int dias_tramitado = (2025 - arr[i].ano_eleicao) * 365;
    
            if (arr[i].ano_eleicao==0)
            {
                fprintf(csv_decrescente,"Dias tramitado: 0\n");
            }
            
            else{
                fprintf(csv_decrescente,"Dias tramatido: %d\n",dias_tramitado);
            }
            fprintf(csv_decrescente,"\n");
            fprintf(csv_decrescente,"\n");
        }

    fclose(csv_decrescente);
}

void remover_aspas(char *str) {
    int len = strlen(str);
    if (len > 0 && str[0] == '"' && str[len-1] == '"') {
        memmove(str, str + 1, len - 1); // Remove o primeiro caractere
        str[len - 2] = '\0'; // Remove o Ãºltimo caractere
    }
}

void limpar_formatacao(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != '{' && str[i] != '}' && str[i] != '"') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

void printarray(ids2 *arr, int n) {

    for (int i = 0; i < n; i++) {
        printf("Registro %d:\n", i + 1);
        printf("ID: %lld\n", arr[i].id);
        printf("Numero: %s\n", arr[i].numero);
        printf("Data: %d-%d-%d %d:%d:%d\n", arr[i].ano,arr[i].mes,arr[i].dia,arr[i].hora,arr[i].minuto,arr[i].segundo);

        printf("Classe:");
        for (size_t j = 0; j < 4; j++)
        {
            if (arr[i].classe[j]==0)
            {
                continue;
            }else{
                printf("%d ", arr[i].classe[j]);
            }
        }

        printf("\n");

        printf("Assunto:");
        for (size_t j = 0; j < 4; j++)
        {
            if (arr[i].assunto[j]==0)
            {
                continue;
            }else{
                printf("%d ", arr[i].assunto[j]);
            }
            
            
        }
        
        printf("\n");

        if (arr[i].ano_eleicao==0)
        {
            printf("Ano Eleicao: 0\n");
        }
        else{
            printf("Ano eleicao: %d\n",arr[i].ano_eleicao);
        }
        

        int meses = (arr[i].mes - 1) * 30;
        int dias = arr[i].dia;
        int dias_passados = meses + dias;
        int dias_ano = 365 - dias_passados;
        int dias_restantes = (2025-(arr[i].ano+1)) * 365 + dias_ano;
        int dias_tramitado = (2025 - arr[i].ano_eleicao) * 365;

        if (arr[i].ano_eleicao==0)
        {
            printf("Dias tramitado: 0\n");
        }
        
        else{
            printf("Dias tramatido: %d\n",dias_tramitado);
        }
        printf("\n");
        printf("\n");
    }
}

void dois_assuntos(ids2 *process, int i){
    printf("Processo com dois assuntos:\n");
    for (size_t j = 0; j < i; j++)
    {
        if (process[j].assunto[0] != 0 && process[j].assunto[1] != 0) {
            printf("%lld\n", process[j].id);
        } 
        
    }
    printf("\n");
}

void tipos_assuntos(ids2 *process, int i) {
    int capacidade=100, processos_cont = 0;

    assuntos_tipos *processos = (assuntos_tipos *)malloc(capacidade * sizeof(assuntos_tipos));
    if (processos == NULL) {
        perror("Erro ao alocar memória para assuntos_tipos");
        return;
    }

    for (size_t j = 0; j < i; j++) {
        if (i >= capacidade) {
            capacidade *= 2;
            assuntos_tipos *temp = (assuntos_tipos *)realloc(processos, capacidade * sizeof(assuntos_tipos));
            processos = temp;
        }
        if (process[j].assunto[0] != 0) {
            int ja_existe = 0;
            for (size_t z = 0; z < processos_cont; z++) {
                if (process[j].assunto[0] == processos[z].assuntos) {
                    ja_existe = 1;
                    break;
                }
            }
            if (!ja_existe) {
                processos[processos_cont].assuntos = process[j].assunto[0];
                processos_cont++;
            }
        }
        if (process[j].assunto[1] != 0) {
            int ja_existe = 0;
            for (size_t z = 0; z < processos_cont; z++) {
                if (process[j].assunto[1] == processos[z].assuntos) {
                    ja_existe = 1;
                    break;
                }
            }
            if (!ja_existe) {
                processos[processos_cont].assuntos = process[j].assunto[1];
                processos_cont++;
            }
        }

    }

    printf("Assuntos distintos: %d\n", processos_cont);
    for (size_t x = 0; x < processos_cont; x++) {
        printf("%d\n", processos[x].assuntos);
    }

    free(processos);
}

void listar_processos_classes(ids2 *process, int i){
    int capacidade=100, processos_cont = 0;
    

    processos_classes *processos = (processos_classes *)malloc(capacidade * sizeof(processos_classes));
    if (processos == NULL) {
        perror("Erro ao alocar memória para processos_classes");
        return;
    }

    for (size_t j = 0; j < i; j++) {
        if (i >= capacidade) {
            capacidade *= 2;
            processos_classes *temp = (processos_classes *)realloc(processos, capacidade * sizeof(processos_classes));
            processos = temp;
        }
        if (process[j].classe[0] != 0) {
            int ja_existe = 0;
            for (size_t z = 0; z < processos_cont; z++) {
                if (process[j].classe[0] == processos[z].classes) {
                    ja_existe = 1;
                    break;
                }
            }
            if (!ja_existe) {
                processos[processos_cont].classes = process[j].classe[0];
                processos_cont++;
            }
        }
        if (process[j].classe[1] != 0) {
            int ja_existe = 0;
            for (size_t z = 0; z < processos_cont; z++) {
                if (process[j].classe[1] == processos[z].classes) {
                    ja_existe = 1;
                    break;
                }
            }
            if (!ja_existe) {
                processos[processos_cont].classes = process[j].classe[1];
                processos_cont++;
            }
        }

    }

    printf("Numero de processos associados as classes:\n");
    for (size_t x = 0; x < processos_cont; x++)
    {
        int cont_associar = 0;
        for (size_t j = 0; j < i; j++)
        {
            if (process[j].classe[0]==processos[x].classes)
            {
                cont_associar++;
            }

            else if (process[j].classe[1]==processos[x].classes)
            {
                cont_associar++;
            }
            
        }

        printf("Classe %d, processos associados: %d\n", processos[x].classes, cont_associar);
        
    }
    

}
