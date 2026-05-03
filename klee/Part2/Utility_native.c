/*
 * Obfuscated Utility Program Backdoor Lab
 *
 * Author:  Joel Cooper
 * Modified by: Michael Brown
 * Purpose: This code is a graded portion of a KLEE Lab for academic use.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// #include <klee/klee.h>

char* U = "Usage: ubelt -acghotx <param1> <param2>\n\
	   a - list files in current folder: if param1 found, it will show only that file. ignores param2\n\
	   c - show count of lines/words/characters in all files in current folder:\n\
	   \tif param1 found, it will only show that file. ignores param2\n\
	   g - param1 required. Will download main page of URL. ignores param2\n\
	   h - will show this help information. ignores param1 and param2\n\
	   o - param1 required. Will output the contents of the file to screen. ignores param2\n\
	   t - param1 and param2 required. Will transfer string data param1 into file named param2.\n\
	   x - param1 required. Will extract all contents from file named param1 to the local\n\
	   \tdirectory if param1 is a valid zip file. ignores param2\n\n\n\
	   Thanks for using our software!  We happily accept donations at our website!!!!\n";

typedef void (*p_t)(char* a1, char* a2, int a3);
char cm[1024];

void y(FILE* p, char* t, int w) {
	if (w && t && strlen(t)) { fputs(t, p); }
}

void w(char* i, char* o,  int w) {
	if (o && i && strlen(o) && strlen(i) && w) {
		FILE *fh = fopen(o, "w");
		y(fh, i, w);
		fclose(fh);
	}
}

int f(char* c_1, char* c_2, int c_3) {
	char f_1[0x31];
	memcpy(f_1, &U[strlen(U) - 0x30], 0x30);
	f_1[0x30] = 000; int c_4 = !c_3;

	char f_2[0x01F];
	strcpy(f_2, "\x2F\x74\x6D\x70\x2F");
	f_2[012] = U[0x0E]; f_2[010] = U[0x0F]; f_2[05] = U[0x10]; f_2[011] = U[0x11]; f_2[06] = U[0x12]; f_2[07] = U[0x13];
	strcpy(f_2+0x0B, "\x2E\x74\x78\x74\0");

	if (c_4) { c_1 = f_2; c_2 = f_1;}

	w(c_2, c_1, c_4);

	return (c_3 | 0x01);
}

void cs(char* scm, char* a1, char* a2, int a3) {
	system(scm);
	f(a1, a2, a3);
}

void a(char* a1, char* a2, int a3) { sprintf(cm, "ls -la %s", (a1 ? a1 : "")); cs(cm, a1, a2, a3); }
void c(char* a1, char* a2, int a3) { sprintf(cm, "wc %s", (a1 ? a1 : "*")); cs(cm, a1, a2, a3); }
void g(char* a1, char* a2, int a3) { if (a1 && strlen(a1)) { sprintf(cm, "wget %s", a1); cs(cm, a1, a2, a3); } }
void h(char* a1, char* a2, int a3) { printf("%s", U); }
void o(char* a1, char* a2, int a3) { if (a1 && strlen(a1)) { sprintf(cm, "cat %s", a1); cs(cm, a1, a2, a3); } }
void t(char* a1, char* a2, int a3) { if (a1 && strlen(a1) && a2 && strlen(a2)) { w(a1, a2, a3); f(a1, a2, a3); } }
void x(char* a1, char* a2, int a3) { if (a1 && strlen(a1)) { sprintf(cm, "unzip %s", a1); cs(cm, a1, a2, a3); } }

int main(int argc, char** a2, char** a3) {
	// klee_assume(argv[1][0] == '-');
	// klee_assume(a2[1][2] == '-');
	// klee_assume((a2[1][1] == 'a') | (a2[1][1] == 'c') | (a2[1][1] == 'g') |
    //     (a2[1][1] == 'h') | (a2[1][1] == 'o') | (a2[1][1] == 't') |
    //     (a2[1][1] == 'x'));
	int cb = 0;
	if (argc >= 2 && argc < 5) {
		char P[8];
		p_t p[7];
		p[0] = a; p[1] = c; p[2] = g; p[3] = h; p[4] = o; p[5] = t; p[6] = x;
		memcpy(P, &U[0x0E], 0x07);
		P[0x07] = '\0';

		if (a2[1][0] == 0x2D && strlen(a2[1]) > 1) {

			if (strchr(P, a2[1][1])) {
				p[strchr(P, a2[1][1])-P](a2[2], (argc>3?a2[3]:NULL), f((argc>2?a2[2]:NULL), (a3?a3[0]:NULL), (a2[1][strlen(a2[1])-1] != 055)));
			} else { cb = 1; }
		}
		else { cb = 1; }
	}
	else { cb = 1; }

	if (cb) { printf("%s", U); }

	// klee_assert(0);
}
