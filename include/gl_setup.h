#ifndef _GL_SETUP_
#define _GL_SETUP_

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

void GlSetup_init(void);

void GlSetup_displayExample(void);

void GlSetup_reshape(int w, int h);

void GlSetup_keyboard(unsigned char key, int x, int y);

void GlSetup_loadTexture(char* filePath);

void GlSetup_run(int argc, char** argv, void (*draw)(void));

#endif