#include "UserData.hpp"
#include <random>

UserData::UserData() {
    chosenCards = {0,1,2,3,4,5,9,10};
}
void UserData::initGame() {
    for (int i : chosenCards) {
        availableCards.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(availableCards.begin(), availableCards.end(), g);
    for (int i=0; i<4; i++) {
        nextCardQueue.push(availableCards.back());
        availableCards.pop_back();
    }
}