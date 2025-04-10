#ifndef structs_h
#define structs_h

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long id;
    char numero[50];
    char data_ajuizamento[50];
    int classe[50];
    int classe_quant;
    int assunto[50];
    int assunto_quant;
    int ano_eleicao;
} ids;

typedef struct {
    long long id;
    char numero[50];
    int ano, mes, dia, hora, minuto, segundo;
    int classe[4];
    int assunto[4];
    int ano_eleicao;
} ids2;

typedef struct {
    int assuntos;
} assuntos_tipos;

typedef struct {
    int classes;
} processos_classes;

#endif