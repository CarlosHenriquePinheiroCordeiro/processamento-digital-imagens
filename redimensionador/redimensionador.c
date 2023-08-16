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
    short iTamanhoSelecionado = 5;
    short iXimagem = 800;
    short iYimagem = 800;
    int   aPixels[iXimagem*iYimagem][2];
    oImg = fopen("Entrada_EscalaCinza.pgm", "r");
    int   iIndice   = -1;
    char  sCor[10]  = "";
    int   iCorAtual = -1;
    printf("\nContando pixels...");
    int iTeste = 1;
    while (fgets(sCor, 10, oImg))
    {
        if (atoi(sCor) != iCorAtual)
        {
            iCorAtual = atoi(sCor);
            iIndice++;
            aPixels[iIndice][0] = atoi(sCor);
        }
        aPixels[iIndice][1]++;
        iTeste++;
    }
    printf("\nRedimensionando pixels...");

    /**
     * (0) 10x Menor
     * (1) Padrão 480x320
     * (2) Padrão 720p (HD)
     * (3) Padrão 1080p Full HD 
     * (4) Padrão 4k
     * (5) Padrão 8k
     */
    int aTamanhosPixels[6] = {64009, 153600, 921600, 2073600, 8294400, 33177600};
    int iTamanhoRedimensionar = aTamanhosPixels[iTamanhoSelecionado];
    int iContador             = iXimagem * iYimagem;
    iIndice                   = 3; //A partir daqui é que começam a ser escritos os pixeis na imagem
    while (iContador != iTamanhoRedimensionar)
    {
        if (aPixels[iIndice][0] == 0)
        {
            iIndice = 3;
        }
        
        iIndice++;
        if (iContador > iTamanhoRedimensionar)
        {
            iContador--;
            aPixels[iIndice][1]--;
        }
        else
        {
            aPixels[iIndice][1]++;
            iContador++;
        }
    }
    printf("\nMontando nova imagem...");
    oNovaImagem = fopen("imagemRedirecionada.pgm", "a");
    fprintf(oNovaImagem, "P2\n");

    /**
     * (0) 10x Menor
     * (1) Padrão 480x320
     * (2) Padrão 720p (HD)
     * (3) Padrão 1080p Full HD 
     * (4) Padrão 4k
     * (5) Padrão 8k
     */
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
    fclose(oNovaImagem);
    fclose(oImg);
}