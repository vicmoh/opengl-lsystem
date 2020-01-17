#include "file_reader.h"

FileReader* new_FileReader(char* fileName) {
  FileReader* this = malloc(sizeof(FileReader));
  FILE* filePointer = fopen(fileName, "r");
  this->line = calloc(1, sizeof(char*));
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
    this->line[lineSize] = calloc(strlen(token), sizeof(char));
    strcpy(this->line[lineSize], token);
    lineSize++;
    this->line = realloc(this->line, sizeof(this->line) * (lineSize + 1));
    token = strtok(NULL, "\r\n");
  }

  // set the size and return
  this->length = lineSize;
  free(stringBuffer);
  fclose(filePointer);
  return this;
}

void FileReader_runTest() {
  printf("Testing FileReader:\n");
  FileReader* fr = new_FileReader("./assets/sample.txt");
  FileReader_print(fr);
  FileReader_free(fr);
}

void FileReader_print(FileReader* this) {
  for (int x = 0; x < this->length; x++) printf("%s\n", this->line[x]);
}

void FileReader_free(FileReader* this) {
  if (this == NULL) return;
  for (int x = 0; x < this->length; x++) free(this->line[x]);
  free(this->line);
  free(this);
}
