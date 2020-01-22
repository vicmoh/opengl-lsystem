#include <stdbool.h>
#include "file_reader.h"
#include "gl_setup.h"
#include "l-system.h"

// Run setup.
const bool _RUN_TEST = false;
const bool _RUN_OPEN_GL = true;

/**
 * Run the program.
 **/
void run(int argc, char** argv) { runOpenGL(argc, argv); }

/**
 * Function to be wrap an run.
 **/
void runTest(int argc, char** argv) {
  printf("----- TESTING -----\n");
  LSystem_runTest();
  FileReader_runTest();
  printf("-------------------\n\n");
}

/**
 * Main function to run the progam.
 **/
int main(int argc, char** argv) {
  printf("Running...\n\n");
  if (_RUN_TEST) runTest(argc, argv);
  if (_RUN_OPEN_GL) run(argc, argv);
  printf("\nExiting...\n");
  return 0;
}
