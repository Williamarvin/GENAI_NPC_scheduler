#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
using namespace std;
#include "piece.h"
#include "array.h"

const int DEFAULT_HP = 2000;

class Player : public Piece{
    public:
        Player(const string &name, char symbol, int row, int col) : Piece(name, symbol, PLAYER), hp(DEFAULT_HP), row(row), col(col), attackItems(), defenseItems() {}
        virtual ~Player(){}
        bool insertAttackItem(AttackItem* item) {return attackItems.insert(item);}
        bool insertDefenseItem(DefenseItem* item) {return defenseItems.insert(item);}
        AttackItem* attack() {return attackItems.attack();}
        DefenseItem* defense(AttackItem* attackItem, int& defense_power) {return defenseItems.defense(attackItem, defense_power);}
        virtual void print() const {
            cout << symbol << ": " << name << " (" << hp << ")" << endl;
            cout << name << "'s Attack Items:" << endl;
            attackItems.print(); 
            cout << name << "'s Defense Items:" << endl;
            defenseItems.print();
        }
        friend class Match;
    private:
        int hp;
        int row, col;
        AttackItemsArray attackItems;
        DefenseItemsArray defenseItems;
};

#endif // __PLAYER_H__