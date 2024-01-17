#ifndef __ITEM_H__
#define __ITEM_H__
#include <iostream>
#include <string>
#include "piece.h"
#include "dictionary.h"
using namespace std;

class Item : public Piece{
    public:
        Item(const string &name, char symbol, PieceType pieceType, int defaultPower);
        virtual ~Item(){}
        int getDefaultPower() const {return defaultPower;}
        virtual void print() const {cout << symbol << ": " << name << " (" << defaultPower << ")" << endl;}
    protected:
        const int defaultPower;
};

class AttackItem : public Item{
    public:
        AttackItem(const string &name, char symbol, int defaultPower, int usageTimes);
        virtual ~AttackItem(){}
        void decrementUsageTimes() {--usageTimes;}
        bool usable() const {return (usageTimes > 0);}
        virtual void print() const {cout << symbol << ": " << name << " (" << defaultPower << "), " << usageTimes << " times left." << endl;}
    private:
        int usageTimes;
};

class DefenseItem : public Item{
    public:
        DefenseItem(const string &name, char symbol, int defaultPower, int remainingDefensePower);
        virtual ~DefenseItem(){}
        bool insertDefensePair(const string &key, int value) {return defensePair.insert(key, value);}
        void reduceRemainingDefensePower(int d) {remainingDefensePower -= d;}
        int getRemainingDefensePower() const {return remainingDefensePower;}
        Dictionary* getDefensePair() {return &defensePair;}
        virtual void print() const {
            cout << symbol << ": " << name << " (" << defaultPower << "), " << remainingDefensePower << " power left." << endl;
            cout << "   Defense Pairs: ";
            defensePair.print();
        }
    private:
        int remainingDefensePower;
        Dictionary defensePair;
};



#endif // __ITEM_H__