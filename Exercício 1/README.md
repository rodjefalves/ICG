#  EXERCÍCIO 1

## Sobre a atividade

Esta atividade tem como objetivo principal instigar o discente a conhecer o funcionamento do OpenGL Moderno e como se efetua a configuração do ambiente de desenvolvimento do mesmo. A atividade consistiu em dá um clone no repositório cedido pelo professor e tentar executar de modo que o resultado seja um triângulo colorido tal qual a figura abaixo:

![exemplo do resultado](https://jeferson-wwe.000webhostapp.com/img-icg/exemplo.png)


## Configurando o ambiente

O ambiente foi configurado no sistema **Ubuntu Linux 20.04**. Para isso, foi necessário atualizar os pacotes instalados no sistema com o código:

> sudo apt-get install update

Em seguida foi necessário instalar a freeGlut e suas dependências com o código:

> sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev

## Executando o programa

Foi feito um teste inicial a tentativa de executar o programa na IDE [Code::Blocks](http://www.codeblocks.org/), porém sem sucesso. Então a etratégia utilizada foi rodar o programa pelo terminal para ter a certeza que ele estava funcionando e as libs tinham sido corretamente instaladas. Para isso, compilou-se o arquivo **"main.c"** gerando um executável **"exercicio-hello-world"**. Executando-o em seguida:

> gcc main.c -o exercicio-hello-world -lglut -lGLU -lGL

> ./exercicio-hello-world

**O resultado pode ser conferido no gif abaixo:**

![Alt Text](https://media.giphy.com/media/vFKqnCdLPNOKc/giphy.gif)

## Conclusão

Não foram encontradas grandes dificuldades na instalação e execução do programa da reprodução em tela do triângulo colorido, dessa maneira, atingido o resultado previsto, não foi necessária a configuração da IDE anteriormente mencionada.

