#ifndef _L_SYSTEM_
#define _L_SYSTEM_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int depth;
  double angle;
  char* final;
  char* original;
} LSystem;

LSystem* new_LSystem(char* start, int depth, double angle);

LSystem* LSystem_run(LSystem* this);

void LSystem_print(LSystem* this);

void LSystem_free(LSystem* this);

#endif
