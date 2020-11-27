#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>


void init_boards() {

  for (int i = 0; i < HSIZE; i ++) {
    htable[i].init = 0; //sets init to 0 for every item in htable
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

  //if the board positions correlating to the win positions are the same, then return the item in that position
  for (int i = 0; i < 8; i++) {
    if ((board[pos2idx[WINS[i][0]]] == board[pos2idx[WINS[i][1]]]) && (board[pos2idx[WINS[i][1]]] == board[pos2idx[WINS[i][2]]])) {
      return(board[pos2idx[WINS[i][0]]]);
    }
  }

  if (depth(board) == 9) { //if depth 9 then return -
    return ('-');
  }
  else {
    return ('?'); //everything else return question mark
  }

}

char turn( Board board) {
  char temp;
  if (depth(board) % 2 == 0) {  //even turns are x
    temp = 'X';
  } else {
    temp = 'O';
  }
  if (depth(board) == 9) { //if depth 9 then return -
    temp = '-';
  }
  return(temp);
}

void init_board( Board board) {
  int hash = 0;
  hash = board_hash(board);
  //do all the init stuff
  htable[hash].init = 1;
  htable[hash].turn = turn(board);
  htable[hash].depth = depth(board);
  strcpy(htable[hash].board, board);
  htable[hash].winner = winner(board);

}


void join_graph( Board board ) {
  int hash = 0;
  hash = board_hash(board);
  if (htable[hash].winner == '?') { //if the table isnt already completetd
    for (int i = 0; i < 9; i++) { //loop for size of move
      if (board[pos2idx[i]] == 'X' || board[pos2idx[i]] == 'O') { //if already taken
        htable[hash].move[i] = -1;
      } else {
        Board newBoard;
        strcpy(newBoard,board); //create a new copy of the board
        newBoard[pos2idx[i]] = turn(newBoard); //place a move based on the turn
        int newHash = 0;
        newHash = board_hash(newBoard); //get the hash of the new board
        htable[hash].move[i] = newHash; //place that hash in the move of the old board
        if (htable[newHash].init == 0) { //if its not arleady been made
          init_board(newBoard);
          join_graph(newBoard);
        }
      }
    }
  } else {
      for (int i = 0; i < 9; i++) {
        htable[hash].move[i] = -1; //invald board, set all moves to -1
      }
  }

}

void compute_score() {
  //not completed
  for(int i = 0; i < HSIZE; i++) {
    if (htable[i].init == 1) {

    }
  }

}

int best_move( int board ) {
  //not completed
  return(0);
}
