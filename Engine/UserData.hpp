#ifndef USERDATA_HPP
#define USERDATA_HPP

#include <vector>
#include <set>
#include <queue>

class UserData {
public:
    std::set<int> chosenCards;
    std::vector<int> availableCards;
    std::queue<int> nextCardQueue;
    float elixir;
    int selectedCard;

    UserData();
    void initGame();
};

#endif // USERDATA_HPP