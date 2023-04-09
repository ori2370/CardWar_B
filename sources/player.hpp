#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "card.hpp"
#include <string>
using namespace std;
namespace ariel
{
    class Player
    {
    private:
        bool winner = false;
        int cards_won;
        int stack_size;
        string player_name;
        int id;
        static const int next_id = 0;

        static int getNextId()
        {
            static int player_id = next_id;
            return player_id++;
        }

    public:
        Player(string name);
        int cardesTaken();
        int stacksize();
        void addWin(int num);
        void setStackSize(int size);
        string getPlayerName();
        int getid();
        void decreaseStackSize() { this->stack_size--; }
        void setWinner() { this->winner = true; }
        bool isWinner() const { return this->winner; }
    };
}
#endif
