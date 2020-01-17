#include "l-system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LSystem* new_LSystem(char* start) {
  if (start == NULL) return NULL;
  const int MAX_MEM = 256 * 8;
  if (MAX_MEM < strlen(start)) {
    printf("new_LSystem(): MEMORY_EXCEEDED!");
    return NULL;
  }

  // Initialize
  LSystem* new = malloc(sizeof(LSystem));
  new->depth = 0;
  new->final = calloc(MAX_MEM, sizeof(char));
  strcpy(new->final, "");
  new->original = calloc(MAX_MEM, sizeof(char));
  strcpy(new->original, start);

  // get string.
  for (int x = 0; x < strlen(new->original); x++)
    if (new->original[x] == 'F')
      sprintf(new->final, "%sF%s", new->final, new->original);
    else
      sprintf(new->final, "%s%c", new->final, new->original[x]);

  return new;
}

LSystem* lsys_run(LSystem* this) {
  (this->depth)++;
  this = lsys_run(this);
}

void lsys_print(LSystem* this) {
  printf("{depth: %d, original: %s, final: %s}\n", this->depth, this->original,
         this->final);
}

void lsys_free(LSystem* this) {
  if (this != NULL) return;
  free(this->final);
}
