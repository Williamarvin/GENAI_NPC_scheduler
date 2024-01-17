#ifndef __ARRAY_H__
#define __ARRAY_H__
#include <iostream>
#include <string>
using namespace std;
#include "item.h"

class ItemsArray{
    public:
        ItemsArray() : arraySize(0), items(nullptr) {}
        ~ItemsArray(){
            if(arraySize > 0){
                for(int i = 0; i < arraySize; ++i)
                    delete items[i];
                delete [] items;
            }
        }
        bool find(const string &name) const;
        bool insert(Item* item);
        void print() const{
            if(arraySize == 0)
                cout << "   No items in the ItemsArray." << endl;
            else{
                for(int i = 0; i < arraySize; ++i){
                    cout << "   ";
                    items[i]->print();
                }
            }
        }
    protected:
        int arraySize;
        Item** items;
};

class AttackItemsArray : public ItemsArray{
    public:
        AttackItemsArray(){}
        ~AttackItemsArray(){}
        AttackItem* attack();
};

class DefenseItemsArray : public ItemsArray{
    public:
        DefenseItemsArray(){}
        ~DefenseItemsArray(){}
        DefenseItem* defense(AttackItem* attackItem, int& defense_power);
};

#endif // __ARRAY_H__