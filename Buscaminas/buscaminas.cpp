#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Tablero
const int tab = 6;
// Minas
const int Minas = 8;

// Estructura para el tablero
struct Cell{
    bool boom;
    bool visible;
    int mincerca;
};

vector<vector<Cell>> board(tab, vector<Cell>(tab));

// Funcion para el tablero
void iniTab(){
    for (int i = 0; i < tab; ++i) {
        for (int j = 0; j < tab; ++j) {
            board[i][j].boom = false;
            board[i][j].visible = false;
            board[i][j].mincerca = 0;
        }
    }
}

// Funcion para crear Minas
void creMina(){
    srand(time(NULL));
    int minesPlaced = 0;
    while (minesPlaced < Minas) {
        int x = rand() % tab;
        int y = rand() % tab;
        if (!board[x][y].boom) {
            board[x][y].boom = true;
            minesPlaced++;
        }
    }
}

// Funcion para calcular las minas
void calcuMinas(){
    for (int i = 0; i < tab; ++i) {
        for (int j = 0; j < tab; ++j) {
            if (!board[i][j].boom) {
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        int newX = i + dx;
                        int newY = j + dy;
                        if (newX >= 0 && newX < tab && newY >= 0 && newY < tab) {
                            if (board[newX][newY].boom) {
                                board[i][j].mincerca++;
                            }
                        }
                    }
                }
            }
        }
    }
}

// Funcion para mostrar el tablero
void mostrarTab(){
    cout << "\n  ";
    for (int i = 1; i <= tab; ++i) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < tab; ++i) {
        cout << i + 1 << " ";
        for (int j = 0; j < tab; ++j) {
            if (board[i][j].visible) {
                if (board[i][j].boom) {
                    cout << "* ";
                } else {
                    cout << board[i][j].mincerca << " ";
                }
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
}

// Funcion para revelar una celda y verificar si hay una mina
bool revelMina(int x, int y){
    if (board[x][y].boom) {
        cout << "--Has perdido--" << endl;
        cout << "Habia una mina cerca" << endl;
        // Mostrar Boom
        for (int i = 0; i < tab; ++i) {
            for (int j = 0; j < tab; ++j) {
                if (board[i][j].boom){
                    board[i][j].visible = true;
                }
            }
        }
        mostrarTab(); // BOOM
        // XD
        return true;
    } else {
        board[x][y].visible = true;
        if (board[x][y].mincerca == 0) {
            // Si la celda no tiene minas cercanas, revela las celdas adyacentes.
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int newX = x + dx;
                    int newY = y + dy;
                    if (newX >= 0 && newX < tab && newY >= 0 && newY < tab && !board[newX][newY].visible) {
                        revelMina(newX, newY);
                    }
                }
            }
        }
        return false;
    }
}

int main(){
    iniTab();
    creMina();
    calcuMinas();

    bool GameOver = false;

    while (!GameOver) {
        mostrarTab();

        int x, y;
        std::cout << "Ingrese la Coordenada x: ";
        std::cin >> y;

        std::cout << "\nIngrese la Coordenada y: ";
        std::cin >> x;

        if (x < 1 || x > tab || y < 1 || y > tab) {
            cout << "Coordenadas fuera del rango" << endl;
            continue;
        }

        y--;
        x--;

        GameOver = revelMina(x, y);
    }

}