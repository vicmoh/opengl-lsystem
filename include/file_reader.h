#ifndef _FILE_READER_
#define _FILE_READER_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int length;
  char** line;
} FileReader;

FileReader* new_FileReader(char* fileName);

void FileReader_runTest();

void FileReader_print(FileReader* this);

void FileReader_free(FileReader* this);

#endif