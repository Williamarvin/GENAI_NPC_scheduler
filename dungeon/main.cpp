#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "item.h"
#include "match.h"


void test1(){ // Sample test case for TODO #1
    cout << "----------------Begin of test 1----------------" << endl;
    Dictionary dictionary;
    dictionary.print();

    cout << "Insert attack items into the dictionary:" << endl;
    dictionary.insert("Axe", 30);
    dictionary.insert("Bow", 20);
    dictionary.insert("Bow", 40);
    dictionary.insert("Sword", 50);
    dictionary.insert("Crossbow", 30);
    dictionary.print();

    cout << "Find Bow in the Dictionary: " << dictionary.find("Bow") << endl;
    cout << "Find Spear in the Dictionary: " << dictionary.find("Spear") << endl;
    cout << "Find Crossbow in the Dictioanry: " << dictionary.find("Crossbow") << endl;
    cout << "----------------End of test 1----------------" << endl;
    return;
}

void test2(){ // Sample test case for TODO #1 ~ 2
    cout << "----------------Begin of test 2----------------" << endl;
    Item bomb1("Bomb 1", '*', BOMB, 500);
    Item bomb2("Bomb 2", '*', BOMB, 300);
    bomb1.print();
    bomb2.print();

    AttackItem sword("Sword", 'S', 300, 3);
    AttackItem bow("Bow", 'B', 100, 8);
    sword.print();
    bow.print();

    DefenseItem shield("Shield", 'O', 20, 80);
    shield.insertDefensePair("Sword", 50);
    shield.insertDefensePair("Axe", 30);
    DefenseItem armor("Armor", 'R', 30, 70);
    armor.insertDefensePair("Gun", 40);
    armor.insertDefensePair("Bow", 50);
    shield.print();
    armor.print();
    cout << "----------------End of test 2----------------" << endl;
    return;
}

void test3(){ // Sample test case for TODO #2 ~ 3
    cout << "----------------Begin of test 3----------------" << endl;
    ItemsArray itemsArray;
    AttackItem* sword = new AttackItem("Sword", 'S', 300, 3);
    AttackItem* bow = new AttackItem("Bow", 'G', 100, 8);
    AttackItem* gun = new AttackItem("Bow", 'B', 400, 2);
    AttackItem* axe = new AttackItem("Axes", 'A', 200, 4);
    if(!itemsArray.insert(sword)) delete sword;
    if(!itemsArray.insert(bow)) delete bow;
    if(!itemsArray.insert(gun)) delete gun;
    if(!itemsArray.insert(axe)) delete axe;
    cout << "Items Array:" << endl;
    itemsArray.print();

    if(itemsArray.find("Bow"))
        cout << "Bow is in the Items Array." << endl;
    else
        cout << "Bow is not in the Items Array." << endl;
    if(itemsArray.find("Crossbow"))
        cout << "Crossbow is in the Items Array." << endl;
    else
        cout << "Crossbow is not in the Items Array." << endl;
    cout << "----------------End of test 3----------------" << endl;
    return;
}

void test4(){ // Sample test case for TODO #1 ~ 3
    cout << "----------------Begin of test 4----------------" << endl;
    Player player1("Apple", '1', 0, 0);
    AttackItem* axe = new AttackItem("Axe", 'A', 200, 4);
    AttackItem* axe1 = new AttackItem("Axe", 'S', 300, 3);
    AttackItem* bow = new AttackItem("Bow", 'B', 100, 8);
    AttackItem* gun = new AttackItem("Gun", 'G', 400, 2);
    if(!player1.insertAttackItem(axe)) delete axe;
    if(!player1.insertAttackItem(axe1)) delete axe1;
    if(!player1.insertAttackItem(bow)) delete bow;
    if(!player1.insertAttackItem(gun)) delete gun;
    DefenseItem* shield = new DefenseItem("Shield", 'O', 40, 70);
    shield->insertDefensePair("Sword", 50);
    shield->insertDefensePair("Axe", 60);
    DefenseItem* armor = new DefenseItem("Armor", 'R', 40, 80);
    armor->insertDefensePair("Gun", 50);
    armor->insertDefensePair("Bow", 50);
    if(!player1.insertDefenseItem(shield)) delete shield;
    if(!player1.insertDefenseItem(armor)) delete armor;
    player1.print();
    cout << "----------------End of test 4----------------" << endl;
    return;
}

void test5(){ // Sample test case for TODO #1 ~ 4
    cout << "----------------Begin of test 5----------------" << endl;
    Match match;

    Player* p1 = new Player("Apple", '1', 0, 0);
    if(!match.setPlayer(p1, 0)) delete p1;
    Player* p2 = new Player("Orange", '2', 6, 5);
    if(!match.setPlayer(p2, 1)) delete p2;
    Player* p3 = new Player("Banana", '2', 6, 6);
    if(!match.setPlayer(p3, 1)) delete p3;
    
    AttackItem* sword = new AttackItem("Sword", 'S', 300, 3);
    if(!match.addItem(sword, 3, 5)) delete sword;
    AttackItem* bow = new AttackItem("Bow", 'B', 100, 8);
    if(!match.addItem(bow, 3, 2)) delete bow;
    AttackItem* gun = new AttackItem("Gun", 'G', 400, 2);
    if(!match.addItem(gun, 3, 0)) delete gun;
    AttackItem* axe = new AttackItem("Axe", 'A', 200, 4);
    if(!match.addItem(axe, 2, 6)) delete axe;
    AttackItem* axe1 = new AttackItem("Axe", 'X', 200, 4);
    if(!match.addItem(axe1, 5, 6)) delete axe1;

    DefenseItem* shield = new DefenseItem("Shield", 'O', 10, 100);
    shield->insertDefensePair("Sword", 20);
    shield->insertDefensePair("Axe", 30);
    if(!match.addItem(shield, 2, 1)) delete shield;
    DefenseItem* armor = new DefenseItem("Armor", 'R', 10, 70);
    armor->insertDefensePair("Gun", 20);
    armor->insertDefensePair("Bow", 15);
    if(!match.addItem(armor, 4, 6)) delete armor;

    Item* bomb1 = new Item("Bomb1", '*', BOMB, 500);
    if(!match.addItem(bomb1, 5, 6)) delete bomb1;
    Item* bomb2 = new Item("Bomb2", '*', BOMB, 500);
    if(!match.addItem(bomb2, 1, 0)) delete bomb2;

    match.play();
    cout << endl;
    match.printPiece(2, 1);
    cout << endl;
    match.printPiece(2, 6);
    cout << endl;
    match.printPiece(1, 0);
    cout << endl;
    match.printPiece(3, 0);
    cout << endl;
    cout << "----------------End of test 5----------------" << endl;
    return;
}

void test6(){ // Sample test case for TODO #1 ~ 4
    cout << "----------------Begin of test 6----------------" << endl;
    Match match;

    Player* p1 = new Player("Apple", '1', 0, 0);
    if(!match.setPlayer(p1, 0)) delete p1;
    Player* p2 = new Player("Orange", '2', 6, 5);
    if(!match.setPlayer(p2, 1)) delete p2;

    Item* bomb1 = new Item("Bomb1", '*', BOMB, 500);
    if(!match.addItem(bomb1, 5, 6)) delete bomb1;
    Item* bomb2 = new Item("Bomb2", '*', BOMB, 5000);
    if(!match.addItem(bomb2, 1, 0)) delete bomb2;

    match.play();
    cout << "----------------End of test 6----------------" << endl;
    return;
}

void test7(){ // Sample test case for TODO #1 ~ 5
    cout << "----------------Begin of test 7----------------" << endl;
    Match match;

    Player* p1 = new Player("Apple", '1', 0, 0);
    if(!match.setPlayer(p1, 0)) delete p1;
    Player* p2 = new Player("Banana", '2', 6, 6);
    if(!match.setPlayer(p2, 1)) delete p2;

    AttackItem* sword = new AttackItem("Sword", 'S', 300, 3);
    AttackItem* bow = new AttackItem("Bow", 'B', 110, 8);
    AttackItem* gun = new AttackItem("Gun", 'G', 400, 2);
    if(!p1->insertAttackItem(sword)) delete sword;
    if(!p1->insertAttackItem(bow)) delete bow;
    if(!p1->insertAttackItem(gun)) delete gun;
    DefenseItem* shield = new DefenseItem("Shield", 'O', 500, 580);
    shield->insertDefensePair("Crossbow", 520);
    shield->insertDefensePair("Axe", 530);
    if(!p1->insertDefenseItem(shield)) delete shield;
    DefenseItem* armor = new DefenseItem("Armor", 'R', 10, 120);
    armor->insertDefensePair("Axe", 20);
    armor->insertDefensePair("Spear", 25);
    if(!p1->insertDefenseItem(armor)) delete armor;

    AttackItem* axe = new AttackItem("Axe", 'A', 200, 4);
    AttackItem* spear = new AttackItem("Spear", 'P', 300, 3);
    AttackItem* crossbow = new AttackItem("Crossbow", 'C', 150, 5);
    if(!p2->insertAttackItem(axe)) delete axe;
    if(!p2->insertAttackItem(spear)) delete spear;
    if(!p2->insertAttackItem(crossbow)) delete crossbow;
    DefenseItem* helmet = new DefenseItem("Helmet", 'O', 15, 50);
    helmet->insertDefensePair("Sword", 20);
    helmet->insertDefensePair("Bow", 30);
    if(!p2->insertDefenseItem(helmet)) delete helmet;
    DefenseItem* superShield = new DefenseItem("Super Shield", 'R', 600, 700);
    superShield->insertDefensePair("Gun", 610);
    superShield->insertDefensePair("Sword", 630);
    if(!p2->insertDefenseItem(superShield)) delete superShield;

    match.battle();
    cout << "----------------End of test 7----------------" << endl;
    return;
}

void test8(string file){ // Sample test case for TODO #1 ~ 5
    cout << "----------------Begin of test 8----------------" << endl;
    Match match;

    Player* p1 = new Player("Apple", '1', 0, 0);
    if(!match.setPlayer(p1, 0)) delete p1;
    Player* p2 = new Player("Banana", '2', 6, 6);
    if(!match.setPlayer(p2, 1)) delete p2;

    AttackItem* sword = new AttackItem("Sword", 'S', 300, 3);
    if(!match.addItem(sword, 3, 5)) delete sword;
    AttackItem* bow = new AttackItem("Bow", 'B', 110, 8);
    if(!match.addItem(bow, 3, 2)) delete bow;
    AttackItem* gun = new AttackItem("Gun", 'G', 400, 2);
    if(!match.addItem(gun, 3, 0)) delete gun;
    AttackItem* axe = new AttackItem("Axe", 'A', 200, 4);
    if(!match.addItem(axe, 2, 4)) delete axe;

    DefenseItem* shield1 = new DefenseItem("Shield", 'O', 15, 100);
    shield1->insertDefensePair("Sword", 20);
    shield1->insertDefensePair("Axe", 30);
    if(!match.addItem(shield1, 2, 3)) delete shield1;
    DefenseItem* shield2 = new DefenseItem("Shield", 'O', 20, 105);
    shield2->insertDefensePair("Gun", 30);
    shield2->insertDefensePair("Sword", 20);
    if(!match.addItem(shield2, 4, 6)) delete shield2;

    Item* bomb1 = new Item("Bomb1", '*', BOMB, 550);
    if(!match.addItem(bomb1, 5, 6)) delete bomb1;
    Item* bomb2 = new Item("Bomb2", '*', BOMB, 350);
    if(!match.addItem(bomb2, 1, 0)) delete bomb2;

    match.automated(file);
    cout << "----------------End of test 8----------------" << endl;
    return;
}


int main(int argc, char* argv[]){
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " --text <filename>" << std::endl;
        return 1;
    }

    std::string option = argv[1];
    std::string filename = argv[2];

    if (option != "--text") {
        std::cerr << "Invalid option. Use --text" << std::endl;
        return 1;
    }

    std::ifstream inputFile(filename);
    
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }
    
    std::ostringstream contentStream;
    std::string line;
    
    while (std::getline(inputFile, line)) {
        contentStream << line << '\n';
    }

    std::string fileContent = contentStream.str();

    // Your code to process the file content stored in 'fileContent' goes here
    // std::cout << "File content:\n" << fileContent << std::endl;

    test8(fileContent);

    // Your code to process the file goes here

    inputFile.close();
    return 0;
}
