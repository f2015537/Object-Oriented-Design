#include<bits/stdc++.h>
using namespace std;

class FurnitureItem {
public:
	virtual void printInfo() = 0;
	virtual ~FurnitureItem() = default;
};

class Table : public FurnitureItem{
public:
	void printInfo() override {
		cout<<"I am a table\n";
	}
};

class Chair : public FurnitureItem{
public:
	void printInfo() override {
		cout<<"I am a chair\n";
	}
};

class Sofa : public FurnitureItem{
public:
	void printInfo() override {
		cout<<"I am a sofa\n";
	}
};

class FurnitureFactory {
public:
	virtual FurnitureItem* createFurniture() = 0;
	virtual ~FurnitureFactory() = default;
};

class TableFactory : public FurnitureFactory {
public:
	FurnitureItem* createFurniture() override {
		return new Table();
	}
};

class ChairFactory : public FurnitureFactory {
public:
	FurnitureItem* createFurniture() override {
		return new Chair();
	}
};

class SofaFactory : public FurnitureFactory {
public:
	FurnitureItem* createFurniture() override {
		return new Sofa();
	}
};

int main(){
	FurnitureFactory* factory = new SofaFactory();
	FurnitureItem* item = factory->createFurniture();
	item->printInfo();

	delete item;
	delete factory;
}

