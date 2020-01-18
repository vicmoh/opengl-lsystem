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

LSystem* new_LSystem(char* start, int depth, double angle);

void LSystem_runTest();

LSystem* LSystem_recurse(LSystem* this);

void LSystem_print(LSystem* this);

void LSystem_free(LSystem* this);

#endif
