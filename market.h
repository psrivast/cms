using namespace std;

const string sides[] = {
    "BUY", 
    "SELL"
};

const string commodities[] = {
    "GOLD",
    "SILV",
    "PORK",
    "OIL",
    "RICE"
};

const string dealers[] = {
    "DB",
    "JPM",
    "UBS",
    "RBC",
    "BARX"
};

class Order {
public:
    string dealer_id;
    string comm;

    Order(int norder_id,
                string ndealer_id, 
                string nside,
                string ncomm, 
                int nquant, 
                double nprice);
    bool is_filled();
    bool is_trade_valid(int amount);
    string make_trade(int amount);
    string get_order_info();

private:
    int order_id;
    string side;
    int quant;
    double price;
};

/* Verification function */
bool verify_dealer_id(string dealer_id);
bool verify_side(string side);
bool verify_commodity(string commodity);

/* Message processing */
void process_message(string message);

/* Commands */
void post_command(vector<string> tokens);
void revoke_command(vector<string> tokens);
void check_command(vector<string> tokens);
void list_command(vector<string> tokens);
void aggress_command(vector<string> tokens);

/* Output */
string get_order_info(int order_id);
string make_trade(pair<int,int> trade);
