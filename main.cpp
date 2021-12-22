#include "TESTS.h"
#include "AI_MOVE_GAME.h"

int main() {

    TestALL();

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
