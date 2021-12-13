#include "DynamicArray.h"
#include <limits>

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


void print_map(DynamicArray<char>& map,int N){
    for (int i = 0; i < map.GetSize(); ++i) {
        std::cout << map[i] << "\t";
        if((i + 1) % N == 0)
            std::cout << "\n\n";
    }
}


int main() {
    int N;
    std::cout << "Enter size of dimension :\n";
    std::cin >> N;

    int win_length;
    std::cout << "Enter the length of the winning chain :\n";
    std::cin >> win_length;

    int max_depth;
    std::cout << "Enter the maximum depth for finding the optimal move for the computer\n"
                 "(this will make its moves dumber or smarter)\n"
                 "RECOMMENDATION: The greater the difference between the dimension and the length of the chain,\n"
                 "the more possible combinations of moves there are. Keep this in mind.\n"
                 "For example, for a 3 by 3 field, the maximum depth is 7.\n";
    std::cin >> max_depth;

    DynamicArray<char> map(N * N);
    for (int i = 0; i < map.GetSize(); ++i) {
        map[i] = empty_cell;
    }

    int x,y;
    int check_user = 0;
    int check_AI = 0;
    std::cout << "Get move with help input pair x y as a coordinates\nExample : 1 1 of 3 2\n";
    while(true){
        if(is_draw(map,N)){
            std::cout << "It's a DRAW !\n";
            break;
        }
        if(is_over(map,user_symbol,N,win_length)){
            std::cout << "You WIN !\n";
            break;
        }
        if(is_over(map,PC_symbol,N,win_length)){
            std::cout << "You LOSE !\n";
            break;
        }
        std::cin >> x >> y;
        user_move(x,y,map,N);
        AI_move(map,N,win_length,max_depth);
        print_map(map,N);

    }

    return 0;
}
