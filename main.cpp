#include <iostream>
#include <array>

using Board = std::array<std::array<char, 3>, 3>;
using Player = char;

struct Move {
    int x;
    int y;
};

void init(Board& board)
{
    for (auto& col : board) {
        for (auto& elem : col) {
            elem = ' ';
        }
    }
}

void print(const Board& board)
{
    const std::string verticalSeparator {"\n-------------------------\n"};
    std::cout << verticalSeparator;
    for (auto col : board) {
        std::cout << "|";
        for (auto elem : col) {
            std::cout << "\t"<< elem << "\t|";
        }
        std::cout << verticalSeparator;
    }
}

Move getPlayerMove() {
    Move move;
    std::cout << "What is your move?\n";
    std::cout << "Row: ";
    std::cin >> move.x;
    std::cout << "Col: ";
    std::cin >> move.y;
    return move;
}

bool isMoveValid(const Move& move, const Board& board) {
    try {
        return board.at(move.x).at(move.y) == ' ';
    } catch (const std::out_of_range&) {
        return false;
    }
}

void makeMove(const Move& move, Board& board, const Player player) {
    board.at(move.x).at(move.y) = player;
}

Player switchPlayers(const Player player)
{
    const Player p1 = 'X';
    const Player p2 = 'O';

    if (player == p1) {
        return p2;
    }
    return p1;
}

bool isWinAtRow(const Board& board, uint row)
{
    bool isWin = true;
    for (int i = 0; i < board.size() - 1; i++) {
        isWin &= board.at(row)[i] != ' ' && board.at(row)[i] == board.at(row)[i + 1];
        if (not isWin) {
            break;
        }
    }
    return isWin;
}

bool isWinAtCol(const Board& board, uint col)
{
    bool isWin = true;
    for (int i = 0; i < board.size() - 1; i++) {
        isWin &= board[i].at(col) != ' ' && board[i].at(col) == board[i + 1].at(col);
        if (not isWin) {
            break;
        }
    }
    return isWin;
}

bool isGameEnd(const Board& board) {
    return isWinAtRow(board, 0) ||
           isWinAtRow(board, 1) ||
           isWinAtRow(board, 2) ||

           isWinAtCol(board, 0) ||
           isWinAtCol(board, 1) ||
           isWinAtCol(board, 2) ||

           board[0][0] != ' ' && board[0][0] == board [1][1] && board [1][1] == board[2][2] ||
           board[0][2] != ' ' && board[0][2] == board [1][1] && board [1][1] == board[2][0];
}

int main() {
    Board board{};
    init(board);
    print(board);

    Player currentPlayer;

    while(not isGameEnd(board)) {
        currentPlayer = switchPlayers(currentPlayer);
        Move move{};
        do {
            std::cout << "Player move: " << currentPlayer << std::endl;
            move = getPlayerMove();
        }
        while (not isMoveValid(move, board));
        makeMove(move, board, currentPlayer);
        print(board);
    }
    std::cout << "Winner " << currentPlayer;

   return 0;
}
