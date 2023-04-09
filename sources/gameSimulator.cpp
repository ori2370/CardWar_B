#include "gameSimulator.hpp"

using namespace std;
using namespace ariel;

string gameSimulator::playTurn(const Card &c1, const Card &c2)
{
    if (c1.getRank() == c2.getRank())
    {
        return "draw";
    }
    else if (c1.getRank() == 1) // ace wins anything but 2
    {
        if (c2.getRank() == 2)
        {
            return "p2";
        }
        else
        {
            return "p1";
        }
    }
    else if (c2.getRank() == 1) // same here
    {
        if (c1.getRank() == 2)
        {
            return "p1";
        }
        else
        {
            return "p2";
        }
    }
    // not ace for both players
    else if (c1.getRank() > c2.getRank())
    {
        return "p1";
    }
    else //(c1.getRank() < c2.getRank())
    {
        return "p2";
    }
}
