#include <iostream>
#include <cstring>
 using namespace std;

struct A{
    int i;
    int j;
};

class b {
    public:
        virtual int hello() = 0;
        int no(){
            cout << "adsf";
        }
};

class c : public b{
    public:
        int hello(){
            cout << "bomb";
        }
};

 int main(){
    string s = "hellp";
    const string b = "hellp";

    if(s == b){
        cout << "yoo";
    }
 }