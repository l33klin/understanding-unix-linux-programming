#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFERSIZE 20
#define MODE 0664

int main() {
  int fd1_count;
  int fd2_count;
  int fd3_count;
  char buf1[BUFFERSIZE];
  char buf3[BUFFERSIZE];

  const char file_path[] = "./test";
  int in_fd;

  if ((in_fd = creat(file_path, MODE)) == -1) {
    perror("Cannot create test file");
    exit(1);
  }

  // operation1
  if ((fd1_count = read(in_fd, buf1, BUFFERSIZE)) == -1) {
    perror("fail to read in 1");
  }
  printf("%s in 1\n", buf1);

  // operation2
  if ((fd2_count = write(in_fd, "testing...", BUFFERSIZE)) == -1) {
    perror("fail to write in 2");
  }

  // operation3
  if ((fd3_count = read(in_fd, buf3, BUFFERSIZE)) == -1) {
    perror("Cannot open in 3");
  }
  printf("%s in 3\n", buf3);

  return 0;
}
