#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

const int WIDTH = 10;
const int HEIGHT = 20;
const int BLOCK_SIZE = 30;

struct Point {
    int x, y;
};

struct Tetromino {
    std::vector<std::vector<int>> shape;
    Point position;
    sf::Color color;
};

// Tetromino shapes
const std::vector<Tetromino> tetrominos = {
    {{{1, 1, 1, 1}}, {4, 0}, sf::Color::Cyan}, // I
    {{{1, 1}, {1, 1}}, {4, 0}, sf::Color::Yellow}, // O
    {{{0, 1, 1}, {1, 1, 0}}, {4, 0}, sf::Color::Green}, // S
    {{{1, 1, 0}, {0, 1, 1}}, {4, 0}, sf::Color::Red}, // Z
    {{{0, 1, 0}, {1, 1, 1}}, {4, 0}, sf::Color::Magenta}, // T
    {{{1, 0, 0}, {1, 1, 1}}, {4, 0}, sf::Color::Blue}, // L
    {{{0, 0, 1}, {1, 1, 1}}, {4, 0}, sf::Color::Cyan}  // J
};

std::vector<std::vector<int>> board(HEIGHT, std::vector<int>(WIDTH, 0));
int score = 0;
int level = 1;
sf::SoundBuffer lineClearBuffer;
sf::Sound lineClearSound;
sf::SoundBuffer gameOverBuffer;
sf::Sound gameOverSound;

// Function to initialize sounds
void initSounds() {
    lineClearBuffer.loadFromFile("E:/download/download in chrome/installation pacakge/music/fish.wav");
    lineClearSound.setBuffer(lineClearBuffer);
    gameOverBuffer.loadFromFile("E:/download/download in chrome/installation pacakge/music/favorite.wav");
    gameOverSound.setBuffer(gameOverBuffer);
}

// Function to draw the board
void drawBoard(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (board[y][x]) {
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setFillColor(sf::Color::White);
                block.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
                window.draw(block);
            }
        }
    }
}

// Function to check collision
bool checkCollision(const Tetromino& piece) {
    for (int y = 0; y < piece.shape.size(); y++) {
        for (int x = 0; x < piece.shape[y].size(); x++) {
            if (piece.shape[y][x]) {
                int boardX = piece.position.x + x;
                int boardY = piece.position.y + y;
                if (boardX < 0 || boardX >= WIDTH || boardY >= HEIGHT || (boardY >= 0 && board[boardY][boardX])) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Function to rotate the tetromino
void rotateTetromino(Tetromino& piece) {
    std::vector<std::vector<int>> newShape(piece.shape[0].size(), std::vector<int>(piece.shape.size()));
    for (int y = 0; y < piece.shape.size(); y++) {
        for (int x = 0; x < piece.shape[y].size(); x++) {
            newShape[x][piece.shape.size() - 1 - y] = piece.shape[y][x];
        }
    }
    piece.shape = newShape;
    if (checkCollision(piece)) {
        rotateTetromino(piece); // Rotate back if collision occurs
    }
}

// Function to lock the piece into the board
void lockPiece(const Tetromino& piece) {
    for (int y = 0; y < piece.shape.size(); y++) {
        for (int x = 0; x < piece.shape[y].size(); x++) {
            if (piece.shape[y][x]) {
                board[piece.position.y + y][piece.position.x + x] = 1;
            }
        }
    }
}

// Function to clear full lines
void clearLines() {
    for (int y = HEIGHT - 1; y >= 0; y--) {
        bool fullLine = true;
        for (int x = 0; x < WIDTH; x++) {
            if (board[y][x] == 0) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            board.erase(board.begin() + y);
            board.insert(board.begin(), std::vector<int>(WIDTH, 0));
            lineClearSound.play();
            score += 100; // Increase score for each line cleared
            if (score % 1000 == 0) { // Increase level every 1000 points
                level++;
            }
        }
    }
}

// Function to check game over
bool checkGameOver() {
    for (int x = 0; x < WIDTH; x++) {
        if (board[0][x]) {
            gameOverSound.play();
            return true;
        }
    }
    return false;
}

// Function to display the score
void displayScore(sf::RenderWindow& window) {
    sf::Font font;
    font.loadFromFile("D:/note/LOVE.ttf"); // Load a font

    std::ostringstream oss;
    oss << "Score: " << score << " Level: " << level;
    sf::Text text(oss.str(), font, 20);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);
    window.draw(text);
}

// Main game loop
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE), "Tetris");
    initSounds();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        Tetromino currentPiece = tetrominos[rand() % tetrominos.size()];
        currentPiece.position = { WIDTH / 2 - 1, 0 };

        while (true) {
            drawBoard(window);
            displayScore(window);

            // Draw the current piece
            for (int y = 0; y < currentPiece.shape.size(); y++) {
                for (int x = 0; x < currentPiece.shape[y].size(); x++) {
                    if (currentPiece.shape[y][x]) {
                        sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                        block.setFillColor(currentPiece.color);
                        block.setPosition((currentPiece.position.x + x) * BLOCK_SIZE, (currentPiece.position.y + y) * BLOCK_SIZE);
                        window.draw(block);
                    }
                }
            }
            window.display();

            // Handle user input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                currentPiece.position.x--;
                if (checkCollision(currentPiece)) currentPiece.position.x++;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                currentPiece.position.x++;
                if (checkCollision(currentPiece)) currentPiece.position.x--;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                currentPiece.position.y++;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                rotateTetromino(currentPiece);
            }

            // Move piece down
            currentPiece.position.y++;
            if (checkCollision(currentPiece)) {
                currentPiece.position.y--;
                lockPiece(currentPiece);
                clearLines();
                if (checkGameOver()) {
                    window.close(); // Close the window if game is over
                    break;
                }
                break; // Break to select a new piece
            }

            // Delay for piece dropping based on level
            sf::sleep(sf::milliseconds(1000 / level));
        }
    }

    return 0;
}
