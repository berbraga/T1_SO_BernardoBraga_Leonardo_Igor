#include "funcoes.h" // Incluindo o arquivo de cabeçalho com as declarações das funções

int main()
{
    char matriz[MAX][MAX], palavras[MAX][MAX];
    int linhas, colunas, qtd_palavras;
    PosicaoDirecao posicoes[MAX]; // Array para armazenar a posição e direção das palavras encontradas

    // Nome do arquivo de entrada
    char nomeArquivoEntrada[] = "./palavras.txt";
    // Nome do arquivo de saída
    char nomeArquivoSaida[] = "./saida.txt";

    // Lendo os dados do arquivo de entrada
    lerDados(nomeArquivoEntrada, matriz, &linhas, &colunas, palavras, &qtd_palavras);

    // Buscando as palavras no diagrama
    buscarPalavras(matriz, linhas, colunas, palavras, qtd_palavras, posicoes);

    // Escrevendo o resultado no arquivo de saída
    escreverSaida(nomeArquivoSaida, matriz, linhas, colunas, palavras, posicoes, qtd_palavras);

    return 0; // Finalizando o programa com sucesso
}
