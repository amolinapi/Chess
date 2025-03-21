#include "board.h"
#include <iostream>
#include <thread>
#include <chrono>

Board::Board()
{
    textures[Piece::Type::KING].loadFromFile("../data/textures/KingWhite.png");
    textures[Piece::Type::QUEEN].loadFromFile("../data/textures/QueenWhite.png");
    textures[Piece::Type::ROOK].loadFromFile("../data/textures/RookWhite.png");
    textures[Piece::Type::BISHOP].loadFromFile("../data/textures/BishopWhite.png");
    textures[Piece::Type::NIGHT].loadFromFile("../data/textures/NightWhite.png");
    textures[Piece::Type::PAWN].loadFromFile("../data/textures/PawnWhite.png");

    texturesBlack[Piece::Type::KING].loadFromFile("../data/textures/KingBlack.png");
    texturesBlack[Piece::Type::QUEEN].loadFromFile("../data/textures/QueenBlack.png");
    texturesBlack[Piece::Type::ROOK].loadFromFile("../data/textures/RookBlack.png");
    texturesBlack[Piece::Type::BISHOP].loadFromFile("../data/textures/BishopBlack.png");
    texturesBlack[Piece::Type::NIGHT].loadFromFile("../data/textures/NightBlack.png");
    texturesBlack[Piece::Type::PAWN].loadFromFile("../data/textures/PawnBlack.png");

    turn = Piece::PieceColor::WHITE;
}

int Board::loadSounds()
{
    if (!moveBuffer.loadFromFile("../data/audio/move.wav")) {
        std::cerr << "Error al cargar move.wav" << std::endl;
    }

    moveSound.setBuffer(moveBuffer);
    moveSound.setVolume(100);

    if (!captureBuffer.loadFromFile("../data/audio/capture.wav")) {
        std::cerr << "Error cargando el sonido de captura\n";
    }

    captureSound.setBuffer(captureBuffer);
    captureSound.setVolume(100);

    if (!winBuffer.loadFromFile("../data/audio/win.wav")) {
        std::cerr << "Error cargando el sonido de captura\n";
    }

    winSound.setBuffer(winBuffer);
    winSound.setVolume(100);
    
    return 0;
}

int Board::loadFonts()
{
    if (!font.loadFromFile("../data/font/LLPIXEL3.ttf")) {
        return EXIT_FAILURE;
    }
    title = Text("CHESS GAME", font);
    title.setCharacterSize(40);
    title.setFillColor(Color(90, 61, 32));

    FloatRect textBounds = title.getGlobalBounds();

    float centerX = (chess_board_sprite.getGlobalBounds().width - textBounds.width) / 2.0f;

    title.setPosition(centerX, 0);

    turnText = Text("Turn: White", font);
    turnText.setCharacterSize(25);
    float turnX = (chess_board_sprite.getGlobalBounds().width - turnText.getGlobalBounds().width) - 25.0f;
    turnText.setPosition(turnX, title.getGlobalBounds().height / 2.0f);

    return 0;
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
    
    if (!valid_cell_texture.loadFromFile("../data/textures/direction.png")) {
        return EXIT_FAILURE;
    }
    valid_cell_sprite.setTexture(valid_cell_texture);
    valid_cell_sprite.setScale(2.0833f, 2.0833f);
    valid_cell_sprite.setColor(Color(255,255,255,128));
    if (!kill_cell_texture.loadFromFile("../data/textures/direction2.png")) {
        return EXIT_FAILURE;
    }
    kill_cell_sprite.setTexture(kill_cell_texture);
    kill_cell_sprite.setScale(2.0833f, 2.0833f);
    kill_cell_sprite.setColor(Color(255, 255, 255, 128));

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
                if (y <= 1) {
                    grid[x][y]->setTexture(texturesBlack[grid[x][y]->getType()]);
                    grid[x][y]->setColorSide(Piece::PieceColor::BLACK);
                }
                else if (y >= 6) {
                    grid[x][y]->setTexture(textures[grid[x][y]->getType()]);
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
            if (grid[x][y] && grid[x][y]->getSprite().getGlobalBounds().contains(mousePos) && grid[x][y]->getColorSide() == turn) {
                if (selectedPiece.first == -1) {
                    selectedPiece = { x, y };
                    moveHints.clear();
                    killHints.clear();

                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {
                            if (grid[x][y]->canMoveTo(x, y, i, j, grid)) {
                                if (grid[i][j] && grid[i][j]->getColorSide()  != grid[x][y]->getColorSide()) {
                                    killHints.emplace_back(i, j); // Casilla donde se puede capturar
                                }
                                else {
                                    moveHints.emplace_back(i, j); // Casilla donde se puede mover
                                }
                            }
                        }
                    }

                    std::cout << "Selected piece on (" << x << ", " << y << ")\n";
                }
                else {
                    int startX = selectedPiece.first;
                    int startY = selectedPiece.second;

                    std::cout << "Trying to move from (" << startX << ", " << startY
                        << ") to (" << x << ", " << y << ")\n";

                    movePiece(startX, startY, x, y);
                    selectedPiece = { -1, -1 };
                    moveHints.clear();
                    killHints.clear();
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

        std::cout << "Trying to move from (" << startX << ", " << startY
            << ") to (" << targetX << ", " << targetY << ")\n";

        movePiece(startX, startY, targetX, targetY);
        selectedPiece = { -1, -1 }; 
        moveHints.clear();
        killHints.clear();
    }
}

void Board::movePiece(int startX, int startY, int endX, int endY)
{
    
    // Verificar que la casilla de origen contiene una pieza
    if (!grid[startX][startY]) {
        std::cout << "No piece found.\n";
        return;
    }

    if (grid[startX][startY]->getColorSide() != turn) {
        std::cout << "Wrong turn";
        return;
    }

    // Verificar que la casilla de destino est� dentro del tablero
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        std::cout << "Out of bounds movement.\n";
        return;
    }

    // Verificar que la pieza puede moverse a esa casilla (implementado en cada pieza)
    if (!grid[startX][startY]->canMoveTo(startX, startY, endX, endY, grid)) {
        std::cout << "Invalid movement.\n";
        return;
    }

    // Si hay una pieza en la casilla de destino, "capturarla" (en este caso, eliminarla)
    if (grid[endX][endY]) {
        if (dynamic_cast<King*>(grid[endX][endY].get())) {
            std::cout << "�King captured! Restarting game...\n";
            resetGame();
            return;
        }
        std::cout << "Capture piece on (" << endX << ", " << endY << ")\n";
        captureSound.play();
        grid[endX][endY] = nullptr;
    }
    else {
        moveSound.play();
    }


    // Mover la pieza a la nueva posici�n
    grid[endX][endY] = std::move(grid[startX][startY]);
    grid[endX][endY]->setPosition(gridToPixel(endX, endY)); // Actualizar la posici�n en pantalla
    grid[startX][startY] = nullptr; // Vaciar la casilla de origen


    if (turn == Piece::PieceColor::WHITE) {
        turn = Piece::PieceColor::BLACK;
        turnText.setString("Turn: Black");
        turnText.setFillColor(Color::Black);
    }
    else {
        turn = Piece::PieceColor::WHITE;
        turnText.setString("Turn: White");
        turnText.setFillColor(Color::White);
    }

    checkGameState();

    std::cout << "Moving piece from (" << startX << ", " << startY << ") to (" << endX << ", " << endY << ")\n";
}

void Board::resetGame()
{
    winSound.play();
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            grid[x][y] = nullptr;
        }
    }

    selectedPiece = { -1, -1 };
    moveHints.clear();
    killHints.clear();
    turn = Piece::PieceColor::WHITE;
    turnText.setString("Turn: White");
    turnText.setFillColor(Color::White);

    initializePieces();
    createPieces();
}

void Board::draw(RenderWindow* window)
{
    if (window) {
        window->draw(chess_board_sprite);
        window->draw(board_sprite);

        if (!moveHints.empty()) {
            for (const auto& pos : moveHints) {
                valid_cell_sprite.setPosition(gridToPixel(pos.first, pos.second));
                window->draw(valid_cell_sprite);
            }
        }
        
        if (!killHints.empty()) {
            for (const auto& pos : killHints) {
                kill_cell_sprite.setPosition(gridToPixel(pos.first, pos.second));
                window->draw(kill_cell_sprite);
            }
        }
               

        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (grid[x][y]) {  // Si hay una pieza en esta casilla
                    grid[x][y]->draw(window);
                }
            }
        }

        window->draw(title);
        window->draw(turnText);
    }
}

bool Board::isValidPosition(int x, int y)
{
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

bool Board::isKingInCheck(Piece::PieceColor isWhite)
{
    int kingX = -1, kingY = -1;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (grid[x][y] && grid[x][y]->getType() == Piece::Type::KING && grid[x][y]->getColorSide() == isWhite) {
                kingX = x;
                kingY = y;
                break;
            }
        }
    }

    // Verificar si alguna pieza enemiga puede moverse a la casilla del rey
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (grid[x][y] && grid[x][y]->getColorSide() != isWhite) { // Pieza enemiga
                if (grid[x][y]->canMoveTo(x, y, kingX, kingY, grid)) {
                    return true; // �El rey est� en jaque!
                }
            }
        }
    }
    
    return false;
}

bool Board::isCheckmate(Piece::PieceColor isWhite)
{
    if (!isKingInCheck(isWhite)) {
        return false; // No est� en jaque, no es jaque mate
    }

    // Intentar mover el rey a una casilla segura
    int kingX = -1, kingY = -1;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (grid[x][y] && grid[x][y]->getType() == Piece::Type::KING && grid[x][y]->getColorSide() == isWhite) {
                kingX = x;
                kingY = y;
                break;
            }
        }
    }

    // Revisar si el rey tiene movimientos v�lidos
    int moves[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

    for (auto& move : moves) {
        int newX = kingX + move[0];
        int newY = kingY + move[1];

        if (isValidPosition(newX, newY) && (!grid[newX][newY] || grid[newX][newY]->getColorSide() != isWhite)) {
            // Simular movimiento del rey
            std::unique_ptr<Piece> temp = std::move(grid[newX][newY]);
            grid[newX][newY] = std::move(grid[kingX][kingY]);
            grid[kingX][kingY] = nullptr;

            bool stillInCheck = isKingInCheck(isWhite);

            // Deshacer movimiento
            grid[kingX][kingY] = std::move(grid[newX][newY]);
            grid[newX][newY] = std::move(temp);

            if (!stillInCheck) {
                return false; // El rey puede escapar
            }
        }
    }

    return true;
}

void Board::checkGameState()
{
    if (isCheckmate(Piece::PieceColor::WHITE)) {
        std::cout << "�Checkmate! Black wins." << std::endl;
        resetGame();
    }
    else if (isCheckmate(Piece::PieceColor::BLACK)) {
        std::cout << "�Checkmate! White wins." << std::endl;
        resetGame();
    }
    else if (isKingInCheck(Piece::PieceColor::WHITE)) {
        std::cout << "�Whites are in check!" << std::endl;
    }
    else if (isKingInCheck(Piece::PieceColor::BLACK)) {
        std::cout << "�Blacks are in check!" << std::endl;
    }
}
