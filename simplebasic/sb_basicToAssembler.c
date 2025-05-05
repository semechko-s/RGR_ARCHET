#include "../include/simplebasic.h"

int
basicToAss (FILE *file_sb, FILE *file_sa)
{
  for (size_t i = 0; i < sizeof (asmString) / sizeof (asmString[0]); i++)
    sprintf (asmString[i], "%s", "");

  for (size_t i = 0; i < sizeof (asmStringOut) / sizeof (asmStringOut[0]); i++)
    sprintf (asmStringOut[i], "%s", "");

  for (size_t i = 0; i < sizeof (variables); i++)
    strcpy (&variables[i], "\0");

  int var_offset, strnum, asm_addr = 0, last_strnum = 0;
  int max_strnum, goto_addr, goto_line;
  char opr[6], str[100], ch;
  char line[100];
  int linenum = 1;

  do
    {
      fgets (line, sizeof (line), file_sb);
      if (feof (file_sb))
        {
          break;
        }

      if (strcmp (line, "\n") != 0)
        {

          if (sscanf (line, "%d %s", &strnum, opr) >= 2)
            {
              if (strnum <= last_strnum)
                {
                  printf ("Invalid syntax\n");
                  return -1;
                }
              if (strcmp (opr, "REM") == 0)
                {
                  linenum++;
                  continue;
                }
              else if (strcmp (opr, "END") == 0)
                {
                  if (sscanf (line, "%d %s %s", &strnum, opr, str) != 2)
                    {
                      printf ("Invalid syntax\n");
                      return -1;
                    }
                  sprintf (asmString[asm_addr], "%d %d %d %s", linenum, strnum,
                           asm_addr, "HALT\n");
                }
              else if (strcmp (opr, "INPUT") == 0)
                {
                  if (sscanf (line, "%d %s %c %s", &strnum, opr, &ch, str)
                      != 3)
                    {
                      printf ("Invalid syntax\n");
                      return -1;
                    }
                  sprintf (asmString[asm_addr], "%d %d %d %s %c%s", linenum,
                           strnum, asm_addr, "READ", ch, "\n");
                }
              else if (strcmp (opr, "LET") == 0)
                {
                  char *s = strstr (line, "LET") + 4;
                  sb_clearBackspace (s);
                  char ch1, ch2, ch3, ch4;
                  int d;
                  if (sscanf (s, "%c=%d", &ch1, &d) == 2)
                    {
                      sprintf (asmString[asm_addr], "%d %d %d %s %d%s",
                               linenum, strnum, asm_addr, "LOAD", d, "\n");
                      asm_addr++;
                      sprintf (asmString[asm_addr], "%d %d %d %s %c%s", -1, -1,
                               asm_addr, "STORE", ch1, "\n");
                      asm_addr++;
                      last_strnum = strnum;
                      linenum++;
                      continue;
                    }
                  if (sscanf (s, "%c=%c%c%c%s", &ch1, &ch2, &ch3, &ch4, str)
                      != 4)
                    {
                      printf ("Invalid syntax\n");
                      return -1;
                    }
                  sprintf (asmString[asm_addr], "%d %d %d %s %c%s", linenum,
                           strnum, asm_addr, "LOAD", ch2, "\n");
                  asm_addr++;
                  if (ch3 == '+')
                    sprintf (asmString[asm_addr], "%d %d %d %s %c%s", -1, -1,
                             asm_addr, "ADD", ch4, "\n");
                  else if (ch3 == '-')
                    sprintf (asmString[asm_addr], "%d %d %d %s %c%s", -1, -1,
                             asm_addr, "SUB", ch4, "\n");
                  else if (ch3 == '*')
                    sprintf (asmString[asm_addr], "%d %d %d %s %c%s", -1, -1,
                             asm_addr, "MUL", ch4, "\n");
                  else if (ch3 == '/')
                    sprintf (asmString[asm_addr], "%d %d %d %s %c%s", -1, -1,
                             asm_addr, "DIVIDE", ch4, "\n");
                  else
                    {
                      printf ("Invalid syntax\n");
                      return -1;
                    }
                  asm_addr++;
                  sprintf (asmString[asm_addr], "%d %d %d %s %c%s", -1, -1,
                           asm_addr, "STORE", ch1, "\n");
                }
              else if (strcmp (opr, "IF") == 0)
                {
                  char *s = strstr (line, "IF") + 2;
                  sb_clearBackspace (s);
                  char ch1, ch2, ch3;
                  if (sscanf (s, "%c%c%cGOTO%d%s", &ch1, &ch2, &ch3,
                              &goto_line, str)
                      != 4)
                    {
                      printf ("Invalid syntax\n");
                      return -1;
                    }
                  sprintf (asmString[asm_addr], "%d %d %d %s %c%s", linenum,
                           strnum, asm_addr, "LOAD", ch1, "\n");
                  asm_addr++;
                  if ((ch2 == '<') && (ch3 == '0'))
                    sprintf (asmString[asm_addr], "%d %d %d %s %d%s", -1, -1,
                             asm_addr, "JNEG", goto_line, "\n");
                  else if ((ch2 == '>') && (ch3 == '0'))
                    sprintf (asmString[asm_addr], "%d %d %d %s %d%s", -1, -1,
                             asm_addr, "JNS", goto_line, "\n");
                  else if ((ch2 == '=') && (ch3 == '0'))
                    sprintf (asmString[asm_addr], "%d %d %d %s %d%s", -1, -1,
                             asm_addr, "JZ", goto_line, "\n");
                  else
                    {
                      printf ("Invalid syntax\n");
                      return -1;
                    }
                }
              else if (strcmp (opr, "GOTO") == 0)
                {
                  if (sscanf (line, "%d %s %d %s", &strnum, opr, &goto_line,
                              str)
                      != 3)
                    {
                      printf ("Invalid syntax\n");
                      return -1;
                    }
                  sprintf (asmString[asm_addr], "%d %d %d %s %d%s", linenum,
                           strnum, asm_addr, "JUMP", goto_line, "\n");
                }
              else if (strcmp (opr, "PRINT") == 0)
                {
                  if (sscanf (line, "%d %s %c %s", &strnum, opr, &ch, str)
                      != 3)
                    {
                      printf ("Invalid syntax\n");
                      return -1;
                    }
                  sprintf (asmString[asm_addr], "%d %d %d %s %c%s", linenum,
                           strnum, asm_addr, "WRITE", ch, "\n");
                }
              else
                {
                  printf ("Invalid syntax\n");
                  return -1;
                }

              asm_addr++;
              last_strnum = strnum;
            }
          else
            {
              printf ("Invalid syntax\n");
              return -1;
            }
        }
      linenum++;
    }
  while (!feof (file_sb));
  fclose (file_sb);

  max_strnum = strnum;
  var_offset = asm_addr;

  for (int i = 0; i < sizeof (asmString) / sizeof (asmString[0]); i++)
    {
      if (strcmp (asmString[i], "") != 0)
        {
          sscanf (asmString[i], "%d %d %d %s", &linenum, &strnum, &asm_addr,
                  opr);
          if ((strcmp (opr, "READ") == 0) || (strcmp (opr, "WRITE") == 0)
              || (strcmp (opr, "LOAD") == 0) || (strcmp (opr, "STORE") == 0)
              || (strcmp (opr, "ADD") == 0) || (strcmp (opr, "SUB") == 0)
              || (strcmp (opr, "DIVIDE") == 0) || (strcmp (opr, "MUL") == 0))
            {

              sscanf (asmString[i], "%d %d %d %s %c", &linenum, &strnum,
                      &asm_addr, opr, &ch);
              int var_addr = sb_getVarAddr (ch, var_offset);
              sprintf (asmStringOut[i], "%02d %s %02d%s", asm_addr, opr,
                       var_addr, "\n");
              int d;
              if (sscanf (asmString[i], "%d %d %d %s %d", &linenum, &strnum,
                          &asm_addr, opr, &d)
                  == 5)
                {
                  if (strcmp (opr, "LOAD") == 0)
                    {
                      numArray[var_addr] = d;
                    }
                }
            }
          else if ((strcmp (opr, "JUMP") == 0) || (strcmp (opr, "JNEG") == 0)
                   || (strcmp (opr, "JNS") == 0) || (strcmp (opr, "JZ") == 0))
            {
              sscanf (asmString[i], "%d %d %d %s %d", &linenum, &strnum,
                      &asm_addr, opr, &goto_line);
              int goto_addr = sb_getGotoAddr (goto_line);
              if (goto_addr == -1)
                {
                  printf ("Invalid syntax\n");
                  return -1;
                }
              sprintf (asmStringOut[i], "%02d %s %02d%s", asm_addr, opr,
                       goto_addr, "\n");
            }
          else if (strcmp (opr, "HALT") == 0)
            {
              sscanf (asmString[i], "%d %d %d %s", &linenum, &strnum,
                      &asm_addr, opr);
              sprintf (asmStringOut[i], "%02d %s%s", asm_addr, opr, " 00\n");
            }
        }
      else
        {
          if (i >= var_offset)
            {
              if (sb_getVarName (i, var_offset) != '\0')
                sprintf (asmStringOut[i], "%02d %c %s", i, '=', "+0000\n");
              if (numArray[i] != 0)
                {
                  sprintf (asmStringOut[i], "%02d %c +%04X%s", i, '=',
                           numArray[i], "\n");
                }
            }
        }
    }

  for (int i = 0; i < sizeof (asmString) / sizeof (asmString[0]); i++)
    fwrite (asmStringOut[i], 1, strlen (asmStringOut[i]), file_sa);

  fclose (file_sa);

  return 0;
}
