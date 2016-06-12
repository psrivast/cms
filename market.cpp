#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include "market.h"

using namespace std;

void process_message(string message) {
    vector<string> tokens;
    istringstream iss(message);
    
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(tokens));    
    
    if(tokens.size() < 2) cout << "Error: Invalid message" << endl;  

    string dealer_id = tokens[0];
    
    /*
    for(vector<int>::size_type i = 0; i < tokens.size(); i++) {
        cout << tokens[i] << " | ";    
    }
    */
}



int main() {
    
    while (true) {
        string message;
        getline(cin, message);
        process_message(message);
    }
    
    return 0;
}
