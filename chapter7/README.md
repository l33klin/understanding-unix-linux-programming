# Troubleshoot

## 1. error `clang: error: linker command failed with exit code 1 ` when
 build with <curses.h> by using gcc.
Use `-l` to link ncurses library like below:
```bash
$ gcc -o hello1.o hello1.c -lncurses
```
REF: [Problems with curses.h on OSX Lion](https://stackoverflow.com/questions/11029293/problems-with-curses-h-on-osx-lion)

