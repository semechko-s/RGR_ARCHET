#ifndef SIMPLEASSEMBLER
#define SIMPLEASSEMBLER
#include "./mySimpleComputer.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int sa_commandValidate (char *command);
int sa_memorySet (int addr, int value);

#endif