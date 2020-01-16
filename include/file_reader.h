#ifndef _FILE_READER_
#define _FILE_READER_

typedef struct {
  int length;
  char** line;
} FileReader;

fr_readFile(char* fileName);

fr_close(FileReader* fr);

#endif