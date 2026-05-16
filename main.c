#include <stdio.h>
#include <stdlib.h>
#include "caminho.h"

void ExibirHistorico(Posicao *P)
{
    while (P != NULL)
    {
        printf("(%d, %d)", P->X, P->Y);
        if (P->Proximo != NULL) printf(" -> ");
        P = P->Proximo;
    }
    printf("\n");
}

int main()
{
    Caminho *C;
    Posicao *Fim;
    Posicao *Historico;

    C = InicializarCaminho("",12,20);
    if (C == NULL)
    {
        printf("Erro ao inicializar o caminho.\n");
        return 1;
    }

    Fim = DeterminarFim(C);
    if (Fim != NULL)
        printf("Posicao final: (%d, %d)\n", Fim->X, Fim->Y);

    Historico = HistoricoPosicoes(C);
    printf("Historico de posicoes:\n");
    ExibirHistorico(Historico);

    printf("Distancia total percorrida: %d\n", CalcularDistanciaTotal(C));
    printf("Distancia geometrica: %.2f\n", CalcularDistanciaGeometrica(C));
    printf("Distancia de Manhattan: %d\n", CalcularDistanciaManhattan(C));
    printf("Quantidade de instrucoes: %d\n", ContarInstrucoes(C));

    DestruirCaminho(C);

    // Teste comando invalido
    Caminho *C2 = InicializarCaminho("NNNXLLL", 0, 0);
    if (C2 == NULL)
        printf("Comando invalido detectado corretamente.\n");

    // Teste sequencia NULL
    Caminho *C3 = InicializarCaminho(NULL, 0, 0);
    if (C3 == NULL)
        printf("Sequencia NULL detectada corretamente.\n");

    return 0;
}