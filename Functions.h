#pragma once

#include "DynamicArray.h"

const char user_symbol = 'X';
const char PC_symbol = 'O';
const char empty_cell = '.';

bool is_valid_move(int& x,int& y,DynamicArray<char>& map,int N){
    return map[(x - 1) * N + (y - 1) % N] == empty_cell;
}

void user_move(int& x,int& y,DynamicArray<char>& map,int N){
    while(!is_valid_move(x,y,map,N)){
        std::cout << "Cell is FULL !\n";
        std::cin >> x >> y;
    }
    map[(x - 1) * N + (y - 1) % N] = user_symbol;
}

int is_over(DynamicArray<char>& map, char c,int N,int win_length){
    int count;

    //проверка главных диагоналей миноров размерами win_length на win_length
    for (int i = 0; i < (N - win_length + 1) * N; i += N) {
        for (int j = 0; j < N - win_length + 1; ++j) {
            count = 0;
            for (int k = 0; k < win_length; ++k) {
                if(map[i + j + (N + 1) * k] == c)
                    ++count;
            }
            if(count == win_length)
                return c;
        }
    }

    //проверка побочных диагоналей миноров размерами win_length на win_length
    for (int i = win_length - 1; i < (N - win_length + 1) * N; i += N) {
        for (int j = 0; j < N - win_length + 1; ++j) {

            count = 0;
            for (int k = 0; k < win_length; ++k) {

                if(map[i + j + (N - 1) * k] == c)
                    ++count;
            }
            if(count == win_length)
                return c;
        }
    }

    //проверка строк длины win_length
    for (int i = 0; i < map.GetSize(); i += N) {//
        for (int j = 0; j < N - win_length + 1; ++j) {
            count = 0;
            for (int k = 0; k < win_length; ++k) {
                if(map[i + j + k] == c)
                    ++count;
            }
            if(count == win_length)
                return c;
        }
    }

    //проверка столбцов длины win_length
    for (int i = 0; i < (N - win_length + 1) * N; i += N) {//
        for (int j = 0; j < N; ++j) {
            count = 0;
            for (int k = 0; k < win_length; ++k) {
                if(map[i + j + N * k] == c)
                    ++count;
            }
            if(count == win_length)
                return c;
        }
    }

    //если конец игры не наступил,то return 0
    return 0;
}


bool is_draw(DynamicArray<char>& map,int N){
    int count = 0;
    for (int i = 0; i < map.GetSize(); ++i) {
        if(map[i] != empty_cell)
            ++count;
    }
    return count == N * N;
}

void print_map(DynamicArray<char>& map,int N){
    for (int i = 0; i < map.GetSize(); ++i) {
        std::cout << map[i] << "\t";
        if((i + 1) % N == 0)
            std::cout << "\n\n";
    }
}