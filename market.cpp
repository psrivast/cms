#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include "market.h"

using namespace std;

/* Verification functions */
bool verify_dealer_id(string dealer_id) {
    for(int i = 0; i < sizeof(dealers)/sizeof(*dealers); i++) {
        if(dealers[i] == dealer_id) return true;
    }
    return false;
}

bool verify_side(string side) {
    for(int i = 0; i < sizeof(sides)/sizeof(*sides); i++) {
        if(sides[i] == side) return true;
    }
    return false;

}
 
bool verify_commodity(string commodity) {
    for(int i = 0; i < sizeof(commodities)/sizeof(*commodities); i++) {
        if(commodities[i] == commodity) return true;
    }
    return false;

}


void process_message(string message) {
    vector<string> tokens;
    istringstream iss(message);
    
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(tokens));    
    
    if(tokens.size() < 2) {
        cout << "ERROR: Invalid message" << endl;  
        return;    
    }
    
    if(!verify_dealer_id(tokens[0])) {
        cout << "ERROR: Unkonwn Dealer: " << tokens[0] << endl;
        return;
    }   
   
    if(tokens[1] == "POST") post_command(tokens);
    /*
    else if(tokens[1] == "REVOKE") revoke_command(tokens);
    else if(tokens[1] == "CHECK") check_command(tokens);
    else if(tokens[1] == "LIST") list_command(tokens);
    else if(tokens[1] == "AGGRESS") aggress_command(tokens);
    */    
    else {
        cout << "ERROR: Invalid Message: Unknown command " << tokens[1] << endl;
        return; 
    }   
     
    /*
    for(vector<int>::size_type i = 0; i < tokens.size(); i++) {
        cout << tokens[i] << " | ";    
    }
    */
}

void post_command(vector<string> tokens) {
}

int main() {
   
    while (true) {
        string message;
        getline(cin, message);
        process_message(message);
    }
    
    return 0;
}
