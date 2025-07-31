/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

enum class PIECES {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

enum class COLORS {
  BLACK,
  WHITE
};

enum class PLAYERS {
    BLACK,
    WHITE
};

class MovementStrategy {
  public:
  virtual bool isValidMove(int sr, int sc, int dr, int dc) = 0;
};

class QueenMovementStrategy: public MovementStrategy {
    public:
    virtual bool isValidMove(int sr, int sc, int dr, int dc){
        if(sr == sc and dr == dc) return false;
        if(sr == sc) return true;
        if(dc == dc) return true;
        // if(same diagonal) return true;
        // if(same anitdiagonal) return true;
        return false;
    }
};

// todo -> other movement strategies

class MovementStrategyFactory {
    public:
    static MovementStrategy* createStrategy(PIECES piece){
        if(piece == PIECES::QUEEN){
            return new QueenMovementStrategy();
        }
        // todo create other strategies
    }
};

class ChessPiece {
private:
    PIECES type;
    MovementStrategy* strategy;
    COLORS color;
public:
    ChessPiece(PIECES type, MovementStrategy* strategy, COLORS color): type(type), strategy(strategy), color(color) {}
};

class QueenPiece : public ChessPiece {
    public:
    QueenPiece(COLORS color): ChessPiece(PIECES::QUEEN, MovementStrategyFactory::createStrategy(PIECES::QUEEN), color) {}
};

class GameBoard {
private:
    static GameBoard* instance;
    static map<pair<int,int>,ChessPiece*> boardState;
    GameBoard() {}
public:
    static GameBoard* getInstance(){
        if(instance == nullptr){ // TODO: make this thread safe -> dpuble check locking
            instance = new GameBoard();
            boardState[{0,3}] = new QueenPiece(COLORS::WHITE);
            boardState[{7,3}] = new QueenPiece(COLORS::BLACK);
            
            // TODO - initialise other pieces
        }
        return instance;
    }
    bool validateMove(PLAYERS player, int sr, int sc, int dr, int dc){
        // basic validation
        // does a piece exist at sr and sc -> if not return false;
        // if player not allowed to touch piece return false
        // if(piece.strategy.isValidMove) return true;
    }
    ChessPiece* executeMove(int sr, int sc, int dr, int dc){
        // actually executes the Move
        // returns piece killed if any othersise return false
    }
    bool isKingUnderAttack(){
        // check if any king is under attack -> if yes, game over
    }
};

GameBoard* GameBoard::instance = nullptr;

int main(){
    
    return 0;
}