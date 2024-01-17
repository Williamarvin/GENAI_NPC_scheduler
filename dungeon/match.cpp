#include "match.h"

bool Match::outOfBound(int row, int col) const {
    // Task 4.1: Check whether a given position is out of bound.
    if(row >= BOARD_SIZE || col >= BOARD_SIZE || row < 0 || col < 0){
        return true;
    }
    return false;
}

bool Match::setPlayer(Player* p, int index){
    // Task 4.2: Set the player with the given index.
    // Case 1: Wrong index.
    if(index != 1 && index != 0){
        return false;
    }
    // Case 2: Player already exists.
    else if(players[index]){
        return false;
    }
    // Case 3: Out of bound or the position is already occupied.
    else if(outOfBound(p->row, p -> col) || board[p->row][p->col] != nullptr){
        return false;
    }
    // Case 4: Otherwise, the player can be set.
    else{
        players[index] = p;
        board[p->row][p->col] = p;
        return true;
    }
}

bool Match::addItem(Item* item, int row, int col){
    // Task 4.3: Add the item to the board.
    // Case 1: Out of bound or the position is already occupied.
    if(outOfBound(row, col) || board[row][col] != nullptr){
        return false;
    }
    // Case 2: Scan the whole board to check whether there exists any item with the same name.
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j] != nullptr){
                if(board[i][j]->getName() == item->getName()){
                    return false;
                }
            }
        }
    }
    // Case 3: Otherwise, the item can be added.
    delete board[row][col];
    board[row][col] = item;
    return true;
}

bool Match::move(char c){
    // Task 4.4: Move the player.
    if(c == 'w' || c == 'a' || c == 's' || c == 'd'){
        if(c == 'w' && outOfBound((players[curRound]->row - 1), players[curRound] -> col)){
            return false;
        }       
        else if(c == 'a' && outOfBound(players[curRound]->row, players[curRound] -> col - 1)){
            return false;
        }
        else if(c == 's' && outOfBound(players[curRound]->row + 1, players[curRound] -> col)){
            return false;
        }
        else if(c == 'd' && outOfBound(players[curRound]->row, players[curRound]->col + 1)){
            return false;
        }
        else{
            int newRow = players[curRound]->row;
            int newCol = players[curRound]->col;

            if(c == 'w'){
                players[curRound]->row -= 1;
            }
            else if(c == 'a'){
                players[curRound] -> col -= 1;
            }
            else if(c == 's'){
                players[curRound] -> row += 1;
            }
            else if(c == 'd'){
                players[curRound] -> col += 1;
            }
            
            Item* inside = dynamic_cast<Item*>(board[players[curRound]->row][players[curRound] -> col]);
            Player* inside1 = dynamic_cast<Player*>(board[players[curRound]->row][players[curRound] -> col]);
            
            if(inside == nullptr){}
            else if(inside->getPieceType() == BOMB){
                players[curRound]->hp -= inside -> getDefaultPower();
                if(players[curRound] -> hp <= 0){
                    board[newRow][newCol] = nullptr;
                    board[players[curRound]->row][players[curRound] -> col] = players[curRound];
                    curRound = -1;
                    delete inside;
                    inside = nullptr;
                    return true;
                }
                delete inside;
            }
            else if(inside ->getPieceType() == DEFENSE_ITEM){
                DefenseItem* insideM = dynamic_cast<DefenseItem*>(inside);
                players[curRound] -> insertDefenseItem(insideM);
            }
            else if(inside -> getPieceType() == ATTACK_ITEM){
                AttackItem* insideM = dynamic_cast<AttackItem*>(inside);
                players[curRound] -> insertAttackItem(insideM);
            }
            
            if(inside1 != nullptr && inside1 -> getPieceType() == PLAYER){
                battle();
                return true;
            }
            board[newRow][newCol] = nullptr;
            board[players[curRound]->row][players[curRound] -> col] = players[curRound];

            if(curRound == 0){
                curRound = 1;
            }
            else{
                curRound = 0;
            }
            return true;
        }
    }

    else{
        return false;
    }
}

void Match::battle(){
    // Task 5.3: Battle when the two players meet.
    while(players[0]->hp > 0 && players[1]->hp > 0){
        if(players[0] -> attackItems.attack() == nullptr && players[1] -> attackItems.attack() == nullptr){
            break;
        }
        AttackItem* maxAttack = players[curRound]->attackItems.attack();
        int maxDefense = 0;
        DefenseItem* defensePointer = players[curRound ? 0 : 1]->defenseItems.defense(maxAttack, maxDefense);
        if(maxAttack == nullptr){
            printBattle(nullptr, nullptr);
        }

        else{
            int damage = max(maxAttack->getDefaultPower(), 0);
            if(defensePointer != nullptr){
                int remDmg = maxDefense - damage;
                if(remDmg < 0){
                    // reduce actual health
                    remDmg = -remDmg;
                    players[curRound ? 0 : 1] -> hp -= remDmg;
                    defensePointer -> reduceRemainingDefensePower(maxDefense);
                }
                else{
                    defensePointer -> reduceRemainingDefensePower(damage);
                }
            }
            else{
                players[curRound ? 0 : 1]->hp -= damage;
            }
            maxAttack -> decrementUsageTimes();
            
            printBattle(maxAttack, defensePointer);
        }

        curRound = curRound ? 0 : 1;
    }
    curRound = -1;
}