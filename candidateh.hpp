#include"voterh.hpp"
using namespace std;
#ifndef candidateh


#define candidateh

class Candidate :public Voter
{
    int numberOfVotes= 0;
public:

    Candidate(string name,int ID): Voter(name, ID){};
    ~Candidate(){};
    int getnumberOfVotes(){return numberOfVotes; }
    void addVote(){++numberOfVotes;}
    void decVote(){--numberOfVotes;}



};

#endif
