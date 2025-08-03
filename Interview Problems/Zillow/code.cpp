#include<bits/stdc++.h>
using namespace std;

class Property {
public:
	int id;
	string name;
	Property(int id, string name): id(id), name(name) {}
	virtual void displayDetails(){
		cout<<"Property "<<id<<" Name "<<name<<": ";
	}
};

class Condo : public Property {
	int floor; // what floor the condo is on
	int building; // what building the Condo is in
public:
	Condo(int id, string name, int floor, int building): 
	Property(id, name), floor(floor), building(building) {}
	void displayDetails() override {
		Property::displayDetails();
		cout<<"Condo on floor "<<floor<<" in building "<<building<<endl;
	}
};

class TownHouse : public Property {
	int floors; // how many floors inside the downhouse
public:
	TownHouse(int id, string name, int floors): 
	Property(id, name), floors(floors) {}
	void displayDetails() override {
		Property::displayDetails();
		cout<<"Townhouse with "<<floors<<" floors."<<endl;
	}
};


enum class PropertyType {
	CONDO,
	TOWNHOUSE
};

class PropertyFactory {
public:
	static Property* createCondo(int id, string name, int floor, int building){
		return new Condo(id, name, floor, building);
	}
	static Property* createTownHouse(int id, string name, int floors){
		return new TownHouse(id, name, floors);
	}
};

struct Customer {
	int id;
	string name;
	Customer(int id, string name): id(id), name(name) {}
	void notify(string message){
		cout<<name<<": "<<message<<endl;
	}
};

// Singleton
class PropertyManager {
private:
	set<Property*> properties;
	map<Property*,Customer*> owners;
	static PropertyManager* instance;
	PropertyManager() = default;

public:
	static PropertyManager* getInstance(){
		if(instance == nullptr){
			instance = new PropertyManager();
		}
		return instance;
	}

	bool addProperty(Property* property, Customer* owner){
		// TODO: Validation -> possibly return false
		properties.insert(property);
		owners[property] = owner;
		return true;
	}

	void removeProperty(Property* property){
		// TODO: Validation -> possibly return false
		properties.erase(property);
		owners.erase(property);
	}

	void displayProperties(){
		for(Property* property: properties){
			property->displayDetails();
			cout<<"Owned by "<<owners[property]->name<<endl;
		}
	}

	void transferOwnership(Customer* buyer, Customer* seller, Property* property){
		owners[property] = buyer;
		string message = "You sold property " + property->name;
		seller->notify(message);
		message = "You bought property " + property->name;
		buyer->notify(message);
	}
};

PropertyManager* PropertyManager::instance = nullptr;

int main(){
	Property* th1 = PropertyFactory::createTownHouse(1, "th1", 3);
	Property* c1 = PropertyFactory::createCondo(2,"c1",5,5);
	PropertyManager* mgr = PropertyManager::getInstance();
	Customer* customer1 = new Customer(1, "John");
	Customer* customer2 = new Customer(2, "Cassie");
	mgr->addProperty(th1,customer1);
	mgr->addProperty(c1, customer2);
	mgr->transferOwnership(customer1, customer2, c1);
	mgr->displayProperties();
}