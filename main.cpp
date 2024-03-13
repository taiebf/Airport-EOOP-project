#include"Election.hpp"

#include <iostream>
#include <cassert>

using namespace std;





int main() {
   // vector<PresidentElection*> elections;
    PresidentElection test, test1;

    test.removeCandidate(6); //removing a non exsiting candidate
    test.castVote(10,6); // casting vote with non exsiting candidate and voter
    test.removeVoter(5); // removing a non exsiting voter
    test.displayCandidates(); // dsiplay empty election
    test.displayVoters(); // display empty voters list
    test.displayResults(); // display empty election resuts
    // Test 1: Add voters
    test.createVoter("Alice", 1);
    test.createVoter("Bob", 2);
    test.createVoter("aooa", 2); // adding a voter with existing id

    // Test 2: Add candidates
    test.createCandidate("Candidate1", 101);
    test.createCandidate("Candidate2", 102);
    test.createCandidate("Candidate1101", 101); // addinng a candidate with an exsiting candidate id
    test.createCandidate("Candidate1", 1); // adding a candidate with an exsiting voter id

    // Test 3: Display voters and candidates
    cout << "---- Test 3: Display Voters and Candidates ----\n";
    test.displayVoters();
    test.displayCandidates();

    // Test 4: Cast votes
    //election.castVote(1, 101);
    //election.castVote(2, 102);
    test.castVote(1, 102);
    test.castVote(1,102); // testing for voter to vote again

    // Test 5: Display results
    cout << "---- Test 5: Display Results with less of 1/3 of votes ----\n";
    test.displayResults();


    // Test 6: Add more voters and candidates
    test.createVoter("Charlie", 3);
    test.createCandidate("Candidate3", 103);

    // Test 7: Cast votes and display results
    test.castVote(2, 103);
    test.castVote(3, 102);
    cout << "---- Test 7: Display Results After Additional Votes ----\n";
    test.displayResults();

    // Test 8: Remove a candidate and display results
    cout << "---- Test 8: Remove Candidate and Display Results ----\n";
    test.removeCandidate(103);
    test.displayResults();

    // Test 9: Remove a voter that has not voted and display results
    cout << "---- Test 9: Remove Voter  and Display candidates and voters ----\n";
    test.removeVoter(3);
    test.displayResults();



    // Test 10: Attempt to cast votes after removing a voter
    cout << "---- Test 10: Attempt to Cast Votes After Removing a Voter ----\n";
    test.castVote(2, 101);
    test.castVote(3, 102);

    // Test 11: Display results after attempted votes
    cout << "---- Test 11: Display Results After Attempted Votes ----\n";
    test.displayResults();

    // Test 12: Remove a non-existing voter
    cout << "---- Test 12: Remove Non-Existing Voter ----\n";
    test.removeVoter(10);

    // Test 13: Remove a non-existing candidate
    cout << "---- Test 13: Remove Non-Existing Candidate ----\n";
    test.removeCandidate(105);

    cout<< "---- Test 14: adding candidates before voters for test2 ----\n";

    // Test 1': Add candidates
    test1.createCandidate("Candidate1", 101);
    test1.createCandidate("Candidate2", 102);
    test1.createCandidate("Candidate1101", 101); // adding a candidate with

    // Test 2': Add voters
    test1.createVoter("Alice", 1);
    test1.createVoter("Bob", 2);
    // Test 3': Display voters and candidates
    cout << "---- Test 3': Display Voters and Candidates ----\n";
    test1.displayVoters();
    test1.displayCandidates();

    return 0;}



   /* while (true) {
        cout<<"*****************************************************\n";
        cout << "1. Create Election\n";
        cout << "2. Add Voter\n";
        cout << "3. Add Candidate\n";
        cout << "4. Remove Voter\n";
        cout << "5. Remove Candidate\n";
        cout << "6. Cast Vote\n";
        cout << "7. Remove Vote\n";
        cout << "8. Display Voters and Candidates\n";
        cout << "9. Display Election Results\n";
        cout << "10. Display Votes (password protected)\n";
        cout << "11. Showcase test\n";
        cout << "12. Exit\n";
        cout<<"*****************************************************\n";
        cout << "Choose an option: ";

        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1: {
                elections.push_back( new PresidentElection());
                cout << "New Election created.\n";
                break;
            }
            case 2: {
                if (elections.empty()) {
                    cout << "No elections available. Create an election first.\n";
                    break;
                }
                int electionIndex;
                cout << "Enter the index of the election: ";
                cin >> electionIndex;

                if (electionIndex < 0 || electionIndex >= elections.size()) {
                    cout << "Invalid election index.\n";
                    break;
                }

                string name;
                int id;
                cout << "Enter voter name: ";
                cin >> name;
                cout << "Enter voter ID: ";
                cin >> id;

                if (elections[electionIndex]->createVoter(name, id)) {
                    cout << "Voter added to the election.\n";
                }
                elections[electionIndex]->displayVoters();
                break;
            }
            case 3: {
                if (elections.empty()) {
                    cout << "No elections available. Create an election first.\n";
                    break;
                }
                int electionIndex;
                cout << "Enter the index of the election: ";
                cin >> electionIndex;

                if (electionIndex < 0 || electionIndex >= elections.size()) {
                    cout << "Invalid election index.\n";
                    break;
                }

                string name;
                int id;
                cout << "Enter candidate name: ";
                cin >> name;
                cout << "Enter candidate ID: ";
                cin >> id;

                if (elections[electionIndex]->createCandidate(name, id)) {
                    cout << "Candidate added to the election.\n";
                }
                elections[electionIndex]->displayCandidates();
                break;
            }
             case 4: {
                if (elections.empty()) {
                    cout << "No elections available. Create an election first.\n";
                    break;
                }

                int electionIndex;
                cout << "Enter the index of the election: ";
                cin >> electionIndex;

                if (electionIndex < 0 || electionIndex >= elections.size()) {
                    cout << "Invalid election index.\n";
                    break;
                }

                int voterId;
                cout << "Enter the ID of the voter to remove: ";
                cin >> voterId;

                if (elections[electionIndex]->removeVoter(voterId)) {
                    cout << "Voter removed from the election.\n";
                }
                elections[electionIndex]->displayVoters();
                break;
            }
            case 5: {
                if (elections.empty()) {
                    cout << "No elections available. Create an election first.\n";
                    break;
                }

                int electionIndex;
                cout << "Enter the index of the election: ";
                cin >> electionIndex;

                if (electionIndex < 0 || electionIndex >= elections.size()) {
                    cout << "Invalid election index.\n";
                    break;
                }

                int candidateId;
                cout << "Enter the ID of the candidate to remove: ";
                cin >> candidateId;

                if (elections[electionIndex]->removeCandidate(candidateId)) {
                    cout << "Candidate removed from the election.\n";
                }
                elections[electionIndex]->displayCandidates();
                break;
            }
            case 6: {

                if (elections.empty()) {
                    cout << "No elections available. Create an election first.\n";
                    break;
                }

                int electionIndex;
                cout << "Enter the index of the election: ";
                cin >> electionIndex;

                if (electionIndex < 0 || electionIndex >= elections.size()) {
                    cout << "Invalid election index.\n";
                    break;
                }

                int voterId, candidateId;
                cout << "Enter the ID of the voter: ";
                cin >> voterId;
                cout << "Enter the ID of the candidate: ";
                cin >> candidateId;

                if (elections[electionIndex]->castVote(voterId, candidateId)) {
                    cout << "Vote cast successfully.\n";
                }
                break;
            }


             case 7: {

                if (elections.empty()) {
                    cout << "No elections available. Create an election first.\n";
                    break;
                }

                int electionIndex;
                cout << "Enter the index of the election: ";
                cin >> electionIndex;

                if (electionIndex < 0 || electionIndex >= elections.size()) {
                    cout << "Invalid election index.\n";
                    break;
                }

                int voterId;
                cout << "Enter the ID of the voter to remove the vote: ";
                cin >> voterId;

                if (elections[electionIndex]->deleteVote(voterId)) {
                    cout << "Vote removed from the election.\n";
                }
                elections[electionIndex]->displayVotes();
                break;
            }

            case 8: {

                if (elections.empty()) {
                    cout << "No elections available. Create an election first.\n";
                    break;
                }

                int electionIndex;
                cout << "Enter the index of the election: ";
                cin >> electionIndex;

                if (electionIndex < 0 || electionIndex >= elections.size()) {
                    cout << "Invalid election index.\n";
                    break;
                }

                elections[electionIndex]->displayCandidates();
                elections[electionIndex]->displayVoters();
                break;
            }










            case 9: {
                if (elections.empty()) {
                    cout << "No elections available. Create an election first.\n";
                    break;
                }

                int electionIndex;
                cout << "Enter the index of the election: ";
                cin >> electionIndex;

                if (electionIndex < 0 || electionIndex >= elections.size()) {
                    cout << "Invalid election index.\n";
                    break;
                }

                elections[electionIndex]->displayResults();
                break;
            }


            case 10: {
                if (elections.empty()) {
                    cout << "No elections available. Create an election first.\n";
                    break;
                }

                int electionIndex;
                cout << "Enter the index of the election: ";
                cin >> electionIndex;

                if (electionIndex < 0 || electionIndex >= elections.size()) {
                    cout << "Invalid election index.\n";
                    break;
                }

                string password;
                cout << "Enter the password to display votes: ";
                cin >> password;

                if (elections[electionIndex]->checkDisplayVotesPassword(password)) {
                    elections[electionIndex]->displayVotes();
                } else {
                    cout << "Incorrect password. Votes cannot be displayed.\n";
                }
                break;
            }


            case 11:{

                testing(test);
                break;

                }





            case 12: {
                  for (PresidentElection* election : elections) {
                        delete election;
                    }
                cout << "Exiting the program.\n";
                return 0;
            }
            default:
                cout << "Invalid choice. Please choose a valid option.\n";
                break;
            }
    }



    return 0;
}*/

