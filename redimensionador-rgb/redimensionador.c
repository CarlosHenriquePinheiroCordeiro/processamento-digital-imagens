#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *oImg;
FILE *oNovaImagem;

void main() {
    /**
     * (0) 10x Menor
     * (1) Padrão 480x320
     * (2) Padrão 720p (HD)
     * (3) Padrão 1080p Full HD 
     * (4) Padrão 4k
     * (5) Padrão 8k
     */
    short iTamanhoSelecionado = 0;
    short iXimagem = 800;
    short iYimagem = 800;
    int   aPixels[800][800][3];
    oImg = fopen("Entrada_RGB.ppm", "r");
    int iX = 0;
    int iY = 0;
    char  sCor[200] = "";
    int   iCorAtual = -1;
    printf("\nMontando matriz de pixels...");
    for (short i = 0; i < 3; i++) //Ignorando valores de cabeçalho, resolução e tonalidade
    {
        fgets(sCor, 200, oImg);
    }
    while (fgets(sCor, 200, oImg)) //Montagem da matriz de pixels
    {
        char *sSplit = strtok(sCor, " ");
        while (sSplit != NULL)
        {
            if (strcmp(sSplit, "\n") != 0) 
            {
                if (iY > 0 && iY % iYimagem == 0)
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
     * (0) 10x Menor
     * (1) Padrão 480x320
     * (2) Padrão 720p (HD)
     * (3) Padrão 1080p Full HD 
     * (4) Padrão 4k
     * (5) Padrão 8k
     */
    int aTamanhosX[6] = {80, 480, 1280, 1920, 3840, 7680};
    int aTamanhosY[6] = {80, 320, 720, 1080, 2160, 4320};
    int iXselecionado = aTamanhosX[iTamanhoSelecionado];
    int iYselecionado = aTamanhosY[iTamanhoSelecionado];
    int aPixelsNovos[iXselecionado][iYselecionado][3];

    printf("\nRedimensionando Y...");
    int iTamanhoY = aTamanhosY[iTamanhoSelecionado];
    if (iTamanhoY < iYimagem) //Diminuir imagem
    {
        int iQuantidadeMedia = iYimagem / iTamanhoY;
        int iRed    = 0;
        int iGreen  = 0;
        int iBlue   = 0;
        for (int iY = 0; iY < iYimagem; iY++)
        {
            for (int iX = 0; iX < iXimagem; iX++)
            {
                iRed   += aPixels[iX][iY][0];
                iGreen += aPixels[iX][iY][1];
                iBlue  += aPixels[iX][iY][2];
                if ((iX+1) % iQuantidadeMedia == 0)
                {
                    iRed   = iRed/iQuantidadeMedia;
                    iGreen = iGreen/iQuantidadeMedia;
                    iBlue  = iBlue/iQuantidadeMedia;
                    aPixelsNovos[(((iX+1))/iQuantidadeMedia)-1][iY][0] = iRed;
                    aPixelsNovos[(((iX+1))/iQuantidadeMedia)-1][iY][1] = iGreen;
                    aPixelsNovos[(((iX+1))/iQuantidadeMedia)-1][iY][2] = iBlue;
                    iRed    = 0;
                    iGreen  = 0;
                    iBlue   = 0;
                }
            }
        }
    }
    else //Aumentar imagem
    {

    }

    printf("\nRedimensionando X...");

    int iTamanhoX = aTamanhosX[iTamanhoSelecionado];
    if (iTamanhoX < iXimagem) //Diminuir imagem
    {
        int iQuantidadeMedia = iXimagem / iTamanhoX;
        int iRed    = 0;
        int iGreen  = 0;
        int iBlue   = 0;
        for (int iX = 0; iX < iXimagem; iX++)
        {
            for (int iY = 0; iY < iYimagem; iY++)
            {
                iRed   += aPixels[iX][iY][0];
                iGreen += aPixels[iX][iY][1];
                iBlue  += aPixels[iX][iY][2];
                if ((iY+1) % iQuantidadeMedia == 0)
                {
                    iRed   = iRed/iQuantidadeMedia;
                    iGreen = iGreen/iQuantidadeMedia;
                    iBlue  = iBlue/iQuantidadeMedia;
                    aPixelsNovos[iX][((iY+1)/iQuantidadeMedia)-1][0] = iRed;
                    aPixelsNovos[iX][((iY+1)/iQuantidadeMedia)-1][1] = iGreen;
                    aPixelsNovos[iX][((iY+1)/iQuantidadeMedia)-1][2] = iBlue;
                    iRed    = 0;
                    iGreen  = 0;
                    iBlue   = 0;
                }
            }
        }
    }
    else //Aumentar imagem
    {

    }

    printf("\nMontando nova imagem...");
    oNovaImagem = fopen("imagemRedirecionadaRGB.pgm", "a");
    fprintf(oNovaImagem, "P3\n");
    /**
     * (0) 10x Menor
     * (1) Padrão 480x320
     * (2) Padrão 720p (HD)
     * (3) Padrão 1080p Full HD 
     * (4) Padrão 4k
     * (5) Padrão 8k
     */
    char aTamanhosResolucao[10][10] = {"80 80","480 320","1280 720","1920 1080","3840 2160","7680 4320"};
    fprintf(oNovaImagem, aTamanhosResolucao[iTamanhoSelecionado]);
    fprintf(oNovaImagem, "\n255\n");
    for (int iX = 0; iX < iTamanhoX; iX++)
    {
        for (int iY = 0; iY < iTamanhoY; iY++)
        {
            fprintf(oNovaImagem, "%d\n%d\n%d\n ", aPixelsNovos[iX][iY][0], aPixelsNovos[iX][iY][1], aPixelsNovos[iX][iY][2]);
        }
    }
    fclose(oNovaImagem);
    fclose(oImg);
}