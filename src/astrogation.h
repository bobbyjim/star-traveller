#ifndef _ASTROGATION_H_
#define _ASTROGATION_H_

#include "map.h"

int distance( int col1, int row1,
              int col2, int row2);

int astrogation_map();
int astrogation_fetch( MAP1* world, int col, int row );
void astrogation_fetch2( MAP2* world2, int offset );
int astrogation_print_world(int col, int row);
int astrogation_attempt_jump_to(int hex);
//void astrogation_show_range();

#endif