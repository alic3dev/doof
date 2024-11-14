#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define charRangeMin 32
#define charRangeMax 127

#define compressionLevel 100

unsigned short int charRangeTotal = (
    charRangeMax - charRangeMin
    );

char* resolveFile(char* fileName);
char getCharVal(
    unsigned short int* bufferArr,
    size_t length
    );
void printUsage();

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Invalid number of arguments\n");
    printUsage();
    return 1;
  }

  char* filePath = resolveFile(argv[1]);

  FILE* inputFile = fopen(
      filePath,
      "rb"
      );

  if (inputFile == NULL) {
    printf(
        "Failed to open file [%s]\n", 
        filePath
        );

    return 1;
  }

  unsigned short int buffer;
  unsigned short int bufferArr[compressionLevel];
  size_t bufferPos = 0;

  while (!feof(inputFile)) {
    fread(
        &buffer,
        sizeof(buffer),
        1,
        inputFile
        );

    bufferArr[bufferPos] = buffer;
    bufferPos = bufferPos + 1;

    if (bufferPos == compressionLevel) {
      char val = getCharVal(
          bufferArr,
          compressionLevel
          );

      printf("%c", val);

      bufferPos = 0;
    }
  }

  if (bufferPos != 0) {
    char val = getCharVal(
        bufferArr,
        bufferPos
        );

    printf("%c", val);
  }

  printf("\n");

  fclose(inputFile);

  return 0;
}

char* resolveFile(char* fileName) {
  static char* filePath;
  filePath = malloc(
      sizeof(fileName) * sizeof(char)
      );

  strcat(filePath, fileName);

  return filePath;
}

char getCharVal(
    unsigned short int* bufferArr,
    size_t length
    ) {
  unsigned long long int res = 0;

  for (size_t i = 0; i < length; i++) {
    res = res + bufferArr[i];
  }

  char val = (char)(
      (res % charRangeTotal) +
      charRangeMin
      );

  return val;
}

void printUsage() {
  printf("USAGE: doof \"filepath\"\n");
}

