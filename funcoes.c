#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Direções para buscar: horizontal, vertical e diagonais
const int DX[] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int DY[] = {-1, 0, 1, 1, 1, 0, -1, -1};
const char *DIRECAO_NOME[] = {"superior esquerda", "superior", "superior direita", "direita", "inferior direita", "inferior", "inferior esquerda", "esquerda"};

void lerDados(char *nomeArquivo, char matriz[][MAX], int *linhas, int *colunas, char palavras[][MAX], int *qtd_palavras)
{
    FILE *file = fopen(nomeArquivo, "r");
    if (!file)
    {
        printf("Não foi possível abrir o arquivo de entrada.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d\n", linhas, colunas); // Lê as dimensões do diagrama
    for (int i = 0; i < *linhas; i++)
    {
        fscanf(file, "%s\n", matriz[i]); // Lê cada linha do diagrama
    }

    *qtd_palavras = 0;
    while (fscanf(file, "%s\n", palavras[*qtd_palavras]) != EOF)
    { // Lê cada palavra até o fim do arquivo
        (*qtd_palavras)++;
    }

    fclose(file);
}

bool buscarPalavra(char matriz[][MAX], int x, int y, const char *palavra, int dx, int dy, int linhas, int colunas)
{
    int len = strlen(palavra);

    for (int i = 0; i < len; i++)
    {
        int nx = x + i * dx;
        int ny = y + i * dy;

        if (nx < 0 || nx >= linhas || ny < 0 || ny >= colunas || toupper(matriz[nx][ny]) != toupper(palavra[i]))
        {
            return false;
        }
    }

    // Se encontrou, converte as letras da palavra em maiúsculas
    for (int i = 0; i < len; i++)
    {
        int nx = x + i * dx;
        int ny = y + i * dy;
        matriz[nx][ny] = toupper(matriz[nx][ny]);
    }

    return true;
}

void buscarPalavras(char matriz[][MAX], int linhas, int colunas, char palavras[][MAX], int qtd_palavras, PosicaoDirecao posicoes[])
{
    // Inicializando todas as posições como não encontradas
    for (int i = 0; i < qtd_palavras; i++)
    {
        posicoes[i].x = -1;
    }

    for (int p = 0; p < qtd_palavras; p++)
    {
        for (int x = 0; x < linhas; x++)
        {
            for (int y = 0; y < colunas; y++)
            {
                for (int d = 0; d < 8; d++)
                {
                    if (buscarPalavra(matriz, x, y, palavras[p], DX[d], DY[d], linhas, colunas))
                    {
                        posicoes[p].x = x;
                        posicoes[p].y = y;
                        strcpy(posicoes[p].direcao, DIRECAO_NOME[d]);
                        break;
                    }
                }
                if (posicoes[p].x != -1)
                    break; // Se já encontrou a palavra, não precisa continuar procurando
            }
            if (posicoes[p].x != -1)
                break; // Se já encontrou a palavra, não precisa continuar procurando
        }
        if (posicoes[p].x == -1)
        {
            printf("Palavra '%s' não encontrada.\n", palavras[p]);
        }
    }
}

void escreverSaida(char *nomeArquivo, char matriz[][MAX], int linhas, int colunas, char palavras[][MAX], PosicaoDirecao posicoes[], int qtd_palavras)
{
    FILE *file = fopen(nomeArquivo, "w");
    if (!file)
    {
        printf("Não foi possível abrir o arquivo de saída.\n");
        exit(EXIT_FAILURE);
    }

    // Escrevendo o diagrama atualizado no arquivo
    for (int i = 0; i < linhas; i++)
    {
        fprintf(file, "%s\n", matriz[i]);
    }

    fprintf(file, "\n"); // Espaço entre o diagrama e a lista de palavras

    // Escrevendo as palavras encontradas e suas posições
    for (int i = 0; i < qtd_palavras; i++)
    {
        if (posicoes[i].x >= 0)
        { // Verifica se a palavra foi encontrada
            fprintf(file, "%s – (%d,%d):%s\n", palavras[i], posicoes[i].x, posicoes[i].y, posicoes[i].direcao);
        }
        else
        {
            fprintf(file, "%s – não encontrada\n", palavras[i]);
        }
    }

    fclose(file);
}
