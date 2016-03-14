/**
 * - use stat() to obtain and print file properties
 * - some members are just numbers
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

void show_stat_info(char *fname, struct stat *buf);

int main(int argc, char *argv[]) {
  struct stat info;

  if (argc > 1) {
    if (stat(argv[1], &info) != -1) {
      show_stat_info(argv[1], &info);
      return 0;
    }
  } else {
    perror(argv[1]);
  }
  return 1;
}

/**
 * display some info from stat in a name = value format
 */
void show_stat_info(char *fname, struct stat *buf) {
  printf("    mode: %o\n", buf->st_mode);
  printf("   links: %lu\n", buf->st_nlink);
  printf("    user: %d\n", buf->st_uid);
  printf("   group: %d\n", buf->st_gid);
  printf("    size: %ld\n", buf->st_size);
  printf(" modtime: %ld\n", buf->st_mtime);
  printf("    name: %s\n", fname);
}
