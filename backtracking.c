//
// Created by vitormoreira on 10/01/2020.
//

#include "sudokuX.h"

///BACKTRACKING

int solve_sudoku(SUDOKU* s)
{
    int row;
    int col;
    //se todas as celulas ja estiverem preenchidas entao o sudoku esta resolvido
    //passar por referencia porque o number_assigned vai mudar os valores da row e col
    if(number_unassigned(&row, &col, s) == 0)
        return 1;

    int i;
    //numero entre 1 e 9
    for(i=1;i<=SIZE;i++)
    {
        //se conseguimos meter i na celula ou nao
        //a celula é  matrix[row][col]
        if(is_safe(i, row, col, s))
        {
            int j=0;
            SQUARE* sq=(s->ptable+row)->psquare;
            while(j < col){
                sq=sq->E;
                j++;
            }
            sq->number = i;
            UNSOLVED--;
            //printf("%d numeros\n", sq->number);
            //printf("faltam %d numeros\n", UNSOLVED);

            //backtracking
            if(solve_sudoku(s))
                return 1;
            //se nao conseguirmos realizar a operação, volta a 0
            sq->number = 0;
            UNSOLVED++;
        }
    }
    return 0;
}

int number_unassigned(int *row, int *col, SUDOKU* s)
{
    int num_unassign = 0;
    int i,j;

    for(i=0; i<s->nlines; i++) {
        SQUARE *sq = (s->ptable + i)->psquare;
        for (j = 0; j < s->ncol; j++) {

            if(sq->number == 0){

                *row = i;
                *col = j;

                num_unassign = 1;
                return num_unassign;
            }
            sq = sq->E;
        }
    }
    return num_unassign;
}

//funçao que verifica se podemos colocar um valor numa celula ou nao

int is_safe(int n, int r, int c, SUDOKU* s)
{
    int i,j;
    SQUARE *sq = (s->ptable + r)->psquare;
    SQUARE *fsq = (s->ptable)->psquare;

    //verifica linha
    while(sq->E != NULL){
        if(sq->number == n)
            return 0;
        sq=sq->E;
    }
    /*
      for(i=0;i<s->ncol;i++)
      {
          //existe celula com o mesmo valor
          if(sq->number == n)
              return 0;
          sq=sq->E;
      }
   */

    //verifica coluna
    for(i=0;i<c;i++){
        fsq=fsq->E;
    }
    while(fsq->S!=NULL){
        if(fsq->number == n)
            return 0;
        fsq=fsq->S;
    }

    //verifica submatriz
    int row_start = (r/3)*3;
    int col_start = (c/3)*3;

    for(i=row_start; i<row_start+3; i++){
        SQUARE* sqsm=(s->ptable+i)->psquare;
        while(sqsm->column < col_start){
            sqsm = sqsm->E;
        }


        for(j=col_start; j<col_start+3; j++){
            if(sqsm->number == n)
                return 0;
            sqsm=sqsm->E;
        }
    }


    //verifica diagonal principal
    if(r == c) {
        sq = (s->ptable)->psquare;
        while(sq->SE != NULL){
            if (sq->number == n)
                return 0;
            sq = sq->SE;
        }

        /*
        for (i = 0; i < s->nlines; i++) {
            sq = (s->ptable + i)->psquare;
            while (sq->column < i) {
                sq = sq->E;
            }
            if (sq->number == n)
                return 0;
        }
         */
    }

    //verifica diagonal secundaria
    if ((r + c) == (SIZE - 1)) {

        sq = (s->ptable)->psquare;
        while(sq->E !=NULL){
            sq = sq->E;
        }
        while(sq->SO != NULL){
            if (sq->number == n)
                return 0;
            sq = sq->SO;
        }
        /*
    for (i = 0; i < SIZE; i++) {
        sq = (s->ptable+i)->psquare;
        for (j = 0; j < SIZE; j++) {

            if ((i + j) == (SIZE - 1)) {
                if (sq->number == n)
                    return 0;
            }
            sq = sq->E;

        }
    }
         */

    }
    return 1;
}