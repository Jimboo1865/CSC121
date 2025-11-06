#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

const int WIDTH = 100;
const int HEIGHT = 100;
const int CELL_SIZE = 8;
const float UPDATE_INTERVAL = 0.1f; // seconds per generation

// Return count of live neighbors for (x, y)
int countNeighbors(const std::vector<std::vector<bool>>& grid, int x, int y) {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                count += grid[nx][ny];
            }
        }
    }
    return count;
}

int main() {
    // ✅ Create the window
    sf::VideoMode mode;
    mode.size = { WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE };
    sf::RenderWindow window(mode, "Conway's Game of Life");

    // ✅ Create grids (double-buffering)
    std::vector<std::vector<bool>> grid(WIDTH, std::vector<bool>(HEIGHT, false));
    std::vector<std::vector<bool>> nextGrid = grid;

    bool paused = true;
    sf::Clock clock;

    // ✅ Main loop
    while (window.isOpen()) {
        // --- EVENT HANDLING ---
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            // Toggle pause/resume with space bar
            if (event->is<sf::Event::KeyPressed>()) {
                auto keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent->scancode == sf::Keyboard::Scancode::Space)
                    paused = !paused;
            }

            // Toggle cell with mouse
            if (event->is<sf::Event::MouseButtonPressed>()) {
                auto mouse = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouse->button == sf::Mouse::Button::Left) {
                    int x = mouse->position.x / CELL_SIZE;
                    int y = mouse->position.y / CELL_SIZE;
                    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
                        grid[x][y] = !grid[x][y];
                }
            }
        }

        // --- UPDATE GRID ---
        if (!paused && clock.getElapsedTime().asSeconds() >= UPDATE_INTERVAL) {
            for (int x = 0; x < WIDTH; ++x) {
                for (int y = 0; y < HEIGHT; ++y) {
                    int neighbors = countNeighbors(grid, x, y);
                    if (grid[x][y]) {
                        nextGrid[x][y] = (neighbors == 2 || neighbors == 3);
                    } else {
                        nextGrid[x][y] = (neighbors == 3);
                    }
                }
            }
            grid.swap(nextGrid);
            clock.restart();
        }

        // --- DRAW ---
        window.clear(sf::Color::Black);
        sf::RectangleShape cellShape({(float)CELL_SIZE - 1, (float)CELL_SIZE - 1});
        cellShape.setFillColor(sf::Color::Green);

        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                if (grid[x][y]) {
                    cellShape.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                    window.draw(cellShape);
                }
            }
        }

        window.display();
    }

    return 0;
}