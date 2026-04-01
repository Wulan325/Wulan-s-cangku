#include "Minesweeper.h"
#include <iostream>
#include <string>

// 主游戏循环
void Minesweeper::playGame() {
    initializeGame();
    std::cout << "Welcome to Minesweeper!" << std::endl;
    std::cout << "Input format: row col (for example: 3 4)" << std::endl;
    std::cout << "Input -1 -1 to quit the game" << std::endl;
    std::cout << std::endl;

    while (!gameOver) {
        displayBoardFunc();
        std::cout << std::endl;

        int row, col;
        std::cout << "Please enter the grid coordinates to reveal: ";
        
        if (!(std::cin >> row >> col)) {
            std::cout << "Input error, please re-enter!" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (row == -1 && col == -1) {
            std::cout << "Game exit!" << std::endl;
            break;
        }

        if (makeMove(row, col)) {
            if (gameOver) {
                if (gameWon) {
                    std::cout << "Congratulations, you won!" << std::endl;
                } else {
                    std::cout << "Game over! You stepped on a mine." << std::endl;
                    displayBoardFunc(true);  // 显示所有地雷
                }
                break;
            } else if (checkWin()) {
                std::cout << "Congratulations, you won!" << std::endl;
                displayBoardFunc(true);  // 显示完整棋盘
                break;
            }
        }
    }
}

int main() {
    int rows, cols, mines;
    
    std::cout << "Setting game difficulty:" << std::endl;
    std::cout << "Enter number of rows (default 10): ";
    std::cin >> rows;
    if (rows <= 0) rows = 10;
    
    std::cout << "Enter number of columns (default 10): ";
    std::cin >> cols;
    if (cols <= 0) cols = 10;
    
    std::cout << "Enter number of mines (default 15): ";
    std::cin >> mines;
    if (mines <= 0) mines = 15;
    
    // 确保地雷数量不超过总格子数
    if (mines >= rows * cols) {
        mines = rows * cols - 1;
        if (mines <= 0) mines = 1;
    }
    
    Minesweeper game(rows, cols, mines);
    game.playGame();
    
    return 0;
}