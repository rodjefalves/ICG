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

## Interpolação de cores

Uma das etapas mais difíceis foi a interpolação de cores. A princípio pensamos em utilizar um for para ir mudando os valores da primeira a segunda cor, mudando seus valores RGBA e isso até deu certo, porém somente se tivessemos controle da quantidade de pixel que seria rasterizado não formação de linhas então descartamos essa solução. Com nossas pesquisas descobrimos um algoritmo de interpolação de cores que usa distância de pontos.

O algoritmo pode ser observado abaixo:

~~~Código em C
//Interpolação das cores
Cores coresInterpoladas (float p, Cores c1, Cores c2) {
    Cores cores;
    cores.red = c1.red*p + (1-p)*c2.red;
    cores.green = c1.green*p + (1-p)*c2.green;
    cores.blue = c1.blue*p + (1-p)*c2.blue;
    cores.alpha = c1.alpha*p + (1-p)*c2.alpha;
    return cores;
        
}

//calculo da distancia dos pontos (total)
float distanciaPontos(int x0, int y0, int x1, int y1){
    //a distancia entre pontos eh uma raiz quadrada
    float valorDist;

    if (x1 == x0)
    {
        valorDist = y1 - y0;
    }
    else if (y1 == y0)
    {
        valorDist = x1 - x0;
    } else
    {
        valorDist = raizQuadrada((x1-x0)*(x1-x0)*(y1-y0)*(y1-y0));
    }
    return valorDist;
}
~~~

E para esses códigos funcionarem, é preciso chamar em cada octante com os seguintes códigos:

~~~
distP = distanciaPontos(x0, y0, x1, y1);
color = coresInterpoladas(distP/distTotal,cor1,cor2);
~~~

![Linhas Interpoladas](https://jeferson-wwe.000webhostapp.com/img-icg/linhasInterpoladas.png)

## A função DrawTriangule

Para rasterizar um triângulo fizemos, antes da função um teste de lógica. Rasterizamos 3 linhas, contendo ao total 3 vértices nomeados de: 

V1 = (x0,y0)
V2 = (x1, y1)
V3 = (x2, y2)

Sendo a primeira reta formada pelos V1 e V2, a segunda pelo V2 e V3 e a terceira por V3 e V1. Colocamos valores nesses pares ordenados, com cores para cada uma das retas para facilitar a visualização e geramos o seguinte triângulo:

![Triângulo com três linhas](https://jeferson-wwe.000webhostapp.com/img-icg/triangulo1.png)

Comprovada a lógica que três retas formariam um triângulo, implementamos a função DrawTriangule baseada nessa lógica:

~~~Código em C
// Função para rasterizar triângulo em tela
void DrawTriangule(int x0, int y0, int x1, int y1, int x2, int y2, Cores corV1, Cores corV2, Cores corV3) {
    DrawLine(x0,y0,x1,y1, corV1);
    DrawLine(x1,y1,x2,y2, corV2);
    DrawLine(x2,y2,x0,y0, corV3);

}
~~~

Rasterização de um triângulo com os mesmos valores de vértices, com a DrawTriangule e a interpolação de cores, tivemos uma surpresa:

![Triângulo Interpolado](https://jeferson-wwe.000webhostapp.com/img-icg/trianguloInterpolado.png)

## Dificuldades encontradas

1. A primeira dificuldade encontrada foi generalizar o algoritmo para os todos os octantes, então fizemos a análise de quais similaridades existiam entre os 8 e como generalizar o algoritmo do ponto médio;
2. Na interpolação de cores o algoritmo utilizado não funcionava para retas verticais e horizontais, pois utilizamos a distância de pontos, que utiliza raiz quadrada e sempre que a raiz dava zero (devido aos x ou y finais e iniciais serem iguais), a função de interpolação não retornava nada. Contudo, a resolução foi simples, visto que se as retas forem paralelas aos eixos, substitui-se a raiz quadrada por uma simples subtração, de acordo com o eixo cujo a reta é paralela.

## Referências

<http://www.univasf.edu.br/~jorge.cavalcanti/comput_graf04_prim_graficas2.pdf>
