#include "dictionary.h"

Dictionary::Dictionary(){
    // Task 1.1: Implement the constructor of Dictionary.
    dataPairs = nullptr;
    arraySize = 0;
}

Dictionary::~Dictionary(){
    // Task 1.2: Implement the destructor of Dictionary.
    delete []dataPairs;
};

int Dictionary::find(const string &key) const{
    // Task 1.3: Search a given key from the Dictionary.
    for(int i = 0; i < arraySize; i++){
        if(dataPairs[i].key == key){
            return dataPairs[i].value;
        }
    }
    return NULL_VALUE;
};

bool Dictionary::insert(const string &key, int value){
    // Task 1.4: Insert a given pair into the Dictionary.
    if(find(key) != NULL_VALUE){
        return false;
    }

    DataPair* newPair = new DataPair[arraySize + 1]{"",0};

    for(int i = 0; i < arraySize; i++){
        newPair[i].key = dataPairs[i].key;
        newPair[i].value = dataPairs[i].value;
    }
    newPair[arraySize].key = key;
    newPair[arraySize].value = value;

    if(dataPairs != nullptr){
        delete []dataPairs;
    }

    dataPairs = newPair;
    arraySize += 1;

    return true;
}
