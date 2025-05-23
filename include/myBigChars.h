#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#include <stdio.h>

#define bc_cornerUpLeft 'l'
#define bc_cornerDownLeft 'm'
#define bc_cornerUpRight 'k'
#define bc_cornerDownRight 'j'
#define bc_horizontaleLine 'q'
#define bc_verticalLine 'x'
#define bc_shadedCell 'a'

#define bc_Null(x) (x == 0) ? 1717992960 : 8283750
#define bc_One(x) (x == 0) ? 471341056 : 3938328
#define bc_Two(x) (x == 0) ? 538983424 : 3935292
#define bc_Three(x) (x == 0) ? 2120252928 : 8282238
#define bc_Four(x) (x == 0) ? 2120640000 : 6316158
#define bc_Five(x) (x == 0) ? 2114092544 : 8273984
#define bc_Six(x) (x == 0) ? 33701376 : 8274558
#define bc_Seven(x) (x == 0) ? 811630080 : 396312
#define bc_Eight(x) (x == 0) ? 2120646144 : 8283750
#define bc_Nine(x) (x == 0) ? 2120646144 : 8282208
#define bc_A(x) (x == 0) ? 1715214336 : 6710910
#define bc_B(x) (x == 0) ? 1044528640 : 4080194
#define bc_C(x) (x == 0) ? 37912064 : 8274434
#define bc_D(x) (x == 0) ? 1111637504 : 4080194
#define bc_E(x) (x == 0) ? 2114092544 : 8258050
#define bc_F(x) (x == 0) ? 101088768 : 394878
#define bc_I(x) (x == 0) ? 410942976 : 8289816
#define bc_L(x) (x == 0) ? 101058048 : 8289798
#define bc_X(x) (x == 0) ? 406611456 : 6700056
#define bc_Plus(x) (x == 0) ? 2115508224 : 1579134
#define bc_Minus(x) (x == 0) ? 2113929216 : 126

int bc_printA (char *str);
int bc_strlen (char *str);
// int bc_box (int x1, int y1, int x2, int y2);
int bc_box (int x1, int y1, int x2, int y2, enum Colors box_fg,
            enum Colors box_bg, char *header, enum Colors header_fg,
            enum Colors header_bg);
int bc_printbigchar (int a[2], int x, int y, enum Colors, enum Colors);
int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos (int *big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int *big, int count);
int bc_bigcharread (int fd, int *big, int need_count, int *count);
