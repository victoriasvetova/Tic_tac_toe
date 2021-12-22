#pragma once
#include "Functions.h"
#include <limits>

int minimax(DynamicArray<char>& board,int N,int win_length,int depth,int max_depth,bool AI_or_USER){
    if(depth < max_depth) {

        if (is_over(board, PC_symbol,N,win_length))
            return 1;
        if (is_over(board, user_symbol,N,win_length))
            return -1;
        if (is_draw(board,N))
            return 0;
        int best_score = std::numeric_limits<int>::min();
        if (AI_or_USER) {
            best_score = std::numeric_limits<int>::min();
            for (int i = 0; i < board.GetSize(); ++i) {
                if (board[i] == empty_cell) {
                    board[i] = PC_symbol;
                    int score = minimax(board, N,win_length,depth + 1,max_depth, false);
                    board[i] = empty_cell;
                    best_score = std::max(best_score, score);
                }
            }
        } else {
            best_score = std::numeric_limits<int>::max();
            for (int i = 0; i < board.GetSize(); ++i) {
                if (board[i] == empty_cell) {
                    board[i] = user_symbol;
                    int score = minimax(board, N,win_length,depth + 1, max_depth,true);
                    board[i] = empty_cell;
                    best_score = std::min(best_score, score);
                }
            }
        }

        return best_score;
    }else
        return 0;
}

void AI_move(DynamicArray<char>& map,int N,int win_length,int max_depth){

    int move = -1;
    int best_score = std::numeric_limits<int>::min();
    char* board_values = new char[map.GetSize()];
    for (int i = 0; i < map.GetSize(); ++i) {
        board_values[i] = map[i];
    }


    DynamicArray<char> board(board_values,map.GetSize());
    for (int i = 0; i < board.GetSize(); ++i) {
        if(board[i] == empty_cell){
            board[i] = PC_symbol;
            int score = minimax(board, N,win_length,0,max_depth,false);
            board[i] = empty_cell;
            if(score > best_score){
                best_score = score;
                move = i;
            }
        }
    }
    if(move != -1)
        map[move] = PC_symbol;

}