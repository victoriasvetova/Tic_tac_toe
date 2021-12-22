#include "AI_MOVE_GAME.h"

void TestALL(){//тестирование функций проверок на окончание игры для частного случая - поле 4 на 4
    //длина победной цепочки - 3
    int N = 4;
    int win_l = 3;

    DynamicArray<char> map(N * N);


    {//проверка поиска цепочек на главных диагоналях миноров
        for (int i = 0; i < map.GetSize(); ++i) {
            map[i] = empty_cell;
        }
        map[5] = user_symbol;
        map[10] = user_symbol;
        map[15] = user_symbol;
        if(!is_over(map,user_symbol,N,win_l)){
            std::cerr << "Incorrect work !(CASE 1)";
            std::exit(0);
        }
    }

    {//проверка поиска цепочек на побочных диагоналях миноров
        for (int i = 0; i < map.GetSize(); ++i) {
            map[i] = empty_cell;
        }
        map[6] = user_symbol;
        map[9] = user_symbol;
        map[12] = user_symbol;
        if(!is_over(map,user_symbol,N,win_l)){
            std::cerr << "Incorrect work !(CASE 2)";
            std::exit(0);
        }
    }

    {//проверка поиска цепочек на горизонтали
        for (int i = 0; i < map.GetSize(); ++i) {
            map[i] = empty_cell;
        }
        map[9] = user_symbol;
        map[10] = user_symbol;
        map[11] = user_symbol;
        if(!is_over(map,user_symbol,N,win_l)){
            std::cerr << "Incorrect work !(CASE 3)";
            std::exit(0);
        }
    }

    {//проверка поиска цепочек на вертикали
        for (int i = 0; i < map.GetSize(); ++i) {
            map[i] = empty_cell;
        }
        map[6] = user_symbol;
        map[10] = user_symbol;
        map[14] = user_symbol;
        if(!is_over(map,user_symbol,N,win_l)){
            std::cerr << "Incorrect work !(CASE 3)";
            std::exit(0);
        }
    }
    //проверка функций проверок победы или ничьей не требуется,
    //поскольку их корректная работа обеспечивается вышеуказанными проверками

    std::cerr << "ALL TESTS OK !\n";
}