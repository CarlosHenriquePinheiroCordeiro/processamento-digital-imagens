#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *oImg;
FILE *oNovaImagem;

void main() {
    oImg        = fopen("Entrada_EscalaCinza.pgm", "r");
    oNovaImagem = fopen("imagemBinariaConvertida.pgm", "w");
    fprintf(oNovaImagem, "P2\n800 800\n255\n");
    char  sCor[10]  = "";
    for (short i = 0; i < 3; i++) { //Ignorando valores de cabeçalho, resolução e tonalidade
        fgets(sCor, 10, oImg);
    }
    while (fgets(sCor, 10, oImg))
    {
        fprintf(oNovaImagem, "%d\n", convertePixel(atoi(sCor)));
    }
    fclose(oNovaImagem);
    fclose(oImg);
}

int convertePixel(int iPixel) {
    int iPixelNovo = 0;
    if (iPixel > 128) {
        iPixelNovo = 255;
    }
    return iPixelNovo;
}