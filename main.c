#include <stdio.h>
#include <stdlib.h>
#include "caminho.h"

int pontos = 0;
int total = 0;

void teste(const char *descricao, int passou)
{
    total++;
    if (passou)
    {
        pontos++;
        printf("[OK] %s\n", descricao);
    }
    else
        printf("[FALHOU] %s\n", descricao);
}

int main()
{
    printf("=== TESTES AUTOMATICOS ===\n\n");

    // -------------------------
    // InicializarCaminho
    // -------------------------
    printf("--- InicializarCaminho ---\n");

    Caminho *c1 = InicializarCaminho("LLLLLLLNNNNN", 2, 2);
    teste("Sequencia valida retorna nao NULL", c1 != NULL);

    if (c1 != NULL)
    {
        teste("Inicio X correto", c1->Inicio->X == 2);
        teste("Inicio Y correto", c1->Inicio->Y == 2);
        teste("N correto (12)", c1->N == 12);
        teste("Fim X correto (9)", c1->Fim->X == 9);
        teste("Fim Y correto (7)", c1->Fim->Y == 7);
        teste("Historico nao NULL", c1->Historico != NULL);
        teste("Historico inicio X correto", c1->Historico->X == 2);
        teste("Historico inicio Y correto", c1->Historico->Y == 2);
        teste("Instrucoes nao NULL", c1->Instrucoes != NULL);
        teste("Primeira instrucao L", c1->Instrucoes->Direcao == 'L');
        DestruirCaminho(c1);
    }

    Caminho *c2 = InicializarCaminho("NNNXLLL", 0, 0);
    teste("Comando invalido retorna NULL", c2 == NULL);

    Caminho *c3 = InicializarCaminho(NULL, 0, 0);
    teste("Sequencia NULL retorna NULL", c3 == NULL);

    Caminho *c4 = InicializarCaminho("", 5, 5);
    teste("Sequencia vazia retorna nao NULL", c4 != NULL);
    if (c4 != NULL)
    {
        teste("Sequencia vazia N = 0", c4->N == 0);
        teste("Sequencia vazia Fim = NULL", c4->Fim == NULL);
        teste("Sequencia vazia Inicio X correto", c4->Inicio->X == 5);
        DestruirCaminho(c4);
    }

    Caminho *c5 = InicializarCaminho("NSLO", 0, 0);
    teste("Sequencia NSLO retorna nao NULL", c5 != NULL);
    if (c5 != NULL)
    {
        teste("NSLO posicao final X = 0", c5->Fim->X == 0);
        teste("NSLO posicao final Y = 0", c5->Fim->Y == 0);
        DestruirCaminho(c5);
    }

    // -------------------------
    // DeterminarFim
    // -------------------------
    printf("\n--- DeterminarFim ---\n");

    Caminho *cf = InicializarCaminho("LLLLLLLNNNNN", 2, 2);
    if (cf != NULL)
    {
        Posicao *fim = DeterminarFim(cf);
        teste("DeterminarFim nao NULL", fim != NULL);
        teste("DeterminarFim X = 9", fim != NULL && fim->X == 9);
        teste("DeterminarFim Y = 7", fim != NULL && fim->Y == 7);
        DestruirCaminho(cf);
    }
    teste("DeterminarFim com NULL retorna NULL", DeterminarFim(NULL) == NULL);

    // -------------------------
    // HistoricoPosicoes
    // -------------------------
    printf("\n--- HistoricoPosicoes ---\n");

    Caminho *ch = InicializarCaminho("LN", 0, 0);
    if (ch != NULL)
    {
        Posicao *h = HistoricoPosicoes(ch);
        teste("Historico nao NULL", h != NULL);
        teste("Historico primeiro ponto X = 0", h != NULL && h->X == 0);
        teste("Historico primeiro ponto Y = 0", h != NULL && h->Y == 0);
        if (h && h->Proximo)
            teste("Historico segundo ponto X = 1", h->Proximo->X == 1);
        if (h && h->Proximo && h->Proximo->Proximo)
            teste("Historico terceiro ponto Y = 1", h->Proximo->Proximo->Y == 1);
        DestruirCaminho(ch);
    }
    teste("HistoricoPosicoes com NULL retorna NULL", HistoricoPosicoes(NULL) == NULL);

    // -------------------------
    // CalcularDistanciaTotal
    // -------------------------
    printf("\n--- CalcularDistanciaTotal ---\n");

    Caminho *ct = InicializarCaminho("LLLLLLLNNNNN", 2, 2);
    if (ct != NULL)
    {
        teste("DistanciaTotal = 12", CalcularDistanciaTotal(ct) == 12);
        DestruirCaminho(ct);
    }
    Caminho *ct2 = InicializarCaminho("", 0, 0);
    if (ct2 != NULL)
    {
        teste("DistanciaTotal vazia = 0", CalcularDistanciaTotal(ct2) == 0);
        DestruirCaminho(ct2);
    }
    teste("DistanciaTotal com NULL retorna -1", CalcularDistanciaTotal(NULL) == -1);

    // -------------------------
    // CalcularDistanciaGeometrica
    // -------------------------
    printf("\n--- CalcularDistanciaGeometrica ---\n");

    Caminho *cg = InicializarCaminho("LLLLLLLNNNNN", 2, 2);
    if (cg != NULL)
    {
        double geo = CalcularDistanciaGeometrica(cg);
        teste("DistanciaGeometrica ~8.60", geo > 8.60 && geo < 8.61);
        DestruirCaminho(cg);
    }
    Caminho *cg2 = InicializarCaminho("", 0, 0);
    if (cg2 != NULL)
    {
        teste("DistanciaGeometrica vazia = -1.0", CalcularDistanciaGeometrica(cg2) == -1.0);
        DestruirCaminho(cg2);
    }
    teste("DistanciaGeometrica com NULL retorna -1.0", CalcularDistanciaGeometrica(NULL) == -1.0);

    // -------------------------
    // CalcularDistanciaManhattan
    // -------------------------
    printf("\n--- CalcularDistanciaManhattan ---\n");

    Caminho *cm = InicializarCaminho("LLLLLLLNNNNN", 2, 2);
    if (cm != NULL)
    {
        teste("Manhattan = 12", CalcularDistanciaManhattan(cm) == 12);
        DestruirCaminho(cm);
    }
    Caminho *cm2 = InicializarCaminho("NNNNOOOOLLLSS", 0, 0);
    if (cm2 != NULL)
    {
        teste("Manhattan NNNNOOOOLLLSS = 3", CalcularDistanciaManhattan(cm2) == 3);
        DestruirCaminho(cm2);
    }
    Caminho *cm3 = InicializarCaminho("", 0, 0);
    if (cm3 != NULL)
    {
        teste("Manhattan vazia = -1", CalcularDistanciaManhattan(cm3) == -1);
        DestruirCaminho(cm3);
    }
    teste("Manhattan com NULL retorna -1", CalcularDistanciaManhattan(NULL) == -1);

    // -------------------------
    // ContarInstrucoes
    // -------------------------
    printf("\n--- ContarInstrucoes ---\n");

    Caminho *ci = InicializarCaminho("LLLLLLLNNNNN", 2, 2);
    if (ci != NULL)
    {
        teste("ContarInstrucoes = 12", ContarInstrucoes(ci) == 12);
        DestruirCaminho(ci);
    }
    Caminho *ci2 = InicializarCaminho("", 0, 0);
    if (ci2 != NULL)
    {
        teste("ContarInstrucoes vazia = 0", ContarInstrucoes(ci2) == 0);
        DestruirCaminho(ci2);
    }
    teste("ContarInstrucoes com NULL retorna -1", ContarInstrucoes(NULL) == -1);

    // -------------------------
    // Resultado
    // -------------------------
    printf("\n=== RESULTADO ===\n");
    printf("Testes passados: %d / %d\n", pontos, total);
    printf("Nota estimada: %.2f\n", (double)pontos / total);

    return 0;
}