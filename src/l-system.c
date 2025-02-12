#include "l-system.h"

char* LSystem_globalFileName = NULL;

char* _LSystem_recurse(LSystem* this, int depth) {
  const bool SHOW_PRINT = false;
  if (SHOW_PRINT) printf("------------------------------------------------\n");
  depth++;
  if (SHOW_PRINT) printf("Goal depth: %d, depth: %d.\n", this->depth, depth);
  char* toBeReturned = strdup("");

  for (int x = 0; x < strlen(this->original); x++) {
    if (SHOW_PRINT) printf("Char: %c\n", this->original[x]);
    if (this->original[x] == 'F') {
      if (depth >= this->depth) {
        toBeReturned = realloc(
            toBeReturned,
            sizeof(char) * (strlen(toBeReturned) + strlen(this->original)) + 4);
        sprintf(toBeReturned, "%sF%s", toBeReturned, this->original);
      } else {
        char* temp = _LSystem_recurse(this, depth);
        toBeReturned =
            realloc(toBeReturned,
                    sizeof(char) * (strlen(toBeReturned) + strlen(temp)) + 4);
        sprintf(toBeReturned, "%sF%s", toBeReturned, temp);
      }
    } else {
      toBeReturned = realloc(
          toBeReturned,
          sizeof(char) * (strlen(toBeReturned) + strlen(this->original)) + 4);
      sprintf(toBeReturned, "%s%c", toBeReturned, this->original[x]);
    }
    if (SHOW_PRINT) printf("debug: %s\n", toBeReturned);
  }

  if (SHOW_PRINT) printf("String: %s\n", toBeReturned);
  return toBeReturned;
}

LSystem* new_LSystem(char* start, int depth, double angle) {
  const bool SHOW_DEBUG = true;
  if (start == NULL) return NULL;
  const int MAX_MEM = 256 * 8;
  if (MAX_MEM < strlen(start)) {
    printf("new_LSystem(): MEMORY_EXCEEDED!");
    return NULL;
  }

  // Initialize
  LSystem* new = malloc(sizeof(LSystem));
  new->depth = depth;
  new->angle = angle;
  new->final = calloc(MAX_MEM, sizeof(char));
  new->original = calloc(MAX_MEM, sizeof(char));
  strcpy(new->original, start);
  strcpy(new->final, start);

  if (SHOW_DEBUG) {
    printf("-----Input-----\n");
    printf("Start: %s.\n", start);
    printf("Depth: %d.\n", depth);
    printf("Angle: %f.\n", angle);
    printf("---------------\n");
  }

  new->final = _LSystem_recurse(new, 1);
  if (SHOW_DEBUG) printf("L-System string: %s\n", new->final);
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

void LSystem_print(LSystem* this) {
  printf("{depth: %d, original: %s, final: %s}\n", this->depth, this->original,
         this->final);
}

void _LSystem_drawBasedOnCondition(char* start, double angle) {
  const bool SHOW_DEBUG = false;
  char* final = strdup(start);
  if (SHOW_DEBUG) printf("Drawing: %s\n", final);
  glPushMatrix();
  for (int x = 0; x < strlen(final); x++) {
    char curState = final[x];
    if (curState == 'F') {
      if (SHOW_DEBUG) printf("Draw solid sphere.\n");
      glTranslatef(0, 2, 0);
      glutSolidSphere(1, 15, 15);
    } else if (curState == '+') {
      if (SHOW_DEBUG)
        printf("Rotate z axis by %f degrees to the right.\n", angle);
      glRotatef(-angle, 0, 0, -7);
    } else if (curState == '-') {
      if (SHOW_DEBUG)
        printf("Rotate z axis by %f degrees to the left.\n", angle);
      glRotatef(angle, 0, 0, -7);
    } else if (curState == '[') {
      if (SHOW_DEBUG) printf("Push matrix.\n");
      glPushMatrix();
    } else if (curState == ']') {
      if (SHOW_DEBUG) printf("Pop matrix.\n");
      glPopMatrix();
    }
  }
  glPopMatrix();
  free(final);
}

void LSystem_freeGlobalFileName() {
  if (LSystem_globalFileName != NULL) free(LSystem_globalFileName);
}

void LSystem_setGlobalFileName(char* fileName) {
  if (fileName == NULL) return;
  LSystem_globalFileName = calloc(strlen(fileName) + 4, sizeof(char));
  strcpy(LSystem_globalFileName, fileName);
}

void LSystem_draw() {
  if (LSystem_globalFileName == NULL) return;
  printf("\n\n\n\n\n\n\n\n\n\nFile: %s\n", LSystem_globalFileName);
  FileReader* fr = new_FileReader(LSystem_globalFileName);
  if (fr == NULL) {
    printf("Could not find the file. Please re-enter the file.\n");
    return;
  }
  LSystem* ls = new_LSystem(FileReader_getLineAt(fr, 2),
                            atoi(FileReader_getLineAt(fr, 0)),
                            atof(FileReader_getLineAt(fr, 1)));
  /* set starting location of objects */
  _LSystem_drawBasedOnCondition(ls->final, ls->angle);
  // Free
  free_LSystem(ls);
}
