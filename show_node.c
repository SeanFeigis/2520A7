#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {


  init_boards();
  init_board(START_BOARD);
  join_graph(START_BOARD);

  for (int i = 1; i < argc; i ++) {
    print_node(htable[atoi(argv[i])]);
  }

  return(0);
}
