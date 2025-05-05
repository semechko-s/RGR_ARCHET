#ifndef SIMPLEBASIC
#define SIMPLEBASIC
#include "./mySimpleComputer.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

extern char variables[256];
extern char asmString[256][256];
extern char asmStringOut[256][256];
extern int numArray[256];

char sb_getVarName (int varAddr, int offset);
int sb_getGotoAddr (int gotoLine);
void sb_clearBackspace (char *str);
int sb_getVarAddr (char varName, int offset);
int sa_commandValidate (char *command);
int basicToAss (FILE *file_sb, FILE *file_sa);

#endif