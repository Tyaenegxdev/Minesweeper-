#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 5;  // Grid size
const int MINES = 5; // Number of mines

// Directions for the 8 neighbors (up, down, left, right, and diagonals)
const int dirs[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

struct Cell {
    bool isMine;
    bool revealed;
    int adjacentMines;
};

// Function to initialize the grid with mines and calculate adjacent mines
void initializeGrid(vector<vector<Cell>>& grid) {
    // Randomly place mines
    srand(time(0));
    for (int i = 0; i < MINES; ++i) {
        int r = rand() % SIZE;
        int c = rand() % SIZE;
        if (grid[r][c].isMine) {
            --i; // Retry if a mine is already placed
        } else {
            grid[r][c].isMine = true;
        }
    }

    // Calculate adjacent mines for each cell
    for (int r = 0; r < SIZE; ++r) {
        for (int c = 0; c < SIZE; ++c) {
            if (!grid[r][c].isMine) {
                int count = 0;
                // Check all 8 neighbors
                for (auto& dir : dirs) {
                    int nr = r + dir[0], nc = c + dir[1];
                    if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE && grid[nr][nc].isMine) {
                        count++;
                    }
                }
                grid[r][c].adjacentMines = count;
            }
        }
    }
}

// Function to print the grid (hidden or revealed cells)
void printGrid(const vector<vector<Cell>>& grid, bool reveal = false) {
    for (int r = 0; r < SIZE; ++r) {
        for (int c = 0; c < SIZE; ++c) {
            if (grid[r][c].revealed || reveal) {
                if (grid[r][c].isMine) {
                    cout << "* ";
                } else {
                    cout << grid[r][c].adjacentMines << " ";
                }
            } else {
                cout << "# "; // Hidden cells
            }
        }
        cout << endl;
    }
}

// Function to reveal a cell and its neighbors if no adjacent mines
void revealCell(int r, int c, vector<vector<Cell>>& grid) {
    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || grid[r][c].revealed) {
        return;
    }
    grid[r][c].revealed = true;

    if (grid[r][c].adjacentMines == 0) {
        for (auto& dir : dirs) {
            revealCell(r + dir[0], c + dir[1], grid);
        }
    }
}

// Function to check if the player has won
bool checkWin(const vector<vector<Cell>>& grid) {
    for (int r = 0; r < SIZE; ++r) {
        for (int c = 0; c < SIZE; ++c) {
            if (!grid[r][c].isMine && !grid[r][c].revealed) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector<vector<Cell>> grid(SIZE, vector<Cell>(SIZE));
    initializeGrid(grid);

    bool gameOver = false;
    while (!gameOver) {
        printGrid(grid);

        int r, c;
        cout << "Enter row and column to reveal (0 to " << SIZE - 1 << "): ";
        cin >> r >> c;

        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) {
            cout << "Invalid coordinates. Try again." << endl;
            continue;
        }

        if (grid[r][c].isMine) {
            cout << "You hit a mine! Game over." << endl;
            gameOver = true;
        } else {
            revealCell(r, c, grid);
            if (checkWin(grid)) {
                printGrid(grid, true);
                cout << "Congratulations! You've won!" << endl;
                gameOver = true;
            }
        }
    }

    return 0;
}
