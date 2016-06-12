
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
    int order_id;
    string side;
    string comm;
    int quant;
    string dealer_id;
    double price;
};

/* Verification function */
bool verify_dealer_id(string dealer_id);
bool verify_side(string side);
bool verify_commodity(string commodity);

/* Message processing */
void process_message(string message);

/* POST */
void post_command(vector<string> tokens);