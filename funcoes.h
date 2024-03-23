#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdbool.h> // Para usar o tipo bool para verdadeiro/falso

#define MAX 100 // Definindo um limite para o tamanho do diagrama e das palavras

// Estrutura para armazenar as posições e direções das palavras encontradas
typedef struct
{
    int x, y;         // Posição inicial da palavra (linha, coluna)
    char direcao[20]; // Direção da palavra encontrada
} PosicaoDirecao;

// Declaração das funções que serão implementadas em outros arquivos
void lerDados(char *nomeArquivo, char matriz[][MAX], int *linhas, int *colunas, char palavras[][MAX], int *qtd_palavras);
void buscarPalavras(char matriz[][MAX], int linhas, int colunas, char palavras[][MAX], int qtd_palavras, PosicaoDirecao posicoes[]);
void escreverSaida(char *nomeArquivo, char matriz[][MAX], int linhas, int colunas, char palavras[][MAX], PosicaoDirecao posicoes[], int qtd_palavras);

#endif // FUNCOES_H
