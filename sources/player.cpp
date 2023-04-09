#include "player.hpp"
#include <stdexcept>

using namespace std;
using namespace ariel;

Player::Player(const string name) : cards_won(0), stack_size(0)
{
    if (name == "")
    {
        throw invalid_argument("player must have a name");
    }
    this->player_name = name;
    id = getNextId();
};

int Player::cardesTaken()
{
    return this->cards_won;
}

int Player::stacksize()
{
    return this->stack_size;
}

void Player::addWin(int num)
{
    this->cards_won += num;
    // if he wins he gets his own card and the other player card
}

void Player::setStackSize(int size)
{
    this->stack_size = size;
}
string Player::getPlayerName()
{
    return this->player_name;
}

int Player::getid()
{
    return this->id;
}