
using namespace std;

enum Side {
    BUY, 
    SELL
};

enum Commodity {
    GOLD,
    SILV,
    PORK,
    OIL,
    RICE
};

enum Dealer {
    DB,
    JPM,
    UBS,
    RBC,
    BARX
};

class Order {
public:
    int order_id;
    Side side;
    Commodity comm;
    int quant;
    double price;
};
