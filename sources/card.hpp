#ifndef CARD_HPP
#define CARD_HPP
#include <string>

using namespace std;
namespace ariel
{
    class Card
    {
    private:
        string suit; // hearts,spades etc...
        int rank;
        string rankToString(int rank) const;

    public:
        Card() : rank(0){};
        Card(int rank, string suit);
        string getSuit();
        int getRank() const;
        string toString() const;
    };

}
#endif