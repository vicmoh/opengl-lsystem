#ifndef _GL_SETUP_
#define _GL_SETUP_

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

void glSetup_init(void);

void glSetup_display(void);

void glSetup_reshapeExample(int w, int h);

void glSetup_keyboard(unsigned char key, int x, int y);

void glSetup_loadTexture(char* filePath);

void glSetup_run(int argc, char** argv);

#endif