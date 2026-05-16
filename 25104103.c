#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "caminho.h"

Caminho *InicializarCaminho(const char *Sequencia, int xInicial, int yInicial)
{
    Caminho *c = (Caminho *)malloc(sizeof(Caminho));
    if (c == NULL)
        return NULL;

    Posicao *novP = (Posicao *)malloc(sizeof(Posicao));
    if (novP == NULL)
    {
        free(c);
        return NULL;
    }

    novP->X = xInicial;
    novP->Y = yInicial;
    novP->Proximo = NULL;

    Posicao *novoH = (Posicao *)malloc(sizeof(Posicao));
    if (novoH == NULL)
    {
        free(novP);
        free(c);
        return NULL;
    }

    c->Inicio = novP;
    c->Historico = novoH;
    c->Historico->X = xInicial;
    c->Historico->Y = yInicial;
    c->Historico->Proximo = NULL;
    c->Fim = NULL;
    c->Instrucoes = NULL;
    c->N = 0;

    if (Sequencia == NULL)
    {
        DestruirCaminho(c);
        return NULL;
    }

    for (int i = 0; Sequencia[i] != '\0'; i++)
    {
        char ch = Sequencia[i];
        if (ch == 'N' || ch == 'S' || ch == 'L' || ch == 'O')
            continue;
        DestruirCaminho(c);
        return NULL;
    }

    int x = xInicial;
    int y = yInicial;

    Posicao *atual = novoH;
    Comando *atualCmd = NULL;

    for (int i = 0; Sequencia[i] != '\0'; i++)
    {
        char op = Sequencia[i];
        switch (op)
        {
        case 'N':
            y++;
            break;
        case 'S':
            y--;
            break;
        case 'L':
            x++;
            break;
        case 'O':
            x--;
            break;
        default:
            DestruirCaminho(c);
            return NULL;
        }

        Posicao *novoNo = (Posicao *)malloc(sizeof(Posicao));
        if (novoNo == NULL)
        {
            DestruirCaminho(c);
            return NULL;
        }

        novoNo->X = x;
        novoNo->Y = y;
        novoNo->Proximo = NULL;
        atual->Proximo = novoNo;
        atual = novoNo;

        Comando *novoCmd = (Comando *)malloc(sizeof(Comando));
        if (novoCmd == NULL)
        {
            DestruirCaminho(c);
            return NULL;
        }

        novoCmd->Direcao = op;
        novoCmd->Proximo = NULL;

        if (c->Instrucoes == NULL)
        {
            c->Instrucoes = novoCmd;
            atualCmd = novoCmd;
        }
        else
        {
            atualCmd->Proximo = novoCmd;
            atualCmd = novoCmd;
        }
        c->N++;
        c->Fim = atual;
    }
    return c;
}
void DestruirCaminho(Caminho *C)
{

    if (C == NULL)
        return;

    Posicao *p = C->Historico;
    while (p != NULL)
    {
        Posicao *prox = p->Proximo;
        free(p);
        p = prox;
    }

    Comando *cmd = C->Instrucoes;
    while (cmd != NULL)
    {
        Comando *prox = cmd->Proximo;
        free(cmd);
        cmd = prox;
    }

    free(C->Inicio);
    free(C);
}

Posicao *DeterminarFim(Caminho *C)
{
    if (C == NULL)
    {
        return NULL;
    }
    return C->Fim;
}
Posicao *HistoricoPosicoes(Caminho *C)
{
    if (C == NULL)
    {
        return NULL;
    }

    return C->Historico;
}
int CalcularDistanciaTotal(Caminho *C)
{
    if (C == NULL)
    {
        return -1;
    }

    return C->N;
}
double CalcularDistanciaGeometrica(Caminho *C)
{
    if (C == NULL || C->Fim == NULL)
    {
        return -1.0;
    }

    double distGeo = sqrt(pow((C->Inicio->X - C->Fim->X), 2) + pow((C->Inicio->Y - C->Fim->Y), 2));

    return distGeo;
}
int CalcularDistanciaManhattan(Caminho *C)
{
    if (C == NULL || C->Fim == NULL)
    {
        return -1;
    }

    int manhattan = abs(C->Inicio->X - C->Fim->X) + abs(C->Inicio->Y - C->Fim->Y);

    return manhattan;
}
int ContarInstrucoes(Caminho *C)
{
    if (C == NULL)
    {
        return -1;
    }

    return C->N;
}