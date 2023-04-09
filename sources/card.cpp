#include "player.hpp"

using namespace std;
using namespace ariel;

Card::Card(int rank, string suit)
{
    this->rank = rank;
    this->suit = suit;
}

string Card::getSuit()
{
    return this->suit;
}

int Card::getRank() const
{
    return this->rank;
}
string Card::rankToString(int rank) const
{
    string str_rank;
    switch (rank)
    {
    case 1:
        str_rank = "Ace";
        break;
    case 2:
        str_rank = "Two";
        break;
    case 3:
        str_rank = "Three";
        break;
    case 4:
        str_rank = "Four";
        break;
    case 5:
        str_rank = "Five";
        break;
    case 6:
        str_rank = "Six";
        break;
    case 7:
        str_rank = "Seven";
        break;
    case 8:
        str_rank = "Eight";
        break;
    case 9:
        str_rank = "Nine";
        break;
    case 10:
        str_rank = "Ten";
        break;
    case 11:
        str_rank = "Jack";
        break;
    case 12:
        str_rank = "Queen";
        break;
    case 13:
        str_rank = "King";
        break;
    }
    return str_rank;
}
string Card::toString() const
{
    return rankToString(this->rank) + " of " + this->suit;
}