#ifndef GAMESIMULATOR_HPP
#define GAMESIMULATOR_HPP
#include "card.hpp"
#include "player.hpp"
#include <string>

using namespace std;
namespace ariel
{
    class gameSimulator
    {
    public:
        gameSimulator(){};
        string playTurn(const Card &card1, const Card &card2);
    };
}

#endif