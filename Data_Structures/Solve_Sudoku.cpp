// #Sudoku
#include <iostream>
using namespace std;

// Function declarations
bool isRowSafe(int board[4][4], int row, int num);
bool isColSafe(int board[4][4], int col, int num);
bool isBoxSafe(int board[4][4], int startRow, int startCol, int num);
bool isSafe(int board[4][4], int row, int col, int num);
bool findEmptyLocation(int board[4][4], int &row, int &col);
bool solveSudoku(int board[4][4]);
void printBoard(int board[4][4]);

// Function definitions
bool isRowSafe(int board[4][4], int row, int num) {
  for (int i = 0; i < 4; i++) {
    if (board[row][i] == num)
      return false;
  }
  return true;
}

bool isColSafe(int board[4][4], int col, int num) {
  for (int i = 0; i < 4; i++) {
    if (board[i][col] == num)
      return false;
  }
  return true;
}

bool isBoxSafe(int board[4][4], int startRow, int startCol, int num) {
  int row = (startRow / 2) * 2;
  int col = (startCol / 2) * 2;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (board[row + i][col + j] == num)
        return false;
    }
  }
  return true;
}

bool isSafe(int board[4][4], int row, int col, int num) {
  return isRowSafe(board, row, num) && isColSafe(board, col, num) &&
         isBoxSafe(board, row, col, num);
}

bool findEmptyLocation(int board[4][4], int &row, int &col) {
  for (row = 0; row < 4; row++) {
    for (col = 0; col < 4; col++) {
      if (board[row][col] == 0)
        return true;
    }
  }
  return false;
}

bool solveSudoku(int board[4][4]) {
  int row, col;
  if (!findEmptyLocation(board, row, col))
    return true; // Sudoku is solved

  for (int num = 1; num <= 4; num++) {
    if (isSafe(board, row, col, num)) {
      board[row][col] = num;
      printBoard(board); // Print the current board

      if (solveSudoku(board))
        return true;

      board[row][col] = 0; // Backtrack
      printBoard(board);   // Print board after backtracking
    }
  }
  return false;
}

void printBoard(int board[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  int board[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cin >> board[i][j];
    }
  }
  solveSudoku(board);
  return 0;
}
