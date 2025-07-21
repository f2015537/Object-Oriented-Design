#include<bits/stdc++.h>
using namespace std;

class OrderProcessingTemplate{
public:
	void processOrder(){
		verifyOrder();
		assignDeliveryPartner();
		trackDelivery();
	}
	virtual void verifyOrder() = 0;
	virtual void assignDeliveryPartner() = 0;
	virtual void trackDelivery() = 0;

	virtual ~OrderProcessingTemplate() = default;
};

class LocalOrderProcessor : public OrderProcessingTemplate {
public:
	void verifyOrder() override {
		cout<<"Verifying local order..."<<endl;
	}
	void assignDeliveryPartner() override {
		cout<<"Assigning delivery partner for local order..."<<endl;
	}
	void trackDelivery() override {
		cout<<"Tracking delivery for local order..."<<endl;
	}	
};

class InternationalOrderProcessor : public OrderProcessingTemplate {
public:
	void verifyOrder() override {
		cout<<"Verifying International order..."<<endl;
	}
	void assignDeliveryPartner() override {
		cout<<"Assigning delivery partner for International order..."<<endl;
	}
	void trackDelivery() override {
		cout<<"Tracking delivery for International order..."<<endl;
	}	
};

int main(){
	OrderProcessingTemplate *local = new LocalOrderProcessor();
	OrderProcessingTemplate *international = new InternationalOrderProcessor();

	local->processOrder();
	international->processOrder();

	delete local;
	delete international;
}