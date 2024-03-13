#include"voterh.hpp"
#include"candidateh.hpp"
using namespace std;
#ifndef voteh


#define voteh


class Vote
{
    Candidate *candidate;
    Voter* voter;

public:
    Vote(Voter *V, Candidate *C= nullptr):voter(V), candidate(C){}
    void setCandidate(Candidate* C){candidate= C;}
    Candidate *getCandidate(){return candidate;}
    Voter *getVoter(){return voter; }

};

#endif
