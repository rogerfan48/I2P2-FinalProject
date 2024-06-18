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

    UserData();
    void initGame();
};

#endif // USERDATA_HPP