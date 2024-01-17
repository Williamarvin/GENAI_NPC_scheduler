#ifndef __MATCH_H__
#define __MATCH_H__
#include <iostream>
#include <string>
using namespace std;
#include "player.h"

const int BOARD_SIZE = 7;

class Match{
    public:
        Match() : curRound{0}, players{}, board{} { }
        ~Match(){
            for(int i = 0; i < BOARD_SIZE; ++i){
                for(int j = 0; j < BOARD_SIZE; ++j){
                    if(board[i][j] != nullptr)
                        delete board[i][j];
                }
            }
        }
        int getCurRound() const {return curRound;}

        bool outOfBound(int row, int col) const;
        bool setPlayer(Player* p, int index);
        bool addItem(Item* item, int row, int col);
        bool move(char c);
        void battle();

        void automated(string filename){
            while(curRound == 0 || curRound == 1){
                print();
                char c;

                for(int i = 0; i < filename.size(); i++){
                    c = filename[i];
                    if(c == 'q')
                        return;
                    if(!move(c))
                        cout << "INVALID MOVE" << endl;
                    print();
                }
                
            }
                if(players[0]->hp > players[1]->hp)
                    cout << players[0]->name << " wins." << endl;
                else if(players[1]->hp > players[0]->hp)
                    cout << players[1]->name << " wins." << endl;
                else
                    cout << "Tie." << endl;        
        }

        void play(){
            while(curRound == 0 || curRound == 1){
                print();
                char c;
                cout << players[curRound]->name << "'s move: " << endl;
                cin >> c;
                if(c == 'q')
                    return;
                if(!move(c))
                    cout << "INVALID MOVE" << endl;
            }
            if(players[0]->hp > players[1]->hp)
                cout << players[0]->name << " wins." << endl;
            else if(players[1]->hp > players[0]->hp)
                cout << players[1]->name << " wins." << endl;
            else
                cout << "Tie." << endl;
        }
        void printPiece(int row, int col) const{
            cout << "Piece(" << row << ", " << col << "):" << endl;
            if(outOfBound(row, col))
                cout << "Out of Bounds" << endl;
            else if(board[row][col] == nullptr)
                cout << "Empty Piece" << endl;
            else
                board[row][col]->print();
        }
        void printBattle(AttackItem* attackItem, DefenseItem* defenseItem) const{
            if(attackItem == nullptr)
                cout <<  players[curRound]->name << " does not attack." << endl;
            else{
                cout << players[curRound]->name << " attacks with " << attackItem->getName() << ", ";
                if(defenseItem == nullptr)
                    cout <<  players[(curRound + 1) % 2]->name << " does not defend." << endl;
                else
                    cout << players[(curRound + 1) % 2]->name << " defends with " << defenseItem->getName() << endl;
            }
            cout << players[0]->name << ": " << players[0]->hp << ", "<< players[1]->name << ": " << players[1]->hp << endl;
        }
        void print() const{
            for(int i = 0; i < BOARD_SIZE; ++i){
                for(int j = 0; j < BOARD_SIZE; ++j){
                    if(board[i][j])
                        cout << board[i][j]->getSymbol() << " ";
                    else
                        cout << "- ";
                }
                cout << endl;
            }
        }
    private:
        int curRound;
        Player* players[2];
        Piece* board[BOARD_SIZE][BOARD_SIZE];
};

#endif // __MATCH_H__