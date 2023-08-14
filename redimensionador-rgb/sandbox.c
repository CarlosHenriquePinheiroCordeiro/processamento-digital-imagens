#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *oImg;
FILE *oNovaImagem;

void main() {
    oImg = fopen("Entrada_RGB.ppm", "r");
    char sCor[200];
    for (short i = 0; i < 3; i++)
    {
        fgets(sCor, 200, oImg);
        printf("\n%s", sCor);
    }
    while (fgets(sCor, 200, oImg))
    {
        printf("\n%s", sCor);
    }
    /*short iTamanhoSelecionado = 0;
    short iXimagem = 800;
    short iYimagem = 800;
    int   aPixels[800][800][3];
    oImg = fopen("Entrada_RGB.ppm", "r");
    int iX = 0;
    int iY = 0;
    char  sCor[200] = "";
    int   iCorAtual = -1;
    printf("\nMontando matriz de pixels...");
    while (fgets(sCor, 200, oImg))
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
    }*/
    fclose(oImg);
}