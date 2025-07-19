#include<bits/stdc++.h>
using namespace std;

class PaymentStrategy {
public:
	virtual void processPayment(double amount) = 0;
	virtual ~PaymentStrategy() {
		cout<<"Destructor\n";
	}
};

class CreditCardPayment : public PaymentStrategy {
public:
	void processPayment(double amount) override {
		cout << "Processing credit card payment of $" << amount << endl;
	}
};

class PayPalPayment : public PaymentStrategy {
public:
    void processPayment(double amount) override {
        cout << "Processing PayPal payment of $" << amount << endl;
    }
};

class CryptocurrencyPayment : public PaymentStrategy {
public:
    void processPayment(double amount) override {
        cout << "Processing cryptocurrency payment of $" << amount << endl;
    }
};

class StrategyFactory{
public:
	static PaymentStrategy* createStrategy(string type){
		if(type == "credit"){
			return new CreditCardPayment();
		} else if(type == "paypal"){
			return new PayPalPayment();
		} else if(type == "crypto"){
			return new CryptocurrencyPayment();
		} else {
			return nullptr;
		}
	}
};

class PaymentProcessor {
private:
	PaymentStrategy* paymentStrategy;

public: 
	PaymentProcessor(): paymentStrategy(nullptr) {}

	void setPaymentStrategy(string type){
		if(paymentStrategy) delete paymentStrategy;
		paymentStrategy = StrategyFactory::createStrategy(type);
	}

	void processPayment(double amount){
		if(paymentStrategy){
			paymentStrategy->processPayment(amount);
		} else{
			cout<<"Payment strategy not defined\n";
		}
	}

	~PaymentProcessor(){
		if(paymentStrategy){
			delete paymentStrategy;
		}
	}
};


int main(){
	PaymentProcessor paymentProcessor;
	paymentProcessor.setPaymentStrategy("credit");
	paymentProcessor.processPayment(200);
	paymentProcessor.setPaymentStrategy("paypal");
	paymentProcessor.processPayment(250);
}