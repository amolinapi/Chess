#include "board.h"
#include <iostream>

Board::Board()
{
    textures[Piece::Type::KING].loadFromFile("../data/textures/KingWhite.png");
    textures[Piece::Type::QUEEN].loadFromFile("../data/textures/QueenWhite.png");
    textures[Piece::Type::ROOK].loadFromFile("../data/textures/RookWhite.png");
    textures[Piece::Type::BISHOP].loadFromFile("../data/textures/BishopWhite.png");
    textures[Piece::Type::NIGHT].loadFromFile("../data/textures/NightWhite.png");
    textures[Piece::Type::PAWN].loadFromFile("../data/textures/PawnWhite.png");
}

int Board::createBoard()
{
    if (!chess_board_texture.loadFromFile("../data/textures/ChessBoard.png")) {
        return EXIT_FAILURE;
    }
    chess_board_sprite.setTexture(chess_board_texture);
    chess_board_sprite.setPosition(0, 0);

    if (!board_texture.loadFromFile("../data/textures/Board.png")) {
        return EXIT_FAILURE;
    }
    board_sprite.setTexture(board_texture);
    board_sprite.setScale(2.0833f, 2.0833f);
    float posX = 400 - (board_sprite.getGlobalBounds().width / 2);
    float posY = 400 - (board_sprite.getGlobalBounds().height / 2);
    board_sprite.setPosition(posX, posY);
    
    return 0;
}

void Board::initializePieces()
{
    auto placePiece = [&](int x, int y, std::unique_ptr<Piece> piece) {
        grid[x][y] = std::move(piece);
        grid[x][y]->setPosition(gridToPixel(x, y));
    };
    
    //PAWS
    for (int i = 0; i < 8; i++) {
        placePiece(i, 1, std::make_unique<Pawn>());
        placePiece(i, 6, std::make_unique<Pawn>());
    }
    //ROOKS
    placePiece(0, 0, std::make_unique<Rook>());
    placePiece(7, 0, std::make_unique<Rook>());
    placePiece(0, 7, std::make_unique<Rook>());
    placePiece(7, 7, std::make_unique<Rook>());
    //NIGHTS
    placePiece(1, 0, std::make_unique<Night>());
    placePiece(6, 0, std::make_unique<Night>());
    placePiece(1, 7, std::make_unique<Night>());
    placePiece(6, 7, std::make_unique<Night>());
    //BISHOPS
    placePiece(2, 0, std::make_unique<Bishop>());
    placePiece(5, 0, std::make_unique<Bishop>());
    placePiece(2, 7, std::make_unique<Bishop>());
    placePiece(5, 7, std::make_unique<Bishop>());
    //KING
    placePiece(3, 0, std::make_unique<King>());
    placePiece(3, 7, std::make_unique<King>());
    //QUEEN
    placePiece(4, 0, std::make_unique<Queen>());
    placePiece(4, 7, std::make_unique<Queen>());
}

Vector2f Board::gridToPixel(int x, int y)
{
    float tileSize = board_sprite.getGlobalBounds().width / 8.0f;
    return Vector2f(x * tileSize + board_sprite.getGlobalBounds().left,
        y * tileSize + board_sprite.getGlobalBounds().top);
}

int Board::createPieces()
{
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (grid[x][y]) {
                grid[x][y]->setTexture(textures[grid[x][y]->getType()]);
                if (y <= 1) {
                    grid[x][y]->setColor(Piece::PieceColor::BLACK);
                    grid[x][y]->setColorSide(Piece::PieceColor::BLACK);
                }
                else if (y >= 6) {
                    grid[x][y]->setColor(Piece::PieceColor::WHITE);
                    grid[x][y]->setColorSide(Piece::PieceColor::WHITE);
                }
                grid[x][y]->setScale(2.0833f, 2.0833f);
            }
        }
    }

    return 0;
}

void Board::handleClick(Vector2f mousePos)
{
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (grid[x][y] && grid[x][y]->getSprite().getGlobalBounds().contains(mousePos)) {
                if (selectedPiece.first == -1) {
                    selectedPiece = { x, y };
                    std::cout << "Pieza seleccionada en (" << x << ", " << y << ")\n";
                }
                else {
                    int startX = selectedPiece.first;
                    int startY = selectedPiece.second;

                    std::cout << "Intentando mover de (" << startX << ", " << startY
                        << ") a (" << x << ", " << y << ")\n";

                    movePiece(startX, startY, x, y);
                    selectedPiece = { -1, -1 };
                }
                return;
            }
        }
    }

    if (selectedPiece.first != -1) {
        int startX = selectedPiece.first;
        int startY = selectedPiece.second;

        // Convertir mousePos a coordenadas de tablero
        float tileSize = board_sprite.getGlobalBounds().width / 8.0f;
        int targetX = (mousePos.x - board_sprite.getGlobalBounds().left) / tileSize;
        int targetY = (mousePos.y - board_sprite.getGlobalBounds().top) / tileSize;

        std::cout << "Intentando mover de (" << startX << ", " << startY
            << ") a (" << targetX << ", " << targetY << ")\n";

        movePiece(startX, startY, targetX, targetY);
        selectedPiece = { -1, -1 };  // Desseleccionar la pieza después del movimiento
    }
}

void Board::movePiece(int startX, int startY, int endX, int endY)
{
    // Verificar que la casilla de origen contiene una pieza
    if (!grid[startX][startY]) {
        std::cout << "No hay pieza en la posición de origen.\n";
        return;
    }

    // Verificar que la casilla de destino está dentro del tablero
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        std::cout << "Movimiento fuera de los límites del tablero.\n";
        return;
    }

    // Verificar que la pieza puede moverse a esa casilla (implementado en cada pieza)
    if (!grid[startX][startY]->canMoveTo(startX, startY, endX, endY, grid)) {
        std::cout << "Movimiento no permitido según las reglas de la pieza.\n";
        return;
    }

    // Si hay una pieza en la casilla de destino, "capturarla" (en este caso, eliminarla)
    if (grid[endX][endY]) {
        std::cout << "Capturando pieza en (" << endX << ", " << endY << ")\n";
        grid[endX][endY] = nullptr;
    }

    // Mover la pieza a la nueva posición
    grid[endX][endY] = std::move(grid[startX][startY]);
    grid[endX][endY]->setPosition(gridToPixel(endX, endY)); // Actualizar la posición en pantalla
    grid[startX][startY] = nullptr; // Vaciar la casilla de origen

    std::cout << "Pieza movida de (" << startX << ", " << startY << ") a (" << endX << ", " << endY << ")\n";
}

void Board::draw(RenderWindow* window)
{
    if (window) {
        window->draw(chess_board_sprite);
        window->draw(board_sprite);

        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (grid[x][y]) {  // Si hay una pieza en esta casilla
                    grid[x][y]->draw(window);
                }
            }
        }

    }
}
