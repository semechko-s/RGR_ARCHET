#ifndef SIMPLE_COMPUTER_H
#define SIMPLE_COMPUTER_H

#include "./myTerm.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define SIZE 128

#define FLAG_OVERFLOW_OPERATION 1
#define FLAG_DIVIDE_BY_ZERO 2
#define FLAG_OVERSTEP_MEMORY 3
#define FLAG_CLOCK_PULSE 4
#define FLAG_INVALID_COMMAND 5

#define CACHE_SIZE 5
#define CACHE_LINE_SIZE 10

typedef struct
{
  int addr;
  int data[CACHE_LINE_SIZE];
  int lastAT;
} CacheLine;

extern int memory[SIZE];
extern int accumulator;
extern int flags;
extern int ticks;
extern int icounter;
extern bool updateStatic;
extern CacheLine *cache;

int sc_memoryInit ();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);

int sc_regInit ();
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int *value);

int sc_accumulatorInit ();
int sc_accumulatorSet (int value);
int sc_accumulatorGet (int *value);

int sc_icounterInit ();
int sc_icounterSet (int value);
int sc_icounterGet (int *value);

int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandValidate (int command);

void sc_printTerm (int address, int input);
void sc_printAccumulator (void);
void sc_printCell (int address, enum Colors fg, enum Colors bg);
void sc_printCommand (int value, int x, int y);
void sc_printCounters (int x, int y);
void sc_printDecodedCommand (int value, int x, int y);
void sc_printFlags (int x, int y);

int sc_RecentlyUsedCache ();
void sc_updateCacheAfterSave (int memAddr, int cacheLine, int *value);

#endif // !SIMPLE_COMPUTER_H