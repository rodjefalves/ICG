#ifndef MYGL_H
#define MYGL_H

#include <string.h>

#include "core.h"
#include "frame_buffer.h"

// Declaração da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void);

//
// >>> Declare aqui as funções que você implementar <<<
//

struct Cores {
    int red;
    int green;
    int blue;
    int alpha;
} typedef Cores;

Cores vermelho = {255,0,0,255};
Cores verde = {0,230,64,1};
Cores azul = {44,130,201,1};

// Função para rasterizar ponto em tela
void PutPixel (int x, int y, Cores cores)  {

    fb_ptr[(x*4 + y*4*IMAGE_WIDTH) + 0] = cores.red;
    fb_ptr[(x*4 + y*4*IMAGE_WIDTH) + 1] = cores.green;
    fb_ptr[(x*4 + y*4*IMAGE_WIDTH) + 2] = cores.blue;
    fb_ptr[(x*4 + y*4*IMAGE_WIDTH) + 3] = cores.alpha;

}

void coresInterpoladas () {
        
}

void DrawLine(int x0, int y0, int x1, int y1, Cores cor)
{

    int dx, dy, dL, dNE;
    int mvX, mvY, dec;

    dx = x1 - x0;
    dy = y1 - y0;
    
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

    if (dx < 0)
    {
        DrawLine(x1, y1, x0, y0, cor);
        return;
    }

    PutPixel(x0, y0, cor);


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

            PutPixel(x0, y0, cor);
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
            PutPixel(x0, y0, cor);
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
            PutPixel(x0, y0, cor);
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

            PutPixel(x0, y0, cor);
        }
    }
}


void DrawTriangule(int x0, int y0, int x1, int y1, int x2, int y2, Cores corV1, Cores corV2, Cores corV3) {
    DrawLine(x0,y0,x1,y1, corV1);
    DrawLine(x2,y2,x1,y1, corV2);
    DrawLine(x1,y1,x2,y2, corV3);
    
}


#endif  // MYGL_H
