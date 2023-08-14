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
        printf("\n%s", sCor);
    }
    while (fgets(sCor, 200, oImg)) //Montagem da matriz de pixels
    {
        char *sSplit = strtok(sCor, " ");
        while (sSplit != NULL)
        {
            if (iY % iYimagem == 0)
            {
                iY = 0;
                iX++;
            }
            aPixels[iX][iY][0] = atoi(sSplit);
            sSplit = strtok(NULL, " ");
            aPixels[iX][iY][1] = atoi(sSplit);
            sSplit = strtok(NULL, " ");
            aPixels[iX][iY][2] = atoi(sSplit);
            sSplit = strtok(NULL, " ");
            iY++;
        }
    }
    printf("\nRedimensionando pixels...");

    /**
     * (0) 10x Menor
     * (1) Padrão 480x320
     * (2) Padrão 720p (HD)
     * (3) Padrão 1080p Full HD 
     * (4) Padrão 4k
     * (5) Padrão 8k
     
    int aTamanhosPixels[6] = {64009, 153600, 921600, 2073600, 8294400, 33177600};
    int iTamanhoRedimensionar = aTamanhosPixels[iTamanhoSelecionado];
    int iContador             = iXimagem * iYimagem;
    iX                   = 3; //A partir daqui é que começam a ser escritos os pixeis na imagem
    while (iContador != iTamanhoRedimensionar)
    {
        if (aPixels[iX][0] == 0)
        {
            iX = 3;
        }
        
        iX++;
        if (iContador > iTamanhoRedimensionar)
        {
            iContador--;
            //aPixels[iX][1]--;
        }
        else
        {
            //aPixels[iX][1]++;
            iContador++;
        }
    }
    printf("\nMontando nova imagem...");
    oNovaImagem = fopen("imagemRedirecionada.pgm", "a");
    fprintf(oNovaImagem, "P2\n");*/

    /**
     * (0) 10x Menor
     * (1) Padrão 480x320
     * (2) Padrão 720p (HD)
     * (3) Padrão 1080p Full HD 
     * (4) Padrão 4k
     * (5) Padrão 8k
     
    char aTamanhosResolucao[10][10] = {"253 253","320 480","720 1280","1080 1920","2160 3840","4320 7680"};
    fprintf(oNovaImagem, aTamanhosResolucao[iTamanhoSelecionado]);
    fprintf(oNovaImagem, "\n255\n");
    iContador = 0;
    for (int x = 3; x < (iXimagem * iYimagem); x++)
    {
        if (iContador == iTamanhoRedimensionar)
        {
            break;
        }
        for (int i = 0; i < aPixels[x][1]; i++)
        {
            iContador++;
            fprintf(oNovaImagem, "%d\n", aPixels[x][0]);
            if (iContador == iTamanhoRedimensionar)
            {
                break;
            }
        }
    }
    fclose(oNovaImagem);*/
    fclose(oImg);
}