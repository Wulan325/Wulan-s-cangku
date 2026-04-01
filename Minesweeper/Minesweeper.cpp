#include "Minesweeper.h"
#include <iomanip>

// 构造函数
Minesweeper::Minesweeper(int r, int c, int m) : rows(r), cols(c), numMines(m), gameOver(false), gameWon(false), firstMove(true) {
    board.resize(rows, std::vector<char>(cols, '0'));
    displayBoard.resize(rows, std::vector<char>(cols, '-'));
}

// 初始化游戏
void Minesweeper::initializeGame() {
    // 初始化棋盘
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = '0';
            displayBoard[i][j] = '-';
        }
    }
}

// 放置地雷
void Minesweeper::placeMines(int firstRow, int firstCol) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rowDis(0, rows - 1);
    std::uniform_int_distribution<> colDis(0, cols - 1);

    int minesPlaced = 0;
    while (minesPlaced < numMines) {
        int row = rowDis(gen);
        int col = colDis(gen);

        // 确保不在第一次点击的位置放雷，并且该位置没有雷
        if ((row != firstRow || col != firstCol) && board[row][col] != '*') {
            board[row][col] = '*';
            minesPlaced++;
        }
    }
}

// 计算每个格子周围的地雷数
void Minesweeper::calculateNumbers() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == '*') continue;

            int count = 0;
            // 检查周围8个格子
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di == 0 && dj == 0) continue; // 跳过自己

                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && board[ni][nj] == '*') {
                        count++;
                    }
                }
            }

            board[i][j] = '0' + count;
        }
    }
}

// 显示棋盘
void Minesweeper::displayBoardFunc(bool revealAll) {
    std::cout << "  ";
    for (int j = 0; j < cols; j++) {
        std::cout << j % 10 << " ";  // 列号
    }
    std::cout << std::endl;

    for (int i = 0; i < rows; i++) {
        std::cout << i % 10 << " ";  // 行号
        for (int j = 0; j < cols; j++) {
            if (revealAll) {
                std::cout << board[i][j] << " ";
            } else {
                std::cout << displayBoard[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

// 处理玩家移动
bool Minesweeper::makeMove(int row, int col) {
    // 检查输入是否有效
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        std::cout << "Invalid coordinates! Please re-enter." << std::endl;
        return false;
    }

    // 如果已经揭开，则返回
    if (displayBoard[row][col] != '-') {
        std::cout << "Position already revealed! Please select another." << std::endl;
        return false;
    }

    // 如果是第一次点击，放置地雷并计算数字
    if (firstMove) {
        placeMines(row, col);  // 避免在第一次点击的位置放雷
        calculateNumbers();    // 计算数字
        firstMove = false;     // 标记不是第一次移动了
    }

    // 检查是否踩到地雷
    if (board[row][col] == '*') {
        gameOver = true;
        displayBoard[row][col] = 'X';  // 标记踩到的地雷
        std::cout << "Stepped on a mine! Game over!" << std::endl;
        return true;  // 返回true表示移动有效，但游戏结束
    }

    // 揭开当前格子
    displayBoard[row][col] = board[row][col];

    // 如果是空格子（数字为0），则递归揭开周围的格子
    if (board[row][col] == '0') {
        revealEmptyCells(row, col);
    }

    return true;
}

// 展开空区域（递归）
void Minesweeper::revealEmptyCells(int row, int col) {
    // 检查边界和是否已经揭开
    if (row < 0 || row >= rows || col < 0 || col >= cols || displayBoard[row][col] != '-') {
        return;
    }

    // 揭开当前格子
    displayBoard[row][col] = board[row][col];

    // 如果当前格子是数字（非0），则停止递归
    if (board[row][col] != '0') {
        return;
    }

    // 递归揭开周围的8个格子
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) continue; // 跳过自己

            int ni = row + di;
            int nj = col + dj;

            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                revealEmptyCells(ni, nj);
            }
        }
    }
}

// 检查游戏是否获胜
bool Minesweeper::checkWin() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // 如果有未揭开的非地雷格子，则游戏未结束
            if (displayBoard[i][j] == '-' && board[i][j] != '*') {
                return false;
            }
        }
    }
    gameWon = true;
    gameOver = true;
    return true;
}