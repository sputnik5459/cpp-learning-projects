#include <iostream>


void print_game_map(int game_map[9][9]) {
    // TODO: beautify
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            std::cout << game_map[row][col];
            if (col == 2 || col == 5) std::cout << "|";
        }
        if (row == 2 || row == 5) std::cout << "\n-----------" << std::endl;
        else std::cout << "\n";
    }
}

int main() {
    // TODO: make sudoku maps reading from files
    int game_map[9][9] = {
            {0, 3, 0, 6, 0, 5, 9, 0, 0},
            {0, 9, 8, 0, 3, 4, 2, 0, 0},
            {7, 0, 0, 0, 0, 0, 0, 5, 0},
            //---------------------------
            {6, 8, 0, 0, 9, 0, 4, 0, 0},
            {0, 0, 7, 5, 0, 0, 3, 9, 0},
            {0, 0, 5, 3, 0, 0, 0, 0, 8},
            //---------------------------
            {0, 0, 0, 9, 2, 6, 0, 0, 4},
            {3, 4, 9, 0, 0, 1, 6, 7, 2},
            {0, 5, 6, 0, 7, 3, 0, 8, 0}
    };
    print_game_map(game_map);
    return 0;
}