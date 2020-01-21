#include "l-system.h"

LSystem* new_LSystem(char* start, int depth, double angle) {
  if (start == NULL) return NULL;
  const int MAX_MEM = 256 * 8;
  if (MAX_MEM < strlen(start)) {
    printf("new_LSystem(): MEMORY_EXCEEDED!");
    return NULL;
  }

  // Initialize
  LSystem* new = malloc(sizeof(LSystem));
  new->depth = 0;
  new->angle = angle;
  new->final = calloc(MAX_MEM, sizeof(char));
  strcpy(new->final, "");
  new->original = calloc(MAX_MEM, sizeof(char));
  strcpy(new->original, start);

  // Get the process string
  for (int i = 0; i < depth - 1; i++) {
    for (int x = 0; x < strlen(new->original); x++)
      if (new->original[x] == 'F') {
        new->final = realloc(
            new->final,
            sizeof(char) * (strlen(new->final) + strlen(new->original) + 4));
        sprintf(new->final, "%sF%s", new->final, new->original);
      } else {
        new->final = realloc(
            new->final,
            sizeof(char) * (strlen(new->final) + strlen(new->original) + 4));
        sprintf(new->final, "%s%c", new->final, new->original[x]);
      }
  }
  return new;
}

void free_LSystem(LSystem* this) {
  if (this != NULL) return;
  free(this->final);
}

void LSystem_runTest() {
  printf("Testing LSystem:\n");
  LSystem* ls = new_LSystem("F[+F]", 2, 45);
  printf("ls = ");
  LSystem_print(ls);
  free_LSystem(ls);
}

LSystem* LSystem_recurse(LSystem* this) {
  (this->depth)++;
  this = LSystem_recurse(this);
  return this;
}

void LSystem_print(LSystem* this) {
  printf("{depth: %d, original: %s, final: %s}\n", this->depth, this->original,
         this->final);
}

/* -------------------------------------------------------------------------- */
/*                           Draw L-System functions                          */
/* -------------------------------------------------------------------------- */

void _LSystem_drawBasedOnCondition(char* start, double angle) {
  const bool SHOW_DEBUG = false;
  double sphereY = 0;
  char* final = strdup(start);
  if (SHOW_DEBUG) printf("Drawing: %s\n", final);
  for (int x = 0; x < strlen(final); x++) {
    char curState = final[x];
    if (curState == 'F') {
      if (SHOW_DEBUG) printf("Draw solid sphere.\n");
      glPushMatrix();
      sphereY += 0.1;
      glTranslatef(0, sphereY, 0);
      glutSolidSphere(0.1, 15, 15);
      glPopMatrix();
    } else if (curState == '+') {
      if (SHOW_DEBUG)
        printf("Rotate z axis by %f degrees to the right.\n", angle);
      glRotatef(angle, 0, 0, 1);
    } else if (curState == '-') {
      if (SHOW_DEBUG)
        printf("Rotate z axis by %f degrees to the left.\n", angle);
      glRotatef(angle, 0, 0, -1);
    } else if (curState == '[') {
      if (SHOW_DEBUG) printf("Push matrix.\n");
      glPushMatrix();
    } else if (curState == ']') {
      if (SHOW_DEBUG) printf("Pop matrix.\n");
      glPopMatrix();
    }
  }
  free(final);
}

void LSystem_draw() {
  FileReader* fr = new_FileReader("./assets/sample1.txt");
  LSystem* ls = new_LSystem(FileReader_getLineAt(fr, 2),
                            atoi(FileReader_getLineAt(fr, 1)),
                            atof(FileReader_getLineAt(fr, 0)));
  /* set starting location of objects */
  _LSystem_drawBasedOnCondition(ls->final, ls->angle);
  // Free
  free_LSystem(ls);
}
