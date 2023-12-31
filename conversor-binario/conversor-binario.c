#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *oImg;
FILE *oNovaImagem;

void main() {
    realizaConversaoImagemBinario();
    realizaConversaoImagemNegativo();
}

void realizaConversaoImagemBinario() {
    oImg        = fopen("Entrada_EscalaCinza.pgm", "r");
    oNovaImagem = fopen("imagemBinariaConvertida.pbm", "w");
    fprintf(oNovaImagem, "P1\n800 800\n");
    char  sCor[10]  = "";
    for (short i = 0; i < 3; i++) { //Ignorando valores de cabeçalho, resolução e tonalidade
        fgets(sCor, 10, oImg);
    }
    while (fgets(sCor, 10, oImg))
    {
        fprintf(oNovaImagem, "%d\n", converteBinario(atoi(sCor)));
    }
    fclose(oNovaImagem);
    fclose(oImg);
}

int converteBinario(int iPixel) {
    int iPixelNovo = 0;
    if (iPixel > 128) {
        iPixelNovo = 1;
    }
    return iPixelNovo;
}

void realizaConversaoImagemNegativo() {
    oImg        = fopen("imagemBinariaConvertida.pbm", "r");
    oNovaImagem = fopen("imagemNegativa.pgm", "w");
    fprintf(oNovaImagem, "P2\n800 800\n1\n");
    char  sCor[10]  = "";
    for (short i = 0; i < 2; i++) { //Ignorando valores de cabeçalho, resolução e tonalidade
        fgets(sCor, 10, oImg);
    }
    while (fgets(sCor, 10, oImg))
    {
        fprintf(oNovaImagem, "%d\n", atoi(sCor));
    }
    fclose(oNovaImagem);
    fclose(oImg);
}