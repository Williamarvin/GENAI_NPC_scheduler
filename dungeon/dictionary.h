#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__
#include <iostream>
#include <string>
using namespace std;

struct DataPair{
    string key;
    int value;
};

const int NULL_VALUE = -1;
// NULL_VALUE is returned when the key is not found in the Dictionary

class Dictionary{
    public:
        Dictionary();
        ~Dictionary();
        int find(const string &key) const;
        bool insert(const string &key, int value);
        void print() const{
            if(arraySize == 0){
                cout << "No data pairs in the Dictionary." << endl;
                return;
            }
            for(int i = 0; i < arraySize; ++i)
                cout << dataPairs[i].key << ": " << dataPairs[i].value << ' ';
            cout << endl;
        }
    private:
        int arraySize;
        DataPair* dataPairs;
};

#endif // __DICTIONARY_H__