#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "caminho.h"

int erros = 0;

void AssertInt(const char *teste, int esperado, int obtido)
{
    if (esperado == obtido)
        printf("[OK] %s\n", teste);
    else
    {
        printf("[ERRO] %s | esperado=%d obtido=%d\n",
               teste, esperado, obtido);
        erros++;
    }
}

void AssertDouble(const char *teste, double esperado, double obtido)
{
    double diff = fabs(esperado - obtido);

    if (diff < 0.01)
        printf("[OK] %s\n", teste);
    else
    {
        printf("[ERRO] %s | esperado=%.2f obtido=%.2f\n",
               teste, esperado, obtido);
        erros++;
    }
}

void AssertPtr(const char *teste, void *ptr)
{
    if (ptr != NULL)
        printf("[OK] %s\n", teste);
    else
    {
        printf("[ERRO] %s | ponteiro NULL\n", teste);
        erros++;
    }
}

void AssertNull(const char *teste, void *ptr)
{
    if (ptr == NULL)
        printf("[OK] %s\n", teste);
    else
    {
        printf("[ERRO] %s | esperado NULL\n", teste);
        erros++;
    }
}

int main()
{
    Caminho *C;
    Posicao *P;

    printf("======== TESTE 1 ========\n");

    C = InicializarCaminho("LLLLLLLNNNNN", 2, 2);

    AssertPtr("InicializarCaminho", C);

    if (C != NULL)
    {
        P = DeterminarFim(C);

        AssertPtr("DeterminarFim", P);

        if (P != NULL)
        {
            AssertInt("Fim X", 9, P->X);
            AssertInt("Fim Y", 7, P->Y);
        }

        AssertInt("Distancia Total",
                  12,
                  CalcularDistanciaTotal(C));

        AssertDouble("Distancia Geometrica",
                     8.60,
                     CalcularDistanciaGeometrica(C));

        AssertInt("Distancia Manhattan",
                  12,
                  CalcularDistanciaManhattan(C));

        AssertInt("ContarInstrucoes",
                  12,
                  ContarInstrucoes(C));

        DestruirCaminho(C);
    }

    printf("\n======== TESTE 2 ========\n");

    C = InicializarCaminho("NNXLL", 0, 0);

    AssertNull("Comando invalido", C);

    printf("\n======== TESTE 3 ========\n");

    C = InicializarCaminho(NULL, 0, 0);

    AssertNull("Sequencia NULL", C);

    printf("\n======== TESTE 4 ========\n");

    AssertNull("DeterminarFim(NULL)",
               DeterminarFim(NULL));

    AssertNull("HistoricoPosicoes(NULL)",
               HistoricoPosicoes(NULL));

    AssertInt("CalcularDistanciaTotal(NULL)",
              -1,
              CalcularDistanciaTotal(NULL));

    AssertDouble("CalcularDistanciaGeometrica(NULL)",
                 -1.0,
                 CalcularDistanciaGeometrica(NULL));

    AssertInt("CalcularDistanciaManhattan(NULL)",
              -1,
              CalcularDistanciaManhattan(NULL));

    AssertInt("ContarInstrucoes(NULL)",
              -1,
              ContarInstrucoes(NULL));

    printf("\n======== TESTE 5 ========\n");

    C = InicializarCaminho("", 5, 5);

    AssertPtr("Sequencia vazia", C);

    if (C != NULL)
    {
        P = DeterminarFim(C);

        if (P == NULL)
            printf("[INFO] Fim ficou NULL na sequencia vazia\n");

        printf("Distancia total: %d\n",
               CalcularDistanciaTotal(C));

        printf("Distancia geometrica: %.2f\n",
               CalcularDistanciaGeometrica(C));

        printf("Distancia Manhattan: %d\n",
               CalcularDistanciaManhattan(C));

        printf("Instrucoes: %d\n",
               ContarInstrucoes(C));

        DestruirCaminho(C);
    }

    printf("\n=========================\n");

    if (erros == 0)
        printf("TODOS OS TESTES PASSARAM\n");
    else
        printf("TOTAL DE ERROS: %d\n", erros);

    return erros;
}