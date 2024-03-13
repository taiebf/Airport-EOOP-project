#include"voterh.hpp"
#include"candidateh.hpp"
#include"voteh.hpp"
#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;


#ifndef Election


#define Election






class PresidentElection
{
        vector<Voter*> voters;
        vector<Candidate*> candidates;
        vector<Vote*> votes;

        string displayVotesPassword = "secret";

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

        /*~PresidentElection() {
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
        }*/

        bool createVoter(string name, int id){
            if (!isUniqueId(id)) {
                cout << "Unable to create voter/candidate with non-unique ID: " << id << endl;
                return false;
            }
            voters.push_back(new Voter(name, id));

            return true;
            }

        bool removeVoter(int id){
            auto it = std::remove_if(voters.begin(), voters.end(),[id]( Voter* voter) { return voter->getId() == id; });
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

            auto voteIt = std::remove_if(votes.begin(), votes.end(),[voterId](Vote* vote) { return vote->getVoter()->getId() == voterId; });
            if (voteIt != votes.end()) {
                (*voteIt)->getCandidate()->decVote();
                (*voteIt)->getVoter()->SethasVoted(false);
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
            candidates.push_back(new Candidate(name, id ));
            return true;
            }
            return false;
        }

        bool removeCandidate(int id){

                auto it = std::remove_if(candidates.begin(), candidates.end(),[id]( Candidate* candidate) { return candidate->getId() == id; });

                if(it != candidates.end()) {
                    deleteVotesByCandidate(id);
                    delete *it;
                    candidates.erase(it, candidates.end());
                    cout << "candidate with ID " << id << " removed successfully." << endl;
                    return true;
                }
                cout << " candidate with ID " << id << " not found." << endl;
                return false;

            }

         void deleteVotesByCandidate(int candidateId) {
            auto voteIt = remove_if(votes.begin(), votes.end(), [candidateId]( Vote* vote) {
                return (vote->getCandidate() != nullptr) && (vote->getCandidate()->getId() == candidateId);
            });

            for (auto it = voteIt; it != votes.end(); ++it) {
                delete *it;
            }

        votes.erase(voteIt, votes.end());
        }



        //Methods to manage votes

        bool castVote(int VoterId, int candidateId ){
            auto voterIt = find_if(voters.begin(), voters.end(),[VoterId]( Voter* voter) { return voter->getId() == VoterId; });

            if (voterIt != voters.end()) {
            if ((*voterIt)->hasVoted()) {
                cout << "Voter with ID " << VoterId << " has already voted." << endl;
            } else {
                auto candidateIt = find_if(candidates.begin(), candidates.end(),[candidateId]( Candidate* candidate) { return candidate->getId() == candidateId; });
                votes.push_back(new Vote(*voterIt, (candidateIt != candidates.end()) ? *candidateIt : nullptr));
                if (candidateIt != candidates.end()) {
                    (*candidateIt)->addVote();
                }

                (*voterIt)->SethasVoted(true);

                cout << "Vote cast successfully by voter with ID " << VoterId<<endl;
                return true;
            }
        } else {
            cout << "Voter with ID " << VoterId << " not found." << endl;
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
                cout << "ID: " << candidate->getId() << ", Name: " << candidate->getName() << ", Votes: " << candidate->getnumberOfVotes() << "\n";
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
            int candidateVotes = candidate->getnumberOfVotes();
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
                << ", Votes: " << winner->getnumberOfVotes() << "\n";
        } else {
            cout << "\nNo winner identified.\n";
        }

        cout << endl;
    }

    bool checkDisplayVotesPassword(const string& inputPassword) const {
        return (inputPassword == displayVotesPassword);
    }


};













#endif
