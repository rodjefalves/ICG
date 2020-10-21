#  EXERCÍCIO 1

## Integrantes da dupla:

**Jeferson Alves Rodrigues**

**Viviane Cristine Alves**

## Sobre a atividade

Esta atividade tem como objetivo principal levar o discente a entender como funciona algoritmos de rasterização e implementar funções para rasterizar pixels, linhas e triângulos. A rasterização foi feita simulando acesso direto a memória de vídeo por meio de um framework que o próprio professor desenvolveu e disponibilizou. Nesse framework existe um ponteiro, o fb_ptr, que aponta para o primeiro byte do color buffer e é essencial para a realização desta atividade.

Foram alterados os arquivos arquivos **mygl.h** e **mygl.c**. Sendo o **mygl.h** o local onde contém as funções que efetuaram a rasterização de  **pixel (PutPixel), de linha (DrawLine) e de triângulo (DrawTriangule)** e o **mygl.c** onde foram chamadas as funções.

## A função PutPixel

Para rasterizar um ponto, ou seja, um pixel foi necessário desenvolver a função PutPixel. Para atingir esse objetivo, a função precisou receber como parâmetros as coordenadas (x,y) do pixel na tela e uma cor. O processo de desenvolvimento seguiu o que foi explicado na aula 03 - Framebuffer de ICG do semestre 2020.1. Para efeitos dessa disciplina, nesse semestre, **foi considerado que o pixel (0,0) se encontraria no canto inferior esquerdo**, como demonstrado abaixo:

![Pixel (0,0) - Origem](https://jeferson-wwe.000webhostapp.com/img-icg/pixelO.png)

Outro material importante para o desenvolvimento do algoritmo se encontra na mesma aula e é o conceito de offset e seu cálculo. Foi a partir desse referencial que desenvolvemos a função que resteriza pixels. O offset pode ser observado abaixo:

![Offset](https://jeferson-wwe.000webhostapp.com/img-icg/offset1.png)

O offset é útil pois ele define em que posição do color buffer irá se localizar cada pixel e está intimamente ligado aos 4 bytes que representam uma cor (RGBA), como demosntrado abaixo:

![Cor RGBA e Offset](https://jeferson-wwe.000webhostapp.com/img-icg/razaoOffset1.png)

O código da função ficou assim:

~~~Código em C
// Função para rasterizar ponto em tela
void PutPixel (int x, int y, Cores cores)  {

    fb_ptr[(x*4 + y*4*IMAGE_WIDTH) + 0] = cores.red;
    fb_ptr[(x*4 + y*4*IMAGE_WIDTH) + 1] = cores.green;
    fb_ptr[(x*4 + y*4*IMAGE_WIDTH) + 2] = cores.blue;
    fb_ptr[(x*4 + y*4*IMAGE_WIDTH) + 3] = cores.alpha;
}
~~~

Abaixo um exemplo de 3 pixels, um de cada cor rasterizados por esse código:

![Exemplos de pixels](https://jeferson-wwe.000webhostapp.com/img-icg/pixels.png)

## A função DrawLine

A função foi feita baseada no algoritmo que o professor passou em aula. Mais especificamente na aula 06 - Rasterização de Linhas: Algoritmo do Ponto Médio.

![Exemplos de linhas](https://jeferson-wwe.000webhostapp.com/img-icg/linhas.png)

Abaixo o algoritmo do ponto médio, que funciona somente para o primeiro octante adaptamos para os diversos analisando as simetrias entre eles (1 e 5; 2 e 6; 3 e 7; 4 e 8):

~~~Código em C
// Função para rasterizar linhas em tela
void DrawLine(int x0, int y0, int x1, int y1) {

    dx = x1 - x0;
    dy = y1 - y0;

    dec = 2*dy - dx; //Primeiro Pixel
    dNE = 2*(dy -  dx); //Direção Nordeste
    dL = 2*dy; //Direção Leste

    x = x0;
    y = y0;
    
    PutPixel(x, y,vermelho);

    while (x < x1){
            if (dec <= 0){
                dec += dL;
                x++;
            } else {
                dec += dNE;
                x++;
                y++;
            }
        PutPixel(x, y, cor);
        }
}
~~~

**Observação:** a versão completa pode ser vista no arquivo **mygl.h** com as devidas adaptações para os demais octantes.

## A função DrawTriangule

Para rasterizar um triângulo fizemos, antes da função um teste de lógica. Rasterizamos 3 linhas, contendo ao total 3 vértices nomeados de: 

V1 = (x0,y0)
V2 = (x1, y1)
V3 = (x2, y2)

Sendo a primeira reta formada pelos V1 e V2, a segunda pelo V2 e V3 e a terceira por V3 e V1. Colocamos valores nesses pares ordenados e gerou o seguinte triângulo:

![Triângulo com três linhas](https://jeferson-wwe.000webhostapp.com/img-icg/triangulo1.png)

Comprovada a lógica que três retas formariam um triângulo, implementamos a função DrawTriangule baseada nessa lógica:

~~~Código em C
// Função para rasterizar triângulo em tela
void DrawTriangule(int x0, int y0, int x1, int y1, int x2, int y2, Cores corV1, Cores corV2, Cores corV3) {
    DrawLine(x0,y0,x1,y1, corV1);
    DrawLine(x1,y1,x2,y2, corV2);
    DrawLine(x2,y2,x1,y1, corV3);

}
~~~

Porém, ao rasterizar um triângulo com os mesmos valores de vértices, com a DrawTriangule, tivemos uma surpresa:

![Triângulo com DrawTriangule](https://jeferson-wwe.000webhostapp.com/img-icg/triangulo3.png)

Até a presente data, da conclusão do prazo, não conseguimos descobrir qual o problema da lógica, provavelmente foi algo durante a adaptação para os demais octantes.

## Dificuldades encontradas

1. Conseguimos interpolar cores em linhas simuladas com **for** contudo não conseguimos incluir essa função nas linhas do algoritmo do ponto médio;
2. Tivemos problema na rasterização de triângulos com a função DrawTriangule e não conseguimos identificar a tempo qual a origem deste problema.

## Referências

<http://www.univasf.edu.br/~jorge.cavalcanti/comput_graf04_prim_graficas2.pdf>
