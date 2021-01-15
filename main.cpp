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
    Move move{};
    std::cout << "What is your move?\n";
    std::cout << "Row: ";
    std::cin >> move.x;
    std::cout << "Col: ";
    std::cin >> move.y;
    return move;
}

bool isMoveValid(const Move& move, const Board& board) {
    if (move.x >= 0 && move.x < board.size() &&
        move.y >= 0 && move.y < board.size() &&
        board[move.x][move.y] == ' ') {
        return true;
    }
    return false;
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

bool isGameEnd(const Board& board) {
    return board[0][0] != ' ' && board[0][0] == board [0][1] && board [0][1] == board[0][2] ||
           board[1][0] != ' ' && board[1][0] == board [1][1] && board [1][1] == board[1][2] ||
           board[2][0] != ' ' && board[2][0] == board [2][1] && board [2][1] == board[2][2] ||

           board[0][0] != ' ' && board[0][0] == board [1][0] && board [1][0] == board[2][0] ||
           board[0][1] != ' ' && board[0][1] == board [1][1] && board [1][1] == board[2][1] ||
           board[0][2] != ' ' && board[0][2] == board [1][2] && board [1][2] == board[2][2] ||

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
