#include<iostream>
#include<vector>
using namespace std;

#ifndef Election


#define Election

class PresidentElection
{
        vector<Voter*> voters;
        vector<Candidate*> candidates;
        vector<Vote*> votes;

        bool isUniqueId(int id) {
            for (const auto& voter : voters) {
                if (voter->getId() == id) {
                return false;
                }
            }
            return true;
        }

public:


        PresidentElection() {
            cout << "Election instance created.\n";
        }

        ~PresidentElection() {
             for (Voter* voter : voters) {
                delete voter;
            }
            for (Candidate* candidate : candidates) {
                delete candidate;
            }
            for (Vote* vote : votes) {
                delete vote;
            }

        cout << "Election instance destroyed.\n";
        }

        bool createVoter(string name, int id){
            if (!isUniqueId(id)) {
                cout << "Unable to create voter/candidate with non-unique ID: " << id << endl;
                return false;
            }
            voters.push_back(new Voter(name, id));

            return true;
            }

        bool removeVoter(int id){
            auto it = std::remove_if(voters.begin(), voters.end(),[id](const Voter* voter) { return voter->getId() == id; });
            deleteVote(id);
            if (it != voters.end()) {
                delete *it;
                voters.erase(it, voters.end());
                cout << "Voter / candidate with ID " << id << " removed successfully." << endl;
                return true;
            } else {
                cout << "Voter / candidate with ID " << id << " not found." << endl;
            }
            return false;
        }

        bool deleteVote(int voterId) {

            auto voteIt = remove_if(votes.begin(), votes.end(),[voterId](const Vote* vote) { return vote->getVoter()->getId() == voterId; });
            if (voteIt != votes.end()) {
                (*voteIt)->getCandidate()->decVote();
                (*voteIt)->getVoter()->sethasVoted(false);
                for (auto it = voteIt; it != votes.end(); ++it) {
                delete *it;
                }
                votes.erase(voteIt, votes.end());
                cout << "Vote for voter with ID " << voterId << " deleted successfully." << endl;
                return true;
            } else{
                cout << "Vote for voter with ID " << voterId << " not found." << endl;
            }
            return false;
        }

        bool createCandidate( string name, int id){
            if(createVoter( name,  id)){
            candidates.push_back(new Candidate(name, id , 0));
            return true;
            }
            return false;
        }

        bool removeCandidate(int id){
            if(removeVoter(id)){
                auto it = std::remove_if(candidates.begin(), candidates.end(),[id](const Candidate* candidate) { return candidate->getId() == id; });

                if(it != candidates.end()) {
                    delete *it;
                    candidates.erase(it, candidates.end());
                }
            return true;
            }
            return false;
        }

        //Methods to manage votes

        void castVote(int Voterid, int candidateId ){
            auto voterIt = find_if(voters.begin(), voters.end(),[voterId](const Voter* voter) { return voter->getId() == voterId; });

            if (voterIt != voters.end()) {
            if ((*voterIt)->hasVoted()) {
                cout << "Voter with ID " << voterId << " has already voted." << endl;
            } else {
                auto candidateIt = find_if(candidates.begin(), candidates.end(),[candidateId](const Candidate* candidate) { return candidate->getId() == candidateId; });
                votes.push_back(new Vote(*voterIt, (candidateIt != candidates.end()) ? *candidateIt : nullptr));
                if (candidateIt != candidates.end()) {
                    (*candidateIt)->getNumberOfVotes()++;
                }

                (*voterIt)->setHasVoted();

                cout << "Vote cast successfully by voter with ID " << voterId<<endl;
                return true;
            }
        } else {
            cout << "Voter with ID " << voterId << " not found." << endl;
        }
        return false;
        }


        void displayVoters(){
            cout << "Voters:\n";
            for (const auto& voter : voters) {
                cout << "ID: " << voter->getId() << ", Name: " << voter->getName() << ", Voted: " << (voter->hasVoted() ? "Yes" : "No") << "\n";
            }
            cout << endl;
        }


        void displayCandidates(){
            cout << "Candidates:\n";
            for (const auto& candidate : candidates) {
                cout << "ID: " << candidate->getId() << ", Name: " << candidate->getName() << ", Votes: " << candidate->getNumberOfVotes() << "\n";
            }
            cout << endl;
        }


       void displayVotes(){
            cout << "Votes:\n";
            for (const auto& vote : votes) {
                cout << "Voter ID: " << vote->getVoter()->getId();
                if (vote->getCandidate() != nullptr) {
                    cout << ", Candidate ID: " << vote->getCandidate()->getId();
                } else {
                    cout << ", Candidate: nullptr";
                }
            cout << "\n";
            }
        cout << endl;
        }

    void displayResults(){
        int totalVotes = votes.size();
        int totalVoters = voters.size();
        int totalCandidates = candidates.size();

    // Check if the number of votes is less than 30% of the number of voters
        if (totalVotes < 0.3 * totalVoters) {
            cout << "Not enough votes to display results." << endl;
            return;
        }

    // Check if the number of candidates is less than 2
        if (totalCandidates < 2) {
            cout << "Not enough candidates to determine results." << endl;
            return;
        }

        cout << "Election Results:\n";

        Candidate* winner = nullptr;
        int maxVotes = 0;

        // Display information about candidates with at least one vote and find the winner
        for (const auto& candidate : candidates) {
            int candidateVotes = candidate->getNumberOfVotes();
            if (candidateVotes > 0) {
                cout << "Candidate ID: " << candidate->getId() << ", Name: " << candidate->getName()
                    << ", Votes: " << candidateVotes << "\n";

            // Update the winner if the candidate has more votes
                if (candidateVotes > maxVotes) {
                    maxVotes = candidateVotes;
                    winner = candidate;
                }
            }
        }

        if (winner != nullptr) {
            cout << "\nWinner: Candidate ID: " << winner->getId() << ", Name: " << winner->getName()
                << ", Votes: " << winner->getNumberOfVotes() << "\n";
        } else {
            cout << "\nNo winner identified.\n";
        }

        cout << endl;
    }


};



class Candidate :public Voter
{
    int numberOfVotes= 0
public:

    Candidate(string name,int ID,int NOV ): Voter(name, ID),numberOfVotes(NOV){};
    ~Candidate(){};
    int getnmberOfVotes(){return numberOfVotes; }
    void addVote(){++numberOfVotes;}
    void decVote(){--numberOfVotes;}



};

class Voter
{
    string name;
    int id;
    bool Voted= false;


public:

    Voter(string name, int id )
    ~Voter()

    int getId(){return id;}
    string getName(){return name;}
    void SethasVoted(bool bo){ Voted= bo;}
    bool hasVoted(){return Voted;}

};




class Vote
{
    Candidate *candidate;
    Voter* voter;

public:
    Vote(Voter *V, Candidate *C= nullptr):voter(V), candidate(C){}
    void setCandidate(Candidate* C){Candidate= C;}
    Candidate *getCandidate(){return candidate;}
    Voter *getVoter(){return voter; }

};


#endif
