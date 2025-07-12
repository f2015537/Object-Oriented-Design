#include<bits/stdc++.h>
using namespace std;

class ProductPrototype {
public:
	virtual ProductPrototype* clone() = 0;
	virtual void display() = 0;
	virtual ~ProductPrototype() = default;
};

class Product : public ProductPrototype {
private:
	string name;
	double price;

public:
	Product(const string& name, double price): name(name), price(price) {};

	ProductPrototype* clone() override {
		return new Product(*this);
	}

	void display(){
		cout<<"Product details: "<<name<<" $"<<price<<"\n";
	}
};

int main(){
	ProductPrototype* product1 = new Product("Phone", 999.99);
	ProductPrototype* product2 = new Product("Watch", 100);
	cout<<"Original Products\n";
	product1->display();
	product2->display(); 

	ProductPrototype* product1Copy = product1->clone();
	ProductPrototype* product2Copy = product2->clone();
	cout<<"Cloned Products\n";
	product1Copy->display();
	product2Copy->display();

	delete product1;
	delete product2;
	delete product1Copy;
	delete product2Copy;

	return 0;
}