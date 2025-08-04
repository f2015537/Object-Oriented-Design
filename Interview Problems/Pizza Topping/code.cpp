#include<bits/stdc++.h>
using namespace std;

class FoodItem {
public:
	virtual double getPrice() = 0;
	virtual string getDescription() = 0;
	virtual ~FoodItem() = default;
};

class Pizza : public FoodItem {
	string name;
	double price;
public:
	Pizza(string name, double price):
	name(name), price(price) {}

	string getDescription() override {
		return name;
	}

	double getPrice() override {
		return price;
	}
};

class Decorator : public FoodItem {
protected:
	FoodItem* baseItem;
	double price;
public:
	Decorator(FoodItem* baseItem, double price): 
	baseItem(baseItem), price(price) {}

	double getPrice() override {
		return baseItem->getPrice() + price;
	}
};

class ExtraCheeseDecorator : public Decorator {
public:
	ExtraCheeseDecorator(FoodItem* baseItem, double price):
	Decorator(baseItem, price) {}

	string getDescription() override {
		return baseItem->getDescription() + " with extra cheese" ;
	}
};

enum class PizzaOfferings {
	VEGGIE,
	ALFREDO,
	CHEESE
};

class PizzaFactory {
public:
	static Pizza* createPizza(PizzaOfferings type){
		if(type == PizzaOfferings::VEGGIE){
			return new Pizza("Veggie", 15);
		}
		// else if for other pizza types
	}
};

class KitchenManager {
private:
	static KitchenManager* instance;
	static mutex mtx;
	KitchenManager() = default;
public:
	static KitchenManager* getInstance(){
		if(instance == nullptr){
			mtx.lock();
			if(instance == nullptr){
				instance = new KitchenManager();
			}
			mtx.unlock();
		}
		return instance;
	}

	Pizza* makePizza(PizzaOfferings type){
		Pizza* pizza = PizzaFactory::createPizza(type);
		return pizza;
	}

	FoodItem* addToppings(FoodItem* baseItem, vector<string> toppings){
		for(string topping: toppings){
			if(topping == "Cheese"){ // ideally enum
				baseItem = new ExtraCheeseDecorator(baseItem, 5);
			}	
		}
		return baseItem;
	}
};


KitchenManager* KitchenManager::instance = nullptr;
mutex KitchenManager::mtx;

int main(){
	FoodItem* pizza = new Pizza("3 Cheese Pizza", 15);
	pizza = new ExtraCheeseDecorator(pizza, 5);

	cout<<pizza->getDescription()<<endl;
	cout<<pizza->getPrice()<<endl;
}