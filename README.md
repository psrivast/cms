# Commodity Market System - CMS<GO>

Author: Parag Srivastava

## Description 
- Electronic platform for trading commodities contracts
- Post orders: Dealers can list contracts they have available to buy or sell
- Aggress orders: Dealers can complete trades
- Modify and revoke orders
- Querying of available orders


## How to build and rum

Uses g++ compiler

Build make file

```sh
$ make
```

Run cms function
```sh
$ ./cms base
```

## Design
##### Order map
- Used unordered_map<int, Order> data type to map order_id to Orders
- Allows for O(1) lookup and delete

##### Order class
- Information: order_id, dealer_id, side, commodity, quanitity, price

##### Assumptions made
- A bank should not simultaneously Aggress the same order muliiple times
```sh
DB AGGRESS 1 100 1 200
```
- A bank should not Aggress on itself
- order_id can never be repeated

## TODO
1. Extension 1 - accept communication over TCP socket
2. Extension 2 - Handle more than one connnection concurrently
