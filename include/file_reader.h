#ifndef _FILE_READER_
#define _FILE_READER_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int length;
  char** lines;
} FileReader;

FileReader* new_FileReader(char* fileName);

void free_FileReader(FileReader* this);

int FileReader_getLength(FileReader* this);

char* FileReader_getLineAt(FileReader* this, int index);

void FileReader_runTest();

void FileReader_print(FileReader* this);

#endif