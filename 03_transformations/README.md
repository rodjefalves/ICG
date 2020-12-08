#  ATIVIDADE 3

## Integrantes da dupla:

**Jeferson Alves Rodrigues**

**Viviane Cristine Alves**

## Sobre a atividade

Esta atividade tem como objetivo principal incentivar os alunos a instalarem as dependências necessárias e aplicarem o conhecimento obtido em aula da estrutura do pipeline gráfico e treinar a implementação das suas variadas possibilidades de transformações geométricas. Para isso, o professor disponibilizou um código template que será utilizado com as seguintes dependências:

* glm
* GLEW

## Exercício 1

Após a instalação das dependências necessárias e sua execução no terminal com o comando sugerido pelo professor, visto que o arquivo makefile não estava funcionando por algum motivo e pela preferência dos integrantes da dupla em utilizar o terminal. O comando de compilação foi:

`g++ -Wall -Wextra -Wpedantic -std=c++17 -O0 -g3 -DDEBUG main.cpp -lglut -lGLEW -lGLU -lGL -o transform gl`

O comando de execução foi:

`./transform gl`

Gerando a figura abaixo:

![Figura Inicial](https://github.com/rodjefalves/ICG/blob/main/Imagens/figura1.png)

Para a realização do primeiro exercício e geração da imagem solicitada, foi necessário efetuar uma mudança na **matriz model**, com fatores de escala em (x, y, z) = (1/3, 3/2, 1), ficando assim:

![Exercício 1 - Código](https://github.com/rodjefalves/ICG/blob/main/Imagens/figura5cod.jpeg)

Esse código gerou a seguinte imagem:

![Exercício 1](https://github.com/rodjefalves/ICG/blob/main/Imagens/figura5.jpeg)

## Exercício 2

Para geração da imagem solicitada no segundo exercício, foi necessário efetuar outra mudança na **matriz model**, com translações em (x, y, z) = (1, 0, 0), ficando assim:

![Exercício 2 - Código](https://github.com/rodjefalves/ICG/blob/main/Imagens/figura6cod.jpeg)

Esse código gerou a seguinte imagem:

![Exercício 2](https://github.com/rodjefalves/ICG/blob/main/Imagens/figura6.jpeg)

## Exercício 3

O terceiro exercício dessa atividade necessitou de mudança similar na estrutura do código, porém, dessa vez, o foco foi a **matriz projection**, com parâmetro d = 1/8:

![Exercício 3 - Código](https://github.com/rodjefalves/ICG/blob/main/Imagens/figura7cod.jpeg)

Esse código gerou a seguinte imagem:

![Exercício 3](https://github.com/rodjefalves/ICG/blob/main/Imagens/figura7.jpeg)

## Exercício 4

Para a realização do que é proposto nesse exercício foi necessário adicionar mais código a solução, baseado em teorias que o professor passou em aula. Os valores utilizados para esse exercício foram: posição da câmera = (− 1 /10 , 1 /10 , 1 /10 ), vetor Up da câmera = (0, 1, 0), ponto para o qual a câmera está apontando = (0, 0, −1).

![Exercício 4 - Código](https://github.com/rodjefalves/ICG/blob/main/Imagens/figura8cod.jpeg)

Esse código gerou a seguinte imagem:

![Exercício 4](https://github.com/rodjefalves/ICG/blob/main/Imagens/figura8.jpeg)

## Exercício 5

Esse exercício tinha duas condições: 1. modificar as 3 matrizes afim de formar uma nova cena; 2. ser diferente do que já foi apresentado. Para a realização desse exercício dividimos em 3 passos, sendo o primeiro a mudança na **matriz projection** com finalidade de mudar o tamanho e posição dos triângulos, a segunda uma mudança na **matriz model**, para virar os triângulos de cabeça para baixo e por fim a terceira, responsável por mudar o zoom e posição da câmera.

Os valores utilizados para esse exercício foram: posição da câmera = (0.3, 0, 0.1), vetor Up da câmera = (0, 1, 0), ponto para o qual a câmera está apontando = (0, 0, −1).

### 1º Passo: modificar matriz projection

![Exercício 5 - Código 1](https://github.com/rodjefalves/ICG/blob/main/Imagens/transflivre1cod.png)

Esse código gerou a seguinte imagem:

![Exercício 5 - Passo 1](https://github.com/rodjefalves/ICG/blob/main/Imagens/transflivre1.jpeg)

### 2º Passo: modificar matriz model

![Exercício 5 - Código 2](https://github.com/rodjefalves/ICG/blob/main/Imagens/transflivre2cod.png)

Esse código gerou a seguinte imagem:

![Exercício 5 - Passo 2](https://github.com/rodjefalves/ICG/blob/main/Imagens/transflivre2.jpeg)

### 3º Passo: modificar matriz view

![Exercício 5 - Código 3](https://github.com/rodjefalves/ICG/blob/main/Imagens/transflivre3cod.png.png)

Esse código gerou a seguinte imagem:

![Exercício 5 - Passo 3](https://github.com/rodjefalves/ICG/blob/main/Imagens/transflivre3.png)
