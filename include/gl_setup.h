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

void GLSetup_init(void);

void GLSetup_display();

void GLSetup_displayLSystem();

void GLSetup_drawLSystem();

void GLSetup_setMaterial();

void GLSetup_LSystemCondition(char* start, double angle);

void GLSetup_displayExample(void);

void GLSetup_reshape(int w, int h);

void GLSetup_keyboard(unsigned char key, int x, int y);

void GLSetup_loadTexture(char* filePath);

void GLSetup_mouseControl(int button, int state, int x, int y);

void GLSetup_run(int argc, char** argv);

#endif