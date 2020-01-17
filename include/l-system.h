#ifndef _L_SYSTEM_
#define _L_SYSTEM_

typedef struct {
  int depth;
	double angle;
  char* final;
  char* original;
} LSystem;

LSystem* new_LSystem(char* start, int depth, double angle);

LSystem* lsys_run(LSystem* this);

void lsys_print(LSystem* this);

void lsys_free(LSystem* this);

#endif
