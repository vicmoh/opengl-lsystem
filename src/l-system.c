#include "l-system.h"

FileReader* LSystem_fileReader = NULL;

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
      if (new->original[x] == 'F')
        sprintf(new->final, "%sF%s", new->final, new->original);
      else
        sprintf(new->final, "%s%c", new->final, new->original[x]);
  }

  return new;
}

void LSystem_setFile(char* fileName) {
  if (fileName == NULL) return;
  LSystem_fileReader = new_FileReader(fileName);
}

void LSystem_draw() {
  if (LSystem_fileReader == NULL) printf("Warning: File reader is null.\n");
  LSystem* ls = new_LSystem(LSystem_fileReader->line[2],
                            atoi(LSystem_fileReader->line[1]),
                            atof(LSystem_fileReader->line[0]));
  LSystem_checkCondition(ls);
  LSystem_free(ls);
}

void LSystem_checkCondition(LSystem* this) {
  char* final = strdup(this->final);
  printf("Drawing: %s\n", final);
  for (int x = 0; x < strlen(final); x++) {
    char curState = final[x];
    if (curState == 'F') {
      printf("Draw solid sphere.\n");
      glutSolidSphere(1.0, 15, 15);
    } else if (curState == '+') {
      printf("Rotate z axis by %f degrees to the right.\n", this->angle);
      glRotatef(this->angle, 0, 0, 1);
    } else if (curState == '-') {
      printf("Rotate z axis by %f degrees to the left.\n", this->angle);
      glRotatef(this->angle, 0, 0, 1);
    } else if (curState == '[') {
      printf("Push matrix.\n");
      glPushMatrix();
    } else if (curState == ']') {
      printf("Pop matrix.\n");
      glPopMatrix();
    }
  
  free(final);
}

void LSystem_runTest() {
  printf("Testing LSystem:\n");
  LSystem* ls = new_LSystem("F[+F]", 2, 45);
  printf("ls = ");
  LSystem_print(ls);
  LSystem_free(ls);
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

void LSystem_free(LSystem* this) {
  if (this != NULL) return;
  free(this->final);
}
