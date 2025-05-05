#ifndef MYREADKEY_H
#define MYREADKEY_H
#include <myBigChars.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

// F5     F6     UP   DOWN LEFT RIGHT
// \E[15~ \E[17~ \E[A \E[B \E[D \E[C

enum keys
{
  F5 = 10,
  F6,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  OTHER,
  MINUS,
  PLUS,
  ESC,
  ENTER
};

enum way
{
  way_UP,
  way_DOWN,
  way_LEFT,
  way_RIGHT,
  way_DEFAULT
};

int rk_readkey (enum keys *key);
int rk_mytermsave ();
int rk_mytermrestore ();
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_readValue (int *value, int timeout);

#endif