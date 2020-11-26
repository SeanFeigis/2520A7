#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>


void init_boards() {

  for (int i = 0; i < HSIZE; i ++) {
    htable[i].init = 0;
  }

}

int depth( Board board ) {
  int depth = 0;
  for (int i = 0; i < 9; i++) {
    if (board[pos2idx[i]] == 'X' || board[pos2idx[i]] == 'O') {
      depth++;
    }
  }
  /*if (depth > 7) {
    printf("DEPTH: %d\n", depth);
  }*/
  return depth;
}

char winner( Board board) {

  for (int i = 0; i < 8; i++) {
    if ((board[pos2idx[WINS[i][0]]] == board[pos2idx[WINS[i][1]]]) && (board[pos2idx[WINS[i][1]]] == board[pos2idx[WINS[i][2]]])) {
      return(board[pos2idx[WINS[i][0]]]);
    }
  }

  if (depth(board) == 9) {
    return '-';
  }
  else {
    return '?';
  }

}

char turn( Board board) {
  char temp;
  if (depth(board) % 2 == 0) {
    temp = 'X';
  } else {
    temp = 'O';
  }
  if (depth(board) == 9) {
    temp = '-';
  }
  return(temp);
}

void init_board( Board board) {
  int hash = 0;
  hash = board_hash(board);

  htable[hash].init = 1;
  htable[hash].turn = turn(board);
  htable[hash].depth = depth(board);
  strcpy(htable[hash].board, board);
  htable[hash].winner = winner(board);

}


void join_graph( Board board ) {
  int hash = 0;
  hash = board_hash(board);
  if (htable[hash].winner == '?') {
    for (int i = 0; i < 9; i++) {
      if (board[pos2idx[i]] == 'X' || board[pos2idx[i]] == 'O') {
        htable[hash].move[i] = -1;
      } else {
        Board newBoard;
        strcpy(newBoard,board);
        newBoard[pos2idx[i]] = turn(newBoard);
        int newHash = 0;
        newHash = board_hash(newBoard);
        htable[hash].move[i] = newHash;
        if (htable[newHash].init == 0) {
          init_board(newBoard);
          join_graph(newBoard);
        }
      }
    }
  } else {
      for (int i = 0; i < 9; i++) {
        htable[hash].move[i] = -1;
      }
  }

}

void compute_score() {

  for(int i = 0; i < HSIZE; i++) {
    if (htable[i].init == 1) {

    }
  }

}

int best_move( int board ) {

  return(0);
}
