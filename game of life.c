
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h> // фишки для винды чтобы мозги не шатало
#define ROWS 20 // число строк в игровом поле
#define COLS 20 // число столбцов в игровом поле
#define ALIVE '*' // символ для живой клетки
#define DEAD ' ' // символ для мертвой клетки
// функция для проверки границ игрового поля
int isValidCell(int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}
// функция для инициализации игрового поля
void initGameBoard(char gameBoard[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            gameBoard[i][j] = DEAD;
        }
    }
}
// функция для вывода игрового поля на экран
void printGameBoard(char gameBoard[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", gameBoard[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
// функция для обновления состояния клеток на основе правил игры "Жизнь"
void updateGameBoard(char gameBoard[][COLS]) {
    char newGameBoard[ROWS][COLS]; // временное поле для хранения нового состояния
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int aliveNeighbors = 0;

            // проверяем всех соседей текущей клетки
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (k == 0 && l == 0) {
                        continue; // пропускаем текущую клетку
                    }

                    int neighborX = i + k;
                    int neighborY = j + l;

                    if (isValidCell(neighborX, neighborY) && gameBoard[neighborX][neighborY] == ALIVE) {
                        aliveNeighbors++;
                    }
                }
            }

            // обновляем состояние клетки на основе правил игры
            if (gameBoard[i][j] == ALIVE) {
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newGameBoard[i][j] = DEAD;  // мертвая клетка из-за недостатка или перенаселения
                }
                else {
                    newGameBoard[i][j] = ALIVE;  // продолжает быть живой
                }
            }
            else {
                if (aliveNeighbors == 3) {
                    newGameBoard[i][j] = ALIVE;  // рождается новая клетка
                }
                else {
                    newGameBoard[i][j] = DEAD;  // клетка остается мертвой
                }
            }
        }
    }

    // копируем новое состояние клеток в оригинальное поле
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            gameBoard[i][j] = newGameBoard[i][j];
        }
    }

}
int main() {
    char gameBoard[ROWS][COLS];
    initGameBoard(gameBoard);

    // задаем начальное состояние поля
    gameBoard[4][5] = ALIVE;
    gameBoard[5][4] = ALIVE;
    gameBoard[5][5] = ALIVE;
    gameBoard[5][6] = ALIVE;
    gameBoard[5][7] = ALIVE;
    gameBoard[4][6] = ALIVE;
    gameBoard[4][7] = ALIVE;
    gameBoard[9][9] = ALIVE;
    gameBoard[8][9] = ALIVE;
    gameBoard[8][10] = ALIVE;

    // игровой цикл
    while (1) {
        system("cls"); // очищаем экран (для UNIX-подобных систем)
        printGameBoard(gameBoard);
        updateGameBoard(gameBoard);
        Sleep(500);
    }

    return 0;

}