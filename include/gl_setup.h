#ifndef _GL_SETUP_
#define _GL_SETUP_

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdio.h>
#include <stdlib.h>

void GlSetup_init(void);

void GLSetup_draw();

void GLSetup_display();

void GLSetup_displaySetup();

void GlSetup_displayExample(void);

void GLSetup_displayLSystem(void);

void GlSetup_reshape(int w, int h);

void GlSetup_keyboard(unsigned char key, int x, int y);

void GlSetup_loadTexture(char* filePath);

void GlSetup_run(int argc, char** argv);

#endif