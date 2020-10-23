#include "mygl.h"


struct Cor {
    int red,green,blue,alpha;
};



// Função para rasterizar ponto em tela
void PutPixel (int x, int y, Cores cores)  {

    fb_ptr[(x*4 + y*4*IMAGE_WIDTH) + 0] = cores.red;
    fb_ptr[(x*4 + y*4*IMAGE_WIDTH) + 1] = cores.green;
    fb_ptr[(x*4 + y*4*IMAGE_WIDTH) + 2] = cores.blue;
    fb_ptr[(x*4 + y*4*IMAGE_WIDTH) + 3] = cores.alpha;

}

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
    return raizQuadrada((x1-x0)*(x1-x0)*(y1-y0)*(y1-y0));
}

//implementacao da raiz quadrada
float raizQuadrada (float num){
    int n;
    float r = num;
   
    for (n = 0; n < 10; ++n)
          r = r/2 + num/(2*r);           
    return(r);    
}    

void DrawLine(int x0, int y0, int x1, int y1, Cores cor1, Cores cor2){


    int dx, dy, dL, dNE;
    int mvX, mvY, dec;
    float distP, distTotal;
    

    distTotal = distanciaPontos(x0, y0, x1, y1);

    dx = x1 - x0;
    dy = y1 - y0;


    if (dx < 0)
    {
        DrawLine(x1, y1, x0, y0, cor1, cor2);
        return;
    }


    if (dx > 0)
    {
        mvX = 1;
    }
    else
    {
        mvX = -1;
    }

    if (dy > 0)
    {
        mvY = 1;
    }
    else
    {
        mvY = -1;
    }

    Cores color = cor1;
    PutPixel(x0, y0, cor1);
    //Octantes 1 e 5
    if (abs(dx) >= abs(dy) && dy >= 0)
    {
        dec = 2 * dy - dx;
        dL = 2 * dy;
        dNE = 2 * (dy - dx);

        while (x0 != x1 || y0 != y1)
        {
            if (dec <= 0)
            {
                dec += dL;
                x0 += mvX;
            }
            else
            {
                dec += dNE;
                x0 += mvX;
                y0 += mvY;
            }
            
            distP = distanciaPontos(x0, y0, x1, y1);
            color = coresInterpoladas(distP/distTotal,cor1,cor2);
            PutPixel(x0, y0, color);

            
        }
    }

    //Octantes 2 e 6
    if (abs(dy) > abs(dx) && dy >= 0)
    {
        dec = 2 * dx - dy;
        dL = 2 * dx;
        dNE = 2 * (dx - dy);

        while (x0 != x1|| y0 != y1)
        {
            if (dec <= 0)
            {
                dec += dL;
                y0 += mvY;
            }
            else
            {
                dec += dNE;
                x0 += mvX;
                y0 += mvY;
            }
            distP = distanciaPontos(x0, y0, x1, y1);
            color  = coresInterpoladas(distP/distTotal,cor1,cor2);
            PutPixel(x0, y0, color);
        }
    }

    // Octantes 3 e 7
    if (abs(dy) > abs(dx) && dy <= 0)
    {
        dec = 2 * dx + dy;
        dL = 2 * dx;
        dNE = 2 * (dx + dy);

        while (x0 != x1 || y0 != y1)
        {
            if (dec < 0)
            {
                dec += dL;
                y0 += mvY;
            }
            else
            {
                dec += dNE;
                x0 += mvX;
                y0 += mvY;
            }
            distP = distanciaPontos(x0, y0, x1, y1);
            color  = coresInterpoladas(distP/distTotal,cor1,cor2);
            PutPixel(x0, y0, color);
        }
    }

    //Octantes 4 e 8
    if (abs(dx) >= abs(dy) && dy <= 0)
    {
        dec = -2 * dy - dx;
        dL = -2 * dy;
        dNE = 2 * (-dy - dx);

        while (x0 != x1 || y0 != y1)
        {
            if (dec <= 0)
            {
                dec += dL;
                x0 += mvX;
            }
            else
            {
                dec += dNE;
                x0 += mvX;
                y0 += mvY;
            }

            distP = distanciaPontos(x0, y0, x1, y1);
            color  = coresInterpoladas(distP/distTotal,cor1,cor2);
            PutPixel(x0, y0, color);

        }
    }
      PutPixel(x0, y0, cor2);
}


void DrawTriangule(int x0, int y0, int x1, int y1, int x2, int y2, Cores cor1, Cores cor2) {
    DrawLine(x0,y0,x1,y1, cor1, cor2);
    DrawLine(x1,y1,x2,y2, cor1, cor2);
    DrawLine(x2,y2,x0,y0, cor1, cor2);
    
}


void MyGlDraw(void) {
    Cores vermelho = {255,0,0,255};
    Cores verde = {0,230,64,1};
    Cores azul = {44,130,201,1};

    Cores cor1, cor2;
    cor1 = vermelho, verde, azul;
    cor2 = azul, verde, vermelho;
    
    /* pontos  */
    //PutPixel(300, 300, vermelho);
    //PutPixel(300, 350, azul);
    //PutPixel(300, 250, verde);

    /* linhas 
    DrawLine(100,100,200,500, cor1,cor2);
    DrawLine(150,50,500,50, cor1,cor2);
    DrawLine(400,100,200,300, cor2,cor1);
*/
    

     
    //DrawTriangule(200,100,500,100,350,300, cor1, cor2);
    DrawLine(100, 256, 400, 256, cor1, cor2);


}
