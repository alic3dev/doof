#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define charRangeMin 32
#define charRangeMax 127

#define compressionLevel 100

#define IMAGE_DIRECTORY "images"

char* images[1] = {
  "IMG_4540.HEIC"
};

unsigned short int charRangeTotal = (
    charRangeMax - charRangeMin
);

char* resolveImage(char* imageName) {
  static char* imagePath;
  imagePath = malloc(
    (
      sizeof(IMAGE_DIRECTORY) +
      sizeof(imageName) +
      1
    ) * sizeof(char)
  );

  strcpy(imagePath, IMAGE_DIRECTORY);
  strcat(imagePath, "/");
  strcat(imagePath, imageName);

  return imagePath;
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

int main() {
  char* imagePath = resolveImage(images[0]);

  FILE* inputFile = fopen(
    imagePath,
    "rb"
  );

  if (inputFile == NULL) {
    printf(
      "Failed to open file [%s]\n", 
      imagePath
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

