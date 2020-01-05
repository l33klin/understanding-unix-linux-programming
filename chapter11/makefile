#
# Makefile for Chapter 11
#
# Type  make    to compile all the programs
# in the chapter
#
all: popen popen_ex3 popendemo rls rlsd testbdp timeclnt timeserv tinybc

.PHONY:clean
clean:
	rm -f popen popen_ex3 popendemo rls rlsd testbdp timeclnt timeserv tinybc


popen: popen.c
	gcc -o popen popen.c

popen_ex3: popen_ex3.c
	gcc -o popen_ex3 popen_ex3.c

popendemo: popendemo.c
	gcc -o popendemo popendemo.c

rls: rls.c
	gcc -o rls rls.c

rlsd: rlsd.c
	gcc -o rlsd rlsd.c

testbdp: testbdp.c
	gcc -o testbdp testbdp.c

timeclnt: timeclnt.c
	gcc -o timeclnt timeclnt.c

timeserv: timeserv.c
	gcc -o timeserv timeserv.c

tinybc: tinybc.c
	gcc -o tinybc tinybc.c
