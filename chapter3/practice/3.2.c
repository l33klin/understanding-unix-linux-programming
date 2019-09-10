//
// Created by Klin on 2019-09-11.
//


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


#define BUFFERSIZE 4096


int main(int argc, char *argv[]) {
  char buf[BUFFERSIZE];
  int n_chars;
  if (argc == 1) {
    perror("no file to open");
  }
  int fd;
  if ((fd = open(argv[1], O_RDONLY)) == -1) {
    perror("open file error");
    exit(1);
  }
  if((n_chars = read(fd, buf, BUFFERSIZE)) > 0) {
    printf("%s", buf);
  } else {
    printf("no content found.");
  }

  close(fd);
}

