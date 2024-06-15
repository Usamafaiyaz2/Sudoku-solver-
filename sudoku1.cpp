#include <iostream>
#define UNASSIGNED 0
#define N 9

using namespace std;

bool isSafe(int grid[N][N], int row, int col, int num);

// Check if the number is already used in the row
bool usedInRow(int grid[N][N], int row, int num) {
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Check if the number is already used in the column
bool usedInCol(int grid[N][N], int col, int num) {
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

// Check if the number is already used in the 3x3 subgrid
bool usedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}

// Check if it's safe to place the number in the specified cell
bool isSafe(int grid[N][N], int row, int col, int num) {
    return !usedInRow(grid, row, num) &&
           !usedInCol(grid, col, num) &&
           !usedInBox(grid, row - row % 3, col - col % 3, num);
}

// Find an unassigned location on the grid
bool findUnassignedLocation(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

// Solve the Sudoku using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;
    if (!findUnassignedLocation(grid, row, col))
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid))
                return true;
            grid[row][col] = UNASSIGNED;
        }
    }
    return false;
}

// Print the grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

// Main function
int main() {
    int grid[N][N];

    cout << "Enter the Sudoku grid (0 for empty cells):" << endl;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cin >> grid[row][col];
        }
    }

    if (solveSudoku(grid)) {
        cout << "Solved Sudoku grid:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}
