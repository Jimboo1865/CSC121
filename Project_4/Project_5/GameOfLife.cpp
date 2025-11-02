#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

const int WIDTH = 200;
const int HEIGHT = 25;

int countNeighbors(const vector<vector<bool>>& grid, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            

            int nx = x + i;
            int ny = y + j;


            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                if (grid[ny][nx]) ++count;
            }
        }
    }
    return count;
}

void displayGrid(const vector<vector<bool>>& grid) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            cout << (grid[i][j] ? '0' : ' ');
        }
        cout << '\n';
    }
}


int main() {
    vector<vector<bool>> current(HEIGHT, vector<bool>(WIDTH, false));
    vector<vector<bool>> next(HEIGHT, vector<bool>(WIDTH, false));

    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
        current[i][j] = rand() % 2;
        }
    }

    while (true) {
        displayGrid(current);


        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                int neighbors = countNeighbors(current, j, i);
            
                if (current[i][j]) {
                 next[i][j] = (neighbors == 2 || neighbors == 3);
                } else {
                    next[i][j] = (neighbors == 3);
                }
         }
        }

        current.swap(next);

        this_thread::sleep_for(chrono::milliseconds(100));

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    return 0;
}