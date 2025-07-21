#include<bits/stdc++.h>
using namespace std;

class FoodItem{
public:
	virtual string getDescription() = 0;
	virtual double getPrice() = 0;
	virtual ~FoodItem() = default;
};

class Pizza : public FoodItem {
public:
	string getDescription() override {
		return "This is a pizza.";
	}
	double getPrice() override {
		return 20.0;
	}
};

class Burger : public FoodItem {
public:
	string getDescription() override {
		return "This is a burger. ";
	}
	double getPrice() override {
		return 15.0;
	}
};

class Decorator : public FoodItem {
protected:
	FoodItem *baseItem;
public:
	Decorator(FoodItem *item) : baseItem(item) {}
	~Decorator(){
		delete baseItem;
	}
};

class ExtraCheeseDecorator : public Decorator {
private:
	double extraCheesePrice;
public:
	ExtraCheeseDecorator(FoodItem *baseItem, double price): Decorator(baseItem), extraCheesePrice(price) {}
	string getDescription() override {
		return baseItem->getDescription() + " With extra cheese";
	}
	double getPrice() override {
		return baseItem->getPrice() + extraCheesePrice;
	}
};

class ExtraSauceDecorator : public Decorator {
private:
	double extraSaucePrice;
public:
	ExtraSauceDecorator(FoodItem *baseItem, double price): Decorator(baseItem), extraSaucePrice(price) {}
	string getDescription() override {
		return baseItem->getDescription() + " With extra Sauce";
	}
	double getPrice() override {
		return baseItem->getPrice() + extraSaucePrice;
	}
};

int main(){
	FoodItem* pizza = new Pizza();
	pizza = new ExtraCheeseDecorator(pizza, 7);
	pizza = new ExtraSauceDecorator(pizza, 3);
	cout<<pizza->getDescription()<<"\n";
	cout<<pizza->getPrice()<<"\n";
	delete pizza;
	cout<<"---------------\n";
	FoodItem* burger = new Burger();
	burger = new ExtraCheeseDecorator(burger, 7);
	burger = new ExtraSauceDecorator(burger, 3);
	cout<<burger->getDescription()<<"\n";
	cout<<burger->getPrice()<<"\n";
	delete burger;
}