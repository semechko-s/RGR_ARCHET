#include "../include/simplebasic.h"

int
sa_commandValidate (char *command)
{
  if (strcmp (command, "NOP") == 0)
    return 0x00;
  if (strcmp (command, "CPUINFO") == 0)
    return 0x1;
  if (strcmp (command, "READ") == 0)
    return 0xA;
  if (strcmp (command, "WRITE") == 0)
    return 0xB;
  if (strcmp (command, "LOAD") == 0)
    return 0x14;
  if (strcmp (command, "STORE") == 0)
    return 0x15;
  if (strcmp (command, "ADD") == 0)
    return 0x1E;
  if (strcmp (command, "SUB") == 0)
    return 0x1F;
  if (strcmp (command, "DIVIDE") == 0)
    return 0x20;
  if (strcmp (command, "MUL") == 0)
    return 0x21;
  if (strcmp (command, "JUMP") == 0)
    return 0x28;
  if (strcmp (command, "JNEG") == 0)
    return 0x29;
  if (strcmp (command, "JZ") == 0)
    return 0x2A;
  if (strcmp (command, "HALT") == 0)
    return 0x2B;
  if (strcmp (command, "JNS") == 0)
    return 0x37;
  if (strcmp (command, "JP") == 0)
    return 0x3A;
  if (strcmp (command, "SUBC") == 0)
    return 0x42;
  if (command[0] == '=')
    return 1;
  return -1;
}
