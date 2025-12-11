// SFML chess UI backed by the board/piece logic

#include "board.h"

#include <SFML/Graphics.hpp>

#include <array>
#include <optional>
#include <string>
#include <vector>

const int BOARD_SIZE = 8;
const int CELL_SIZE = 80;
const int UI_HEIGHT = 100;
const sf::Color LIGHT_SQUARE(238, 238, 210);
const sf::Color DARK_SQUARE(118, 150, 86);
const sf::Color SELECT_COLOR(255, 215, 0);

struct UIState {
    Board board;
    bool inProgress = false;
    bool whiteTurn = true;
    std::optional<Position> selected;
    sf::Font font;
    bool hasFont = false;
    std::string status = "Click Start Game";
};

int toIndex(int row, int col) {
    return row * BOARD_SIZE + col;
}

std::optional<Position> posFromMouse(int mx, int my) {
    int col = mx / CELL_SIZE;
    int row = (my - UI_HEIGHT) / CELL_SIZE;
    if (col < 0 || col >= BOARD_SIZE || row < 0 || row >= BOARD_SIZE) {
        return std::nullopt;
    }
    Position pos;
    pos.row = row;
    pos.col = col;
    return pos;
}

void resetGame(UIState& state) {
    state.board.initialize();
    state.whiteTurn = true;
    state.inProgress = true;
    state.selected.reset();
    state.status = "White to move";
}

void endGame(UIState& state) {
    state.board.clear();
    state.inProgress = false;
    state.selected.reset();
    state.status = "Game ended";
}

bool loadFont(UIState& state) {
    const std::vector<std::string> fontPaths = {
        "/System/Library/Fonts/Supplemental/Arial.ttf",
        "/Library/Fonts/Arial.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
    };
    for (const std::string& path : fontPaths) {
        if (state.font.openFromFile(path)) {
            state.hasFont = true;
            return true;
        }
    }
    state.hasFont = false;
    return false;
}

sf::FloatRect startButtonBounds() {
    return sf::FloatRect(sf::Vector2f(20.0f, 20.0f), sf::Vector2f(140.0f, 40.0f));
}

sf::FloatRect endButtonBounds() {
    return sf::FloatRect(sf::Vector2f(180.0f, 20.0f), sf::Vector2f(140.0f, 40.0f));
}

void drawButton(sf::RenderWindow& window, const sf::FloatRect& bounds, const std::string& label, bool active, const sf::Font* font) {
    sf::RectangleShape shape;
    shape.setPosition(bounds.position);
    shape.setSize(bounds.size);
    shape.setFillColor(active ? sf::Color(60, 160, 75) : sf::Color(70, 70, 90));
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color::Black);
    window.draw(shape);

    if (font != nullptr) {
        sf::Text text(*font, label, 18);
        text.setFillColor(sf::Color::White);
        const sf::FloatRect textBounds = text.getLocalBounds();
        float textX = bounds.position.x + (bounds.size.x - textBounds.size.x) / 2.0f;
        float textY = bounds.position.y + (bounds.size.y - textBounds.size.y) / 2.5f;
        text.setPosition(sf::Vector2f(textX, textY));
        window.draw(text);
    }
}

void drawStatus(sf::RenderWindow& window, const UIState& state) {
    if (!state.hasFont) {
        return;
    }
    sf::Text text(state.font, state.status, 18);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(340.0f, 30.0f));
    window.draw(text);
}

void drawBoard(sf::RenderWindow& window, const UIState& state) {
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            sf::RectangleShape square(sf::Vector2f(static_cast<float>(CELL_SIZE), static_cast<float>(CELL_SIZE)));
            square.setPosition(sf::Vector2f(static_cast<float>(c * CELL_SIZE), static_cast<float>(UI_HEIGHT + r * CELL_SIZE)));
            bool light = ((r + c) % 2 == 0);
            square.setFillColor(light ? LIGHT_SQUARE : DARK_SQUARE);
            if (state.selected && state.selected->row == r && state.selected->col == c) {
                square.setOutlineThickness(3.0f);
                square.setOutlineColor(SELECT_COLOR);
            } else {
                square.setOutlineThickness(0.0f);
            }
            window.draw(square);

            Position pos;
            pos.row = r;
            pos.col = c;
            const Piece* piece = state.board.pieceAt(pos);
            if (piece != nullptr) {
                const char symbol = piece->symbol();
                const bool whitePiece = (symbol == std::toupper(static_cast<unsigned char>(symbol)));
                sf::CircleShape shape(static_cast<float>(CELL_SIZE) * 0.35f);
                shape.setFillColor(whitePiece ? sf::Color(240, 240, 240) : sf::Color(40, 40, 40));
                shape.setOutlineThickness(2.0f);
                shape.setOutlineColor(sf::Color::Black);
                shape.setPosition(sf::Vector2f(
                    static_cast<float>(c * CELL_SIZE + CELL_SIZE * 0.15f),
                    static_cast<float>(UI_HEIGHT + r * CELL_SIZE + CELL_SIZE * 0.15f)));
                window.draw(shape);

                if (state.hasFont) {
                    sf::Text text(state.font, std::string(1, static_cast<char>(std::toupper(static_cast<unsigned char>(symbol)))), 28);
                    text.setFillColor(whitePiece ? sf::Color::Black : sf::Color::White);
                    text.setStyle(sf::Text::Bold);
                    text.setPosition(sf::Vector2f(
                        static_cast<float>(c * CELL_SIZE + CELL_SIZE * 0.35f),
                        static_cast<float>(UI_HEIGHT + r * CELL_SIZE + CELL_SIZE * 0.25f)));
                    window.draw(text);
                }
            }
        }
    }
}

void handleMove(UIState& state, Position target) {
    if (!state.selected) {
        const Piece* piece = state.board.pieceAt(target);
        if (piece != nullptr && piece->isWhite() == state.whiteTurn) {
            state.selected = target;
            state.status = state.whiteTurn ? "White selected" : "Black selected";
        }
        return;
    }

    Position from = *state.selected;
    if (from.row == target.row && from.col == target.col) {
        state.selected.reset();
        return;
    }

    if (state.board.movePiece(from, target, state.whiteTurn)) {
        state.whiteTurn = !state.whiteTurn;
        state.status = state.whiteTurn ? "White to move" : "Black to move";
    } else {
        state.status = "Illegal move";
    }
    state.selected.reset();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(
                                          static_cast<unsigned int>(CELL_SIZE * BOARD_SIZE),
                                          static_cast<unsigned int>(CELL_SIZE * BOARD_SIZE + UI_HEIGHT))),
                            "Chess UI");
    window.setFramerateLimit(60);

    UIState state;
    loadFont(state);
    resetGame(state);

    while (window.isOpen()) {
        while (true) {
            std::optional<sf::Event> event = window.pollEvent();
            if (!event) {
                break;
            }
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (event->is<sf::Event::MouseButtonPressed>()) {
                const sf::Event::MouseButtonPressed* mouse = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouse != nullptr && mouse->button == sf::Mouse::Button::Left) {
                    const int mx = mouse->position.x;
                    const int my = mouse->position.y;
                    if (startButtonBounds().contains(sf::Vector2f(static_cast<float>(mx), static_cast<float>(my)))) {
                        resetGame(state);
                    } else if (endButtonBounds().contains(sf::Vector2f(static_cast<float>(mx), static_cast<float>(my)))) {
                        endGame(state);
                    } else if (state.inProgress) {
                        std::optional<Position> pos = posFromMouse(mx, my);
                        if (pos) {
                            handleMove(state, *pos);
                        }
                    }
                }
            } else if (event->is<sf::Event::KeyPressed>()) {
                const sf::Event::KeyPressed* key = event->getIf<sf::Event::KeyPressed>();
                if (key != nullptr && key->scancode == sf::Keyboard::Scan::Escape) {
                    window.close();
                }
            }
        }

        window.clear(sf::Color(30, 30, 40));
        drawButton(window, startButtonBounds(), "Start Game", state.inProgress, state.hasFont ? &state.font : nullptr);
        drawButton(window, endButtonBounds(), "End Game", !state.inProgress, state.hasFont ? &state.font : nullptr);
        drawStatus(window, state);
        drawBoard(window, state);
        window.display();
    }

    return 0;
}
