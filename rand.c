#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int genRand() {
  int dev = open("/dev/random", O_RDONLY);
  if (dev < 0) {
    printf("Error: %s\n", strerror(errno));
    return -1;
  }
  
  int num;
  int reading = read(dev, &num,sizeof(num));
  if (reading < sizeof(num)) {
    printf("Error: %s\n", strerror(errno));
    return -1;
  }
  
  close(dev);
  return abs(num);
  
}

int main() {

  int * nums = calloc(10, sizeof(int));

  printf("Generating rand numbers \n");
  for (int i = 0; i < 10; i++) {
    int random = genRand();
    printf("Random at %d: %d\n", i, random);
    nums[i] = random;
  }

  printf("Writing numbers to outfile: \n");
  int words = open("out.txt", O_WRONLY);
  if (words < 0) {
    printf("Error: %s\n", strerror(errno));
  }
  else {
    write(words, nums, 10 *sizeof(int));
  }

  printf("Opening file for reading: \n");
  int * intake = calloc(10, sizeof(int));
  int reading = open("out.txt", O_RDONLY);
  if (reading < 0) {
    printf("Error: %s\n", strerror(errno));
  }
  else {
    read(reading, intake, 10 * sizeof(int));
  }

  printf("Checking that values are the same: \n");
  for (int i = 0; i < 10; i++) {
    if (nums[i] == intake[i]) {
      printf("Random val at %d: %d \n", i, intake[i]);
    }
    else {
      printf("Value was not equal\n");
    }
  }

  return 0;
}
