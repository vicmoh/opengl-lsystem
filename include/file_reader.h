#ifndef _FILE_READER_
#define _FILE_READER_

typedef struct {
  int length;
  char** line;
} FileReader;

FileReader* fr_readFile(char* fileName);

void fr_print(FileReader* fr);

void fr_close(FileReader* fr);

#endif