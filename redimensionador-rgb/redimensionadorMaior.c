#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *oImg;
FILE *oNovaImagem;

void main() {
    /**
     * (0) Padrão 720p (HD)
     * (1) Padrão 1080p Full HD 
     * (2) Padrão 4k
     * (3) Padrão 8k
     */
    short iTamanhoSelecionado = 1;
    short iXImagem = 800;
    short iYImagem = 800;
    short aPixels[iXImagem][iYImagem][3];
    oImg = fopen("Entrada_RGB.ppm", "r");
    short iX = 0;
    short iY = 0;
    char  sCor[200] = "";
    printf("\nMontando matriz de pixels...");
    for (short i = 0; i < 3; i++) //Ignorando valores de cabeçalho, resolução e tonalidade
    {
        fgets(sCor, 200, oImg);
    }
    while (fgets(sCor, 200, oImg))
    {
        char *sSplit = strtok(sCor, " ");
        while (sSplit != NULL)
        {
            if (strcmp(sSplit, "\n") != 0) 
            {
                if (iY > 0 && iY % iYImagem == 0)
                {
                    iY = 0;
                    iX++;
                }
                aPixels[iX][iY][0] = atoi(sSplit);
                sSplit = strtok(NULL, " ");
                aPixels[iX][iY][1] = atoi(sSplit);
                sSplit = strtok(NULL, " ");
                aPixels[iX][iY][2] = atoi(sSplit);
                iY++;
            }
            sSplit = strtok(NULL, " ");
        }
    }


    /**
     * IDEIAS:
     * -PARA REDIMENSIONAR/AUMENTAR AS COLUNAS, SOMENTE DUPLICAR OS PIXEIS DAS COLUNAS PARA PREENCHER A LINHA TODA DO NOVO TAMANHO
     * -PARA REDIMENSIONAR/AUMENTAR AS LINHAS, VERIFICAR QUAIS LINHAS DEVEM SER DUPLICADAS PARA BAIXO
     * 
     * -PRIMEIRO AUMENTAR AS LINHAS, DEPOIS AUMENTAR AS COLUNAS
     * -NO ÚLTIMO PASSO, QUE É DO AUMENTO DAS COLUNAS, CONSTRUIR DIRETO NO ARQUIVO DA IMAGEM LINHA POR LINHA, JÁ COM AS LINHAS AUMENTADAS, ADICIONANDO OS NOVOS PIXEIS DAS COLUNAS CONFORME O NOVO TAMANHO.
    */


    /**
     * (0) Padrão 720p (HD)
     * (1) Padrão 1080p Full HD 
     * (2) Padrão 4k
     * (3) Padrão 8k
     */
    short aTamanhosX[4] = {1280, 1920, 3840, 7680};
    short aTamanhosY[4] = {720, 1080, 2160, 4320};
    short iTamanhoX = aTamanhosX[iTamanhoSelecionado];
    short iTamanhoY = aTamanhosY[iTamanhoSelecionado];

    
    // printf("\nMontando nova imagem...");
    // oNovaImagem = fopen("redimenRgbMaior.ppm", "w");
    // fprintf(oNovaImagem, "P3\n");
    // /**
    //  * (0) Padrão 720p (HD)
    //  * (1) Padrão 1080p Full HD 
    //  * (2) Padrão 4k
    //  * (3) Padrão 8k
    //  */
    // char aTamanhosResolucao[10][10] = {"1280 720","1920 1080","3840 2160","7680 4320"};
    // fprintf(oNovaImagem, aTamanhosResolucao[iTamanhoSelecionado]);
    // fprintf(oNovaImagem, "\n255\n");
    // int iContador = 0;
    // iX = 0;
    // iY = 0;
    // while (iContador < iTamanhoX*iTamanhoY)
    // {
    //     for (iY = 0; iY < iTamanhoY; iY++)
    //     {
    //         iContador++;
    //         fprintf(oNovaImagem, "%d\n%d\n%d\n", aPixels[iX][iY][0], aPixels[iX][iY][1], aPixels[iX][iY][2]);
    //     }
    //     iX++;
    // }
    // fclose(oNovaImagem);
    fclose(oImg);
}