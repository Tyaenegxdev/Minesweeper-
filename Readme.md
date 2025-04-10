## A very simple and interesting implementation of Minesweeper.
How this works:
- The grid is displayed with # representing hidden cells.

- You input coordinates (row and column) to reveal cells, like 1 1 for the cell in the second row, second column.

- If the cell is empty, the game will show the number of adjacent mines (0 in this example).

- If the cell has no adjacent mines (value 0), the game automatically reveals neighboring cells.

- If you hit a mine, the game ends with "You hit a mine! Game over."
