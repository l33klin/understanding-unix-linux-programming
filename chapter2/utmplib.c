/**
 * utmplib.h - function to buffer read from utmp file
 * functions are
 *   utmp_open(filename) - open file
 *     return -1 on error
 *   utmp_next()         - return pointer to next struct
 *     return NULL on eof
 *   ump_close()         - close file
 *
 * read NRECS per read and then doles them out from the buffer
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>

#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

static char utmpbuf[NRECS * UTSIZE];  // storage
static int  num_recs;                 // num stored
static int  cur_rec;                  // next to go
static int  fd_utmp = -1;             // read from

int utmp_open(char *filename) {
  fd_utmp = open(filename, O_RDONLY);
  cur_rec = num_recs = 0;
  return fd_utmp;
}

int utmp_reload() {
  int amt_read;
  amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);
  num_recs = amt_read / UTSIZE;
  cur_rec = 0;
  return num_recs;
}

struct utmp * utmp_next() {
  struct utmp *recp;
  if (fd_utmp == -1)
    return NULLUT;
  if (cur_rec == num_recs && utmp_reload() == 0)
    return NULLUT;

  recp = (struct utmp *)&utmpbuf[cur_rec * UTSIZE];
  cur_rec++;
  return recp;
}

void utmp_close() {
  if (fd_utmp != -1)
    close(fd_utmp);
}
