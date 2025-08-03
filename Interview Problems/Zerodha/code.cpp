#include<bits/stdc++.h>
using namespace std;

class Stock {
	int id;
	string name;
public:
	Stock(int id, string name): id(id), name(name) {}
};

class Observer {
public:
	int id;
	string name;
	double balance;
public:
	Observer(int id, string name): id(id), name(name) {}
	void updateBalance(double newBalance){
		balance = newBalance;
	}
	double getBalance(){
		return balance;
	}
	virtual void notify() = 0;
};

// Base class : Observer -> can be other observers like Admin, Agents etc
class Customer : public Observer {
	vector<pair<Stock*,int>> stocks; // protfolio of stocks owned by Customer
public:
	Customer(int id, string name): Observer(id, name) {}

	void addStockToPortfolio(Stock* stock, int qty) {
		stocks.push_back({stock, qty});
	}

	void notify() override {
		// call this method when customer has to be notofied about a status update
		cout<<"Customer "<<this->name<<" notfied"<<endl;
	}
};

enum Order_types {
	BUY,
	SELL
};

class Order {
public:
	int id;
	string name;
	Order_types type;
	Order(int id, string name, Order_types type): id(id), name(name), type(type) {}
};

class BuyOrder : public Order {
public:
	BuyOrder(int id, string name): Order(id, name, Order_types::BUY) {}
};

class SellOrder : public Order {
public:
	SellOrder(int id, string name): Order(id, name, Order_types::SELL) {}
};

// Factory
class OrderFactory {
public:
	static Order* createOrder(int id, string name, Order_types type){
		if(type == Order_types::BUY){
			return new BuyOrder(id, name);
		} else if(type == Order_types::SELL){
			return new SellOrder(id, name);
		} else {
			return nullptr;
		}
	}
};

class OrderExecutionStrategy {
public:
	virtual void executeOrder(Customer* customer, Order* order) = 0; 
};

class BuyAtMarketStrategy : public OrderExecutionStrategy {
	void executeOrder(Customer* customer, Order* order) override {
		cout<<"Exeuting "<<order->name<<" for "<<customer->name<<endl;
	}
};

class SellAtMarketStrategy : public OrderExecutionStrategy {
	void executeOrder(Customer* customer, Order* order) override {
		// execute order for customer using this strategy
	}
};

class BuyAtLimitStrategy : public OrderExecutionStrategy {
	void executeOrder(Customer* customer, Order* order) override {
		// execute order for customer using this strategy
	}
};

class SellAtLimitStrategy : public OrderExecutionStrategy {
	void executeOrder(Customer* customer, Order* order) override {
		// execute order for customer using this strategy
	}
};

// Black boxing logic for getting market price of stocks

enum class Price_Types {
	MARKET,
	LIMIT
};

// Singleton
class OrderProcessor {
private:
	static OrderProcessor* instance;
	OrderProcessor() = default;
public:
	static OrderProcessor* getInstance(){
		if(instance == nullptr){
			instance = new OrderProcessor();
		}
		return instance;
	}

	void executeOrder(Customer* customer, Order* order, Price_Types type){
		OrderExecutionStrategy* strategy = nullptr;
		if(type == Price_Types::MARKET){
			if(order->type == Order_types::BUY){
				// use the approporiate strategy to excute order
				strategy = new BuyAtMarketStrategy();
			} else {
				// use the approporiate strategy to excute order
				strategy = new SellAtMarketStrategy();
			}
		} else {
			if(order->type == Order_types::BUY){
				strategy = new BuyAtLimitStrategy();
			} else {
				strategy = new SellAtLimitStrategy();
			}
		}

		if(strategy != nullptr){
			strategy->executeOrder(customer, order);
			customer->notify();
		}
	}
};

OrderProcessor* OrderProcessor::instance = nullptr;


// Patterns discussed - Observer, Strategy, Factory, Singleton

int main(){
	OrderProcessor* processor = OrderProcessor::getInstance();

	Order* order = OrderFactory::createOrder(1, "test order 1", Order_types::BUY);
	Customer* customer1 = new Customer(1, "John");

	processor->executeOrder(customer1, order, Price_Types::MARKET);
}