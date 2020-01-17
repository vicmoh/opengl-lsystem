#include "file_reader.h"
#include "gl_setup.h"
#include "l-system.h"

/**
 * Main function to run the progam.
 **/
int main(int argc, char** argv) {
  printf("Running...\n");
  // glSetup_run(argc, argv, NULL);
  LSystem* ls = new_LSystem("F[+F]", 3, 45);
  LSystem_print(ls);
  LSystem_free(ls);
  printf("Exiting...\n");
  return 0;
}
