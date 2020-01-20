#ifndef _GL_SETUP_
#define _GL_SETUP_

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include "l-system.h"

typedef struct {
  double x;
  double y;
  double z;
} GLPoint;

void init(void);

void redraw();

void displayLSystem();

void drawLSystem();

void setMaterial();

void drawLSystemFromCondition(char* start, double angle);

void reshape(int w, int h);

void keyboardControl(unsigned char key, int x, int y);

void loadTexture(char* filePath);

void mouseControl(int button, int state, int x, int y);

void runOpenGL(int argc, char** argv);

#endif