#include "gl_setup.h"

/**
 * Main function to run the progam.
 **/
int main(int argc, char** argv) {
  printf("Running...\n");
  glSetup_run(argc, argv, NULL);
  printf("Exiting...\n");
  return 0;
}
