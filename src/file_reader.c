#include "file_reader.h"

FileReader* fr_readFile(char* fileName) {
  FileReader* fr = malloc(sizeof(FileReader));
  // dec vars
  FILE* filePointer = fopen(fileName, "r");
  fr->line = calloc(1, sizeof(char*));
  char* stringBuffer = calloc(1, sizeof(char));
  int charBuffer;
  int stringSize = 0;
  int lineSize = 0;

  // read the entire file to the string
  while (true) {
    charBuffer = getc(filePointer);
    if (charBuffer == EOF) {
      break;
    }  // end if
    stringBuffer[stringSize] = (char)charBuffer;
    stringSize++;
    stringBuffer =
        realloc(stringBuffer, sizeof(stringBuffer) * (stringSize + 1));
    stringBuffer[stringSize] = '\0';
  }

  // remove the \r\n by tokenizing and adding to array
  char* token = strtok(stringBuffer, "\r\n");
  while (token != NULL) {
    fr->line[lineSize] = calloc(strlen(token), sizeof(char));
    strcpy(fr->line[lineSize], token);
    lineSize++;
    fr->line = realloc(fr->line, sizeof(fr->line) * (lineSize + 1));
    token = strtok(NULL, "\r\n");
  }

  // set the size and return
  fr->length = lineSize;
  free(stringBuffer);
  fclose(filePointer);
  return fr;
}

void fr_print(FileReader* fr) {
  for (int x = 0; x < fr->length; x++) printf("%s\n", fr->line[x]);
}

void fr_close(FileReader* fr) {
  if (fr == NULL) return;
  for (int x = 0; x < fr->length; x++) free(fr->line[x]);
  free(fr->line);
  free(fr);
}
