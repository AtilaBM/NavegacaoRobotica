# 🤖 Navegação Robótica

Um programa em C que simula o movimento de um robô em um plano cartesiano.

## O que ele faz?

Você fornece uma sequência de comandos e uma posição inicial. O robô segue os comandos um a um, e o programa registra cada passo do caminho percorrido.

## Comandos

| Comando | Direção  | Efeito          |
|---------|----------|-----------------|
| `N`     | Norte    | y + 1 (sobe)    |
| `S`     | Sul      | y - 1 (desce)   |
| `L`     | Leste    | x + 1 (direita) |
| `O`     | Oeste    | x - 1 (esquerda)|

**Exemplo:** robô começa em (2, 2) com a sequência `LLLLLLLNNNNN` e termina em (9, 7).

## O que o programa calcula?

- **Posição final** — onde o robô parou
- **Histórico** — todas as posições visitadas em ordem
- **Distância total** — quantos passos foram dados
- **Distância geométrica** — distância em linha reta do início ao fim
- **Distância de Manhattan** — distância percorrendo só na horizontal e vertical (como andar em quarteirões)
- **Contagem de instruções** — quantos comandos foram executados

## Como compilar e rodar?

```bash
gcc implementacao.c main.c -o robo.exe
./robo.exe
```