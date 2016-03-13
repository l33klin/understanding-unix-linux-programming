/**
 * starts in current directory and recursively
 * climbs to the root of filesystem, prints top part
 * then prints current part
 * - use readdir() to get info about each thing
 * - bug: prints an empty string if run from "/"
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

ino_t get_inode(char *);
void print_path_to(ino_t);
void inum_to_name(ino_t, char *, int);

int main() {
  print_path_to(get_inode("."));
  putchar('\n');
  return 0;
}

/**
 * print path leading down to an object with this node
 * kindof recursive
 */
void print_path_to(ino_t this_inode) {
  ino_t my_inode;
  char its_name[BUFSIZ];
  if (get_inode("..") != this_inode) {
    printf("here\n");
    chdir("..");
    inum_to_name(this_inode, its_name, BUFSIZ);
    my_inode = get_inode(".");
    print_path_to(my_inode);
    printf("/%s", its_name);
  }
}

/**
 * looks through current directory for a file with this node
 * number and copies its name into namebuf
 */
void inum_to_name(ino_t inode_to_find, char *namebuf, int buflen) {
  DIR *dir_ptr;
  struct dirent * direntp;
  dir_ptr = opendir(".");
  if (dir_ptr) {
    perror(".");
    exit(1);
  }

  while ((direntp = readdir(dir_ptr))) {
    if (direntp->d_ino == inode_to_find) {
      strncpy(namebuf, direntp->d_name, buflen);
      namebuf[buflen-1] = '\0';
      closedir(dir_ptr);
      return;
    }
  }

  fprintf(stderr, "error looking for inum %lu\n", inode_to_find);
  exit(1);
}

/**
 * return inode number of the file
 */
ino_t get_inode(char *fname) {
  struct stat info;
  if (stat(fname, &info) == -1) {
    fprintf(stderr, "Cannot stat");
    perror(fname);
    exit(1);
  }
  return info.st_ino;
}
