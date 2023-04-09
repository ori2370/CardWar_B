#include "game.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
using namespace std;
using namespace ariel;

Game::Game(Player &p1, Player &p2) : player1(p1), player2(p2), p1_wins(0), p2_wins(0), players_draws(0), turn_oprator()
{
    // if (p1.getid() == p2.getid())
    // { // checking by unique if and not name as two persons can have the same name
    //     throw invalid_argument("players cannot play himself");
    // }
    for (int i = 1; i <= 13; i++)
    {
        card_deck.push_back(Card(i, "hearts"));
        card_deck.push_back(Card(i, "clubs"));
        card_deck.push_back(Card(i, "spades"));
        card_deck.push_back(Card(i, "diamonds"));
    }
    mixCards();

    for (int i = 0; i < 26; i++)
    {
        p1_stack.push_back(card_deck.back());
        card_deck.pop_back();
        p2_stack.push_back(card_deck.back());
        card_deck.pop_back();
    }
    p1.setStackSize(p1_stack.size());
    p2.setStackSize(p2_stack.size());
}
// took the mixing cards method from this https://www.techiedelight.com/shuffle-vector-cpp/
// from the website above: 3. Using Fisher-Yates Shuffle Algorithm
void Game::mixCards()
{
    srand(time(NULL));
    unsigned int n = card_deck.size();
    unsigned int i = 0;
    for (i = 0; i < n - 1; i++)
    {
        unsigned int j = i + static_cast<unsigned int>(rand()) % (n - i);
        swap(card_deck[i], card_deck[j]);
    }
}

void Game::playTurn()
{
    if (player1.getid() == player2.getid())
    { // checking by unique if and not name as two persons can have the same name
        throw invalid_argument("players cannot play himself");
    }
    if (gameOver())
    {
        throw runtime_error("cant play turn, game is over");
    }
    string turn_result = turn_oprator.playTurn(p1_stack.back(), p2_stack.back());

    if (turn_result == "p1")
    {
        last_turn_result = "" + player1.getPlayerName() + " played " + p1_stack.back().toString() + " " + player2.getPlayerName() + " played " + p2_stack.back().toString() + ". " + player1.getPlayerName() + " wins.";
        player1.addWin(2);
        p1_wins++;
        decreaseDeckSize();
        turn_results.push_back(last_turn_result);
    }
    else if (turn_result == "p2")
    {
        last_turn_result = "" + player1.getPlayerName() + " played " + p1_stack.back().toString() + " " + player2.getPlayerName() + " played " + p2_stack.back().toString() + ". " + player2.getPlayerName() + " wins.";
        player2.addWin(2);
        p2_wins++;
        decreaseDeckSize();
        turn_results.push_back(last_turn_result);
    }
    else
    {
        string draw_result = "" + player1.getPlayerName() + " played " + p1_stack.back().toString() + " " + player2.getPlayerName() + " played " + p2_stack.back().toString() + ". draw. ";
        try
        {
            string playdraw_result = playdraw();
            last_turn_result = draw_result + " " + playdraw_result;
            turn_results.push_back(last_turn_result);
        }
        catch (const runtime_error &e)
        {

            cout << e.what() << endl;
            last_turn_result = draw_result + " " + e.what();
            turn_results.push_back(last_turn_result);
            return;
        }
    }
}
string Game::playdraw()
{
    players_draws++;
    bool drawable = canPlayDraw();
    if (!drawable)
    {
        decreaseDeckSize();
        player1.addWin(1);
        player2.addWin(1);
        throw runtime_error("turn skipped, cant play draw with less than 2 cards");
    }
    vector<Card> p1_draw_stack;
    vector<Card> p2_draw_stack;
    // saving the cards from last turn- where the draw occured
    p1_draw_stack.push_back(p1_stack.back());
    p2_draw_stack.push_back(p2_stack.back());
    decreaseDeckSize();
    // burning one card and saving it incase of uncompleted draw
    p1_draw_stack.push_back(p1_stack.back());
    p2_draw_stack.push_back(p2_stack.back());
    decreaseDeckSize();
    string result = "";
    string draw_result = turn_oprator.playTurn(p1_stack.back(), p2_stack.back());
    // while theres still draw and enough cards to play draw
    while (draw_result == "draw" && drawable)
    {
        // saving the cards from last turn- where the draw occured
        p1_draw_stack.push_back(p1_stack.back());
        p2_draw_stack.push_back(p2_stack.back());
        decreaseDeckSize();
        // burning one card and saving it incase of uncompleted draw
        p1_draw_stack.push_back(p1_stack.back());
        p2_draw_stack.push_back(p2_stack.back());
        decreaseDeckSize();
        players_draws++;
        result += " " + player1.getPlayerName() + " played " + p1_stack.back().toString() + " " + player2.getPlayerName() + " played " + p2_stack.back().toString() + ". " + player2.getPlayerName() + " draw.";
        draw_result = turn_oprator.playTurn(p1_stack.back(), p2_stack.back());
        drawable = canPlayDraw();
    }
    // still draw but not enough cards to play draw
    if (draw_result == "draw" && !drawable)
    {
        // returning the cards to the players
        result += " " + player1.getPlayerName() + " played " + p1_stack.back().toString() + " " + player2.getPlayerName() + " played " + p2_stack.back().toString() + ". " + player2.getPlayerName() + "not enough cards to continue,turn canceld!.";
        players_draws--;
        for (unsigned int i = 0; i < p1_draw_stack.size(); i++)
        {
            p1_stack.push_back(p1_draw_stack[i]);
            p2_stack.push_back(p2_draw_stack[i]);
            player1.setStackSize(p1_stack.size());
            player2.setStackSize(p2_stack.size());
        }
        return result;
    }
    // !draw which means theres a winner , dont care if drawable or not
    else if (draw_result == "p1")
    {
        int cards_taken = p1_draw_stack.size() + p2_draw_stack.size() + 2; // +2 for the breakingpoint cards
        player1.addWin(cards_taken);
        p1_wins++;
        decreaseDeckSize();
        result = "" + player1.getPlayerName() + " played " + p1_stack.back().toString() + " " + player2.getPlayerName() + " played " + p2_stack.back().toString() + ". " + player1.getPlayerName() + " wins.";
        return result;
    }
    else // (draw_result == "p2")
    {
        int cards_taken = p1_draw_stack.size() + p2_draw_stack.size() + 2; // +2 for the breakingpoint cards
        player2.addWin(cards_taken);
        p2_wins++;
        decreaseDeckSize();
        result = "" + player1.getPlayerName() + " played " + p1_stack.back().toString() + " " + player2.getPlayerName() + " played " + p2_stack.back().toString() + ". " + player2.getPlayerName() + " wins.";
        return result;
    }
}

void Game::printLastTurn()
{
    cout << last_turn_result << endl;
}

void Game::playAll()
{
    // play turns while both of the players have cards
    while (p1_stack.size() != 0 && p2_stack.size() != 0)
    {
        playTurn();
    }
}

void Game::printWiner()
{
    if (player1.cardesTaken() > player2.cardesTaken())
    {
        cout << player1.getPlayerName() << " won the game" << endl;
        player1.setWinner();
    }
    else if (player1.cardesTaken() < player2.cardesTaken())
    {
        cout << player2.getPlayerName() << " won the game" << endl;
        player2.setWinner();
    }
    else
    {
        cout << "there is no winner yet,game has not ended" << endl;
    }
}

void Game::printLog()
{
    for (unsigned int i = 0; i < turn_results.size(); i++)
    {
        cout << turn_results[i] << endl;
    }
}

void Game::printStats()

{
    int num_turns = (int)turn_results.size();
    double p1_winrate = (p1_wins / (double)num_turns) * 100;
    double p2_winrate = (p2_wins / (double)num_turns) * 100;
    double draws_rate = (players_draws / (double)num_turns) * 100;
    string p1_stats = "" + player1.getPlayerName() + " WinRate : " + to_string(p1_winrate) + "%, CardsWon : " + to_string(player1.cardesTaken()) + ", Wins :" + to_string(p1_wins) + " , DrawRate : " + to_string(draws_rate) + "%, Draws : " + to_string(players_draws) + "";
    string p2_stats = "" + player2.getPlayerName() + " WinRate : " + to_string(p2_winrate) + "%, CardsWon : " + to_string(player2.cardesTaken()) + ", Wins :" + to_string(p2_wins) + " , DrawRate : " + to_string(draws_rate) + "%, Draws : " + to_string(players_draws) + "";
    cout << "Number of turns : " + to_string(num_turns) << endl;
    cout << p1_stats << endl;
    cout << p2_stats << endl;
}

void Game::decreaseDeckSize()
{
    p1_stack.pop_back();
    p2_stack.pop_back();
    player1.decreaseStackSize();
    player2.decreaseStackSize();
}
bool Game::canPlayDraw()
{
    // can work with || , but both players needs to have the same amount in the stack
    if (p1_stack.size() <= 2 && p2_stack.size() <= 2)
    {
        return false;
    }
    return true;
}

bool Game::gameOver()
{
    if (p1_stack.size() == 0 && p2_stack.size() == 0)
    {
        return true;
    }
    return false;
}