#include "file_reader.h"
#include "gl_setup.h"
#include "l-system.h"

/**
 * Function to be wrap an run.
 **/
void runTest(int argc, char** argv) {
  LSystem_runTest();
  FileReader_runTest();
}

/**
 * Main function to run the progam.
 **/
int main(int argc, char** argv) {
  printf("Running...\n\n");
  runTest(argc, argv);
  printf("\nExiting...\n");
  return 0;
}
