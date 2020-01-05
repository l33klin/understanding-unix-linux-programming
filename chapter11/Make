#
# Makefile for Chapter 11
#
# Type  make    to compile all the programs
# in the chapter
#
all: popen popen_ex3 popendemo rls rlsd testbdp timeclnt timeserv tinybc

clean:
	rm -f popen popen_ex3 popendemo rls rlsd testbdp timeclnt timeserv tinybc


popen: popen.c
	gcc -o popen.o popen.c

popen_ex3: popen_ex3.c
	gcc -o popen_ex3.o popen_ex3.c

popendemo: popendemo.c
	gcc -o popendemo.o popendemo.c

rls: rls.c
	gcc -o rls.o rls.c

rlsd: rlsd.c
	gcc -o rlsd.o rlsd.c

testbdp: testbdp.c
	gcc -o testbdp.o testbdp.c

timeclnt: timeclnt.c
	gcc -o timeclnt.o timeclnt.c

timeserv: timeserv.c
	gcc -o timeserv.o timeserv.c

tinybc: tinybc.c
	gcc -o tinybc.o tinybc.c
