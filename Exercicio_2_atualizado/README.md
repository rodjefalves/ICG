#  EXERCÍCIO 1

## Integrantes da dupla:

**Jeferson Alves Rodrigues**

**Viviane Cristine Alves**

## Sobre a atividade

Esta atividade tem como objetivo principal levar o discente a entender como funciona algoritmos de rasterização e implementar funções para rasterizar pixels, linhas e triângulos. A rasterização foi feita simulando acesso direto a memória de vídeo por meio de um framework que o próprio professor desenvolveu e disponibilizou. Nesse framework existe um ponteiro, o fb_ptr, que aponta para o primeiro byte do color buffer e é essencial para a realização desta atividade.

Foram alterados os arquivos arquivos mygl.h e mygl.c. Sendo o mygl.h o local onde contém as funções que efetuaram a rasterização de  pixel (PutPixel), de linha (DrawLine) e de triângulo (DrawTriangule).

## A função PutPixel

Para rasterizar um ponto, ou seja, um pixel foi necessário desenvolver a função PutPixel. Para atingir esse objetivo, a função precisou receber como parâmetros as coordenadas (x,y) do pixel na tela e uma cor. O processo de desenvolvimento seguiu o que foi explicado na aula 3 de ICG do semestre 2020.1 sobre FrameBuffer. Para efeitos dessa disciplina, nesse semestre, **foi considerado que o pixel (0,0) se encontraria no canto inferior esquerdo**, como demonstrado abaixo:

![Pixel (0,0) - Origem](https://jeferson-wwe.000webhostapp.com/img-icg/pixelO.png)

Outro material importante para o desenvolvimento do algoritmo se encontra na mesma aula e é o conceito de offset e seu cálculo. Foi a partir desse referencial que desenvolvemos a função que resteriza pixels. O offset pode ser observado abaixo:

![Offset](https://jeferson-wwe.000webhostapp.com/img-icg/offset.png)

O offset é útil pois ele define em que posição do color buffer irá se localizar cada pixel e está intimamente ligado aos 4 bytes que representam uma cor (RGBA), como demosntrado abaixo:

![Cor RGBA e Offset](https://jeferson-wwe.000webhostapp.com/img-icg/razaoOffset.png)

## A função DrawLine

