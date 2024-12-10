# Cub3D: Uma Viagem aos Anos 80-90

O **Cub3D** é um projeto incrível que nos transporta para a época em que os computadores tinham limitações significativas para renderizar gráficos 3D. Com a técnica do **ray casting**, foi possível criar jogos jogáveis mesmo em computadores medianos.

Nos dias atuais, com processadores poderosos, memórias rápidas e armazenamento de alta capacidade, é fascinante revisitar essa técnica que solucionou um dos maiores desafios da computação gráfica da época. Para programadores, entender o **ray casting** é uma lição valiosa em inovação e eficiência.

---

## O Conceito do Ray Casting

A ideia principal do **ray casting** é simples e engenhosa:

1. Trabalhar com um **mapa 2D** que limita o campo de visão.
2. Realizar cálculos matemáticos para determinar as paredes visíveis ao jogador.

Por exemplo, imagine o seguinte mapa:

11111111 
10000001 
10000001 
10000001 
10000P11 
11111111


O ponto `P` representa a posição inicial do jogador. Normalmente, utilizamos um **FOV (Field of View)** de 66 graus para criar uma experiência imersiva. Representando o FOV no mapa, teríamos algo assim:

11111111 
10\00001 
100\0001 
1000\0/1 
10000P11 
11111111


Aqui, os caracteres `\` e `/` simulam o ângulo de visão do jogador.

---

## Como Funciona o Ray Casting?

1. **Transformação do Mapa 2D:** 
   Primeiro, o mapa é convertido em um sistema de coordenadas 2D. A posição do jogador é representada por valores `sx` e `sy`, centralizados no bloco inicial.

2. **Cálculo de Distância:**
   O objetivo é calcular a distância entre o jogador e as paredes do mapa. Para isso, utilizamos:
   - **DeltaDist:** Comprimento necessário para sair de um bloco para o próximo (horizontal ou vertical).
   - **SideDist:** Distância inicial percorrida antes de sair do bloco atual.

3. **Iteração por Colunas:**
   Com a largura da tela definida, iteramos por cada coluna vertical (valor `x`) e calculamos as distâncias para identificar onde o jogador enxerga paredes, chão e teto. Por exemplo:

1000\0/1 
10000P11 
11111111

Neste caso, o `\` seria o valor `1` e o `P` (meio bloco) seria `0.5`. Para alcançar a parede, precisaríamos percorrer uma distância de `3.5`.

4. **Renderização:**
   A cada iteração, verificamos se um raio atinge uma parede. Quando isso ocorre, desenhamos a parede na tela.

---

Essa explicação foi simplificada para ilustrar os conceitos principais. Caso tenha interesse em mais detalhes, entre em contato comigo ou com o **Diogo**, ou pesquise por artigos sobre ray casting na internet.
