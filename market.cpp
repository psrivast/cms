#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "market.h"

using namespace std;

unordered_map<int, Order> order_map;
int orders_count;

/* Order function */
Order::Order(int norder_id,
                string ndealer_id, 
                string nside,
                string ncomm, 
                int nquant, 
                double nprice) {
    dealer_id = ndealer_id;
    order_id = norder_id;
    side = nside;
    comm = ncomm;
    quant = nquant;
    price = nprice; 
}

bool Order::is_filled() {
    return !(quant>0);
}

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
    else if(tokens[1] == "REVOKE") revoke_command(tokens);
    else if(tokens[1] == "CHECK") check_command(tokens);
    else if(tokens[1] == "LIST") list_command(tokens);
    /*
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
    
    // Verify syntax     
    if(tokens.size() != 6) {
        cout << "ERROR: INVALID_MESSAGE: incorrect number of arguments" << endl;
        return;    
    }
    if(!verify_side(tokens[2])) {
        cout << "ERROR: INVALID_MESSAGE: unknown side: " << tokens[2] << endl;
        return;
    }

    if(!verify_commodity(tokens[3])) {
        cout << "ERROR: UNKNOWN_COMMODITY: " << tokens[3] << endl;
        return;
    }

    if(stoi(tokens[4]) <= 0) {
        cout << "ERROR: INVALID_MESSAGE: quantity must be greater than 0" << endl;
        return;
    }
    
    if(stod(tokens[5]) <= 0.0) {
        cout << "ERROR: INVALID_MESSAGE: price must be greater than 0.0" << endl;
        return;
    }
    
    // Create order
    orders_count++;
    Order new_order(orders_count,tokens[0],tokens[2],tokens[3],stoi(tokens[4]),stod(tokens[5]));    
    pair<int,Order> order_pair(orders_count, new_order);    
    order_map.insert(order_pair);
    cout << ">" << get_order_info(orders_count) << " HAS BEEN POSTED" << endl;
    return;
}

void revoke_command(vector<string> tokens) {
    
    // Verify syntax
    if(tokens.size() != 3) {
        cout << "ERROR: INVALID_MESSAGE: incorrect number of arguments" << endl;
        return;    
    }
    int order_id = stoi(tokens[2]);
    if(order_map.find(order_id) == order_map.end()) {
        cout << "ERROR: UNKNOWN_ORDER" << endl;
        return;
    }
    
    Order order = order_map.find(order_id)->second;
    if(order.dealer_id != tokens[0]) {
        cout << "ERROR: UNAUTHORIZED" << endl;
        return;
    }

    order_map.erase(order_id);
    cout << ">" << order_id << " HAS BEEN REVOKED" << endl;
    return;
}

void check_command(vector<string> tokens) {
    
    // Verify syntax
    if(tokens.size() != 3) {
        cout << "ERROR: INVALID_MESSAGE: incorrect number of arguments" << endl;
        return;    
    }
    int order_id = stoi(tokens[2]);
    if(order_map.find(order_id) == order_map.end()) {
        cout << "ERROR: UNKNOWN_ORDER" << endl;
        return;
    }
    
    Order order = order_map.find(order_id)->second;
    if(order.dealer_id != tokens[0]) {
        cout << "ERROR: UNAUTHORIZED" << endl;
        return;
    }

    if(order.is_filled()) cout << order_id << " HAS BEEN FILLED" << endl;    
    else cout << ">" << get_order_info(order_id) << endl;
    return;
}

void list_command(vector<string> tokens) {
    
    bool commodity_flag = false;
    bool dealer_id_flag = false;

    //Verify syntax
    if(tokens.size() >= 3) {
        if(!verify_commodity(tokens[2])) {
            cout << ">ERROR: UNKNOWN_COMMODITY: " << tokens[2] << endl;        
            return;
        }
        commodity_flag = true;
    } 
    if(tokens.size() >= 4) {
        if(!verify_dealer_id(tokens[3])) {
            cout << ">ERROR: UNKNOWN_DEALER_ID: " << tokens[3] << endl;        
        }
        dealer_id_flag = true;
    }
    if(tokens.size() > 4) {
        cout << "ERROR: INVALID_MESSAGE: incorrect number of arguments" << endl;
        return;
    }

    //Iterate through orders
    for(unordered_map<int,Order>::iterator it = order_map.begin();
        it != order_map.end(); ++it) {
        Order order = it->second;
        if((!commodity_flag || (commodity_flag && order.comm == tokens[2])) &&
           (!dealer_id_flag || (dealer_id_flag && order.dealer_id == tokens[3])))
            cout << ">" << get_order_info(it->first) << endl;
    }
    return;
}

/* Output functions */
string get_order_info(int order_id) {
    
    Order order = order_map.find(order_id) -> second;
    string order_info = to_string(order.order_id) + " " + order.dealer_id + 
                        " " + order.side + " " + order.comm + " " + 
                        to_string(order.quant) + " " + to_string(order.price);
    return order_info;    
}

int main() {
   
    orders_count = 0;

    while (true) {
        string message;
        getline(cin, message);
        process_message(message);
    }
    
    return 0;
}
