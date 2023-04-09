#ifndef GAME_HPP
#define GAME_HPP
#include "player.hpp"
#include "gameSimulator.hpp"
#include "card.hpp"
#include <string>
#include <vector>

using namespace std;
namespace ariel
{

    class Game
    {
    private:
        Player &player1;
        Player &player2;
        string last_turn_result;
        gameSimulator turn_oprator;
        vector<string> turn_results;
        vector<Card> card_deck;
        vector<Card> p1_stack;
        vector<Card> p2_stack;
        int p1_wins, p2_wins, players_draws;
        string playdraw();
        bool canPlayDraw();
        bool gameOver();
        // using player& so it wont create a copy of the players or allocating a new memory for them.
    public:
        Game(Player &player1, Player &player2); // same goes here..
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        void mixCards();
        void decreaseDeckSize();
    };
}

#endif