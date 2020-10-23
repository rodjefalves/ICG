#ifndef MYGL_H
#define MYGL_H

#include <string.h>

#include "core.h"
#include "frame_buffer.h"


struct Cor;  
typedef struct Cor Cores;
// Declaração da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void);
void PutPixel (int x, int y, Cores cores);
void DrawLine(int x0, int y0, int x1, int y1, Cores cor1, Cores cor2);
void DrawTriangule(int x0, int y0, int x1, int y1, int x2, int y2, Cores cor1, Cores cor2);
Cores coresInterpoladas(float p, Cores c1, Cores c2);
float distanciaPontos(int x0, int y0, int x1, int y1);
float raizQuadrada (float num);



#endif  // MYGL_H
