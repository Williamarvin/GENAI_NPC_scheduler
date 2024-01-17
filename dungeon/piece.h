#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>
#include <string>
using namespace std;

enum PieceType{
    PLAYER,
    ATTACK_ITEM,
    DEFENSE_ITEM,
    BOMB
};

class Piece{
    public:
        Piece(const string &name, char symbol, PieceType pieceType) : name(name), symbol(symbol), pieceType(pieceType) {}
        virtual ~Piece(){}
        virtual void print() const = 0;
        string getName() const {return name;}
        PieceType getPieceType() const {return pieceType;}
        char getSymbol() const {return symbol;}
    protected:
        const string name;
        const char symbol;
        const PieceType pieceType;
};

#endif // __PIECE_H__