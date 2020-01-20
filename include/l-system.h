#ifndef _L_SYSTEM_
#define _L_SYSTEM_

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_reader.h"

typedef struct {
  int depth;
  double angle;
  char* final;
  char* original;
} LSystem;

// Functions
LSystem* new_LSystem(char* start, int depth, double angle);
void free_LSystem(LSystem* this);
void LSystem_runTest();
void LSystem_print(LSystem* this);

// Draw LSystem functions
void LSystem_draw();

#endif
