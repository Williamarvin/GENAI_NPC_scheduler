#include "array.h"

bool ItemsArray::find(const string &name) const{
    // Task 3.1: Find an item in the ItemsArray.
    for(int i = 0; i < arraySize; i++){
        if(items[i]->getName() == name){
            return true;
        }
    }
    return false;
}

bool ItemsArray::insert(Item* item) {
    // Task 3.2: Insert an item into the ItemsArray.
    if (find(item->getName())) {
        return false;
    } 
    else {
        Item** newItem = new Item*[arraySize + 1];
        int j = 0;
        bool inserted = false;

        for (int i = 0; i < arraySize; i++) {
            if (!inserted && items[i]->getDefaultPower() < item->getDefaultPower()) {
                newItem[j] = item;
                inserted = true;
                j++;
            }
            newItem[j] = items[i];
            j++;
        }

        if (!inserted) {
            newItem[arraySize] = item;
        }

        if (items != nullptr) {
            delete[] items;
        }

        items = newItem;
        newItem = nullptr;
        arraySize += 1;

        return true;
    }
}

AttackItem* AttackItemsArray::attack(){
    // Task 5.1: Choose the most powerful attack item.
    for(int i = 0; i < arraySize; i++){
        AttackItem* attack = dynamic_cast<AttackItem*>(items[i]);
        if(attack){
            if(attack->usable()){
                return attack;
            }
        }
    }   
    return nullptr;
}

DefenseItem* DefenseItemsArray::defense(AttackItem* attackItem, int& defense_power){
    // Task 5.2: Choose the best defending item.
    int maxDefense = 0;
    int j = 0;
    bool found = false;
    for(int i = 0; i < arraySize; i++){
        DefenseItem* defense = dynamic_cast<DefenseItem*>(items[i]);

        if(defense != nullptr){
            if(attackItem != nullptr && defense -> getDefensePair()->find(attackItem -> getName()) != NULL_VALUE){
                if(min(max(defense -> getDefensePair()->find(attackItem->getName()), defense->getDefaultPower()), defense -> getRemainingDefensePower()) > maxDefense){
                    maxDefense = max(min(max(defense -> getDefensePair()->find(attackItem->getName()), defense->getDefaultPower()), defense -> getRemainingDefensePower()), maxDefense);
                    defense_power = maxDefense;
                    j = i;
                    found = true;
                } 
            }
            else{
                if(maxDefense < min(max(0, defense->getDefaultPower()), defense->getRemainingDefensePower())){
                    maxDefense = max(min(max(0, defense->getDefaultPower()), defense->getRemainingDefensePower()), maxDefense);
                    defense_power = maxDefense;
                    j = i;
                    found = true;
                }
            }
        }
    }
    if(!found){return nullptr;}
    DefenseItem* defense = dynamic_cast<DefenseItem*>(items[j]);
    return defense;
}