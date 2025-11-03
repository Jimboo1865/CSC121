#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 50;
const int HEIGHT = 25;
const int CELL_SIZE = 20;

int countNeighbors(const vector<vector<bool>>& grid, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT)
                count += grid[ny][nx];
        }
    }
    return count;
}

int main() {
    vector<vector<bool>> current(HEIGHT, vector<bool>(WIDTH, false));
    vector<vector<bool>> next(HEIGHT, vector<bool>(WIDTH, false));

    srand(static_cast<unsigned>(time(nullptr)));
    for (int y = 0; y < HEIGHT; ++y)
        for (int x = 0; x < WIDTH; ++x)
            current[y][x] = rand() % 2;

    sf::RenderWindow window(
    sf::VideoMode({WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE}),
    "Conway's Game of Life",
    sf::State::Windowed
);
    window.setFramerateLimit(10);

    sf::RectangleShape cell({CELL_SIZE - 1.0f, CELL_SIZE - 1.0f});
    cell.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        // New SFML 3.0 event handling
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Compute next state
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                int n = countNeighbors(current, x, y);
                next[y][x] = current[y][x] ? (n == 2 || n == 3) : (n == 3);
            }
        }
        current.swap(next);

        // Draw
        window.clear();
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                if (current[y][x]) {
                    cell.setPosition({static_cast<float>(x * CELL_SIZE), static_cast<float>(y * CELL_SIZE)});
                    window.draw(cell);
                }
            }
        }
        window.display();
    }

    return 0;
}