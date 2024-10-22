#include "file_reader.h"

FileReader* new_FileReader(char* fileName) {
  FILE* filePointer = fopen(fileName, "r");
  if (filePointer == NULL) return NULL;

  FileReader* this = malloc(sizeof(FileReader));
  this->lines = calloc(1, sizeof(char*));
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
    this->lines[lineSize] = calloc(strlen(token), sizeof(char));
    strcpy(this->lines[lineSize], token);
    lineSize++;
    this->lines = realloc(this->lines, sizeof(this->lines) * (lineSize + 1));
    token = strtok(NULL, "\r\n");
  }

  // set the size and return
  this->length = lineSize;
  free(stringBuffer);
  fclose(filePointer);
  return this;
}

void free_FileReader(FileReader* this) {
  if (this == NULL) return;
  for (int x = 0; x < this->length; x++) free(this->lines[x]);
  free(this->lines);
  free(this);
}

int FileReader_getLength(FileReader* this) {
  if (this == NULL) return 0;
  return this->length;
}

char* FileReader_getLineAt(FileReader* this, int index) {
  if (this == NULL) return NULL;
  if (index > this->length - 1) return NULL;
  if (index < 0) return NULL;
  return this->lines[index];
}

void FileReader_runTest() {
  printf("Testing FileReader:\n");
  FileReader* fr = new_FileReader("./assets/sample.txt");
  FileReader_print(fr);
  free_FileReader(fr);
}

void FileReader_print(FileReader* this) {
  for (int x = 0; x < this->length; x++) printf("%s\n", this->lines[x]);
}
