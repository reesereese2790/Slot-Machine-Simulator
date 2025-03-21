#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;

// Create a data structure that contains an item and a probability of picking it
struct ItemProb {
    string item;
    double prob; 
};

// strip for the slot game
vector<ItemProb> strip = {
    {"A",0.33},
    {"B",0.33},
    {"C",0.34}
};

// Function to use the slot machine
string SlotPull(){

    // seed for pseudorandom number generator
    random_device rd;
    
    // random number generator 
    mt19937 gen(rd());

    // every number in the range has equal probability of being generated
    uniform_real_distribution<> dis(0.0,1.0);
    
    // gets random number between 0 and 1
    double random_value = dis(gen);
    
    // determine which item to pick
    // if the random value is greater than the prob 
    // then keep adding the prob until the value is less than it
    double cumulative_prob = 0.0;
    for (int i = 0; i < strip.size(); ++i){    
        cumulative_prob += strip[i].prob;
        if (random_value < cumulative_prob){
            return strip[i].item;
        }
    }
    return "";
};

int main() {
    // initializing variables
    bool valid_input = false;
    bool play_again = true;
    string user_input;
    int wallet = 10;
    int prize;
    int low = 1;
    int mid = 2;
    int high = 5;
    
    cout << "Your wallet balance is " << wallet << endl;
    cout << "The return to player (RTP) for this game is " << (high*strip[0].prob + mid*strip[1].prob + low*strip[2].prob)/strip.size() << endl;

    while (play_again){
        while (!valid_input){
            cout << "Welcome to the Slot Machine Simulator! Type the word 'bet' to bet 1 credit and find out what your prize is." << endl;
            cin >> user_input;
            if (user_input == "bet") {
                wallet -= 1;
                valid_input = true;
            }
            else {
                cout << "Invalid input. Please enter 'bet' if you would like to play." << endl;
                cin.clear();
            }
        }
            
        // Pick 2 random letters from a strip.
        string slot_pull_1 = SlotPull();
        string slot_pull_2 = SlotPull();
        cout << "The payline is " << slot_pull_1 << slot_pull_2 << endl;
        
        // prizes 
        if (slot_pull_1 == "A" && slot_pull_2 == "A") {
            prize = high;
            wallet += prize;
        }
        else if (slot_pull_1 == "B" && slot_pull_2 == "B") {
            prize = mid;
            wallet += prize;
        }
        else if (slot_pull_1 == "C" && slot_pull_2 == "C") {
            prize = low;
            wallet += prize;
        }
        else{
            prize = 0;
        }

        cout << "Your prize is "<< prize << endl;
        cout << "Your wallet balance is " << wallet << endl;
        
        // play again prompt
        cout << "Would you like to play again? (Y/N)" << endl;
        cin >> user_input;
        if (user_input == "Y") {
            play_again = true;
            wallet -= 1;
            if (wallet == 0){
                cout << "You ran out of money. Womp womp. :(" << endl;
                play_again = false;
            }
        }
        else if (user_input == "N") {
            play_again = false;
        }
        else {
            cout << "Invalid input. Game shutting down." << endl;
            play_again = false;
        }
    }

    return 0;
}