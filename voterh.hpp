#include<iostream>
#include<vector>
#include <algorithm>
#include<string>
using namespace std;

#ifndef voterh


#define voterh

class Voter
{
    string name;
    int id;
    bool Voted= false;



public:

    Voter(string n, int ID ):name(n), id(ID) {}
    ~Voter(){}

    int getId(){return id;}
    string getName(){return name;}
    void SethasVoted(bool bo){ Voted= bo;}
    bool hasVoted(){return Voted;}

};

#endif
