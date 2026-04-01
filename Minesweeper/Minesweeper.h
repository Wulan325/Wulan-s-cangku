#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <iostream>
#include <random>
#include <ctime>

class Minesweeper {
private:
    int rows;           // 棋盘行数
    int cols;           // 棋盘列数
    int numMines;       // 地雷数量
    std::vector<std::vector<char>> board;        // 真实棋盘（包含地雷和数字）
    std::vector<std::vector<char>> displayBoard; // 显示棋盘（玩家看到的）
    bool gameOver;      // 游戏结束标志
    bool gameWon;       // 游戏获胜标志
    bool firstMove;     // 是否是第一次移动

public:
    // 构造函数
    Minesweeper(int r = 10, int c = 10, int m = 15);
    
    // 初始化游戏
    void initializeGame();
    
    // 放置地雷
    void placeMines(int firstRow, int firstCol);
    
    // 计算每个格子周围的地雷数
    void calculateNumbers();
    
    // 显示棋盘
    void displayBoardFunc(bool revealAll = false);
    
    // 展开空区域（递归）
    void revealEmptyCells(int row, int col);
    
    // 处理玩家移动
    bool makeMove(int row, int col);
    
    // 检查游戏是否获胜
    bool checkWin();
    
    // 获取游戏状态
    bool isGameOver() const { return gameOver; }
    bool isGameWon() const { return gameWon; }
    
    // 主游戏循环
    void playGame();
};

#endif