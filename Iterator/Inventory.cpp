#include<bits/stdc++.h>
using namespace std;

class Product {
private:
	string name;
	double price;

public:
	Product(const string& name, double price): name(name), price(price) {}
	const string& getName() const {
		return name;
	}

	double getPrice() const {
		return price;
	}
};


// Interface
class Iterator{
public:
	virtual ~Iterator() = default;
	virtual bool hasNext() = 0;
	virtual Product* next() = 0;
	virtual Product* first() = 0;
};

class ProductIterator : public Iterator {
private:
	vector<Product*> products;
	size_t current;

public:
	ProductIterator(vector<Product*> &products): products(products), current(0) {}

	bool hasNext() override {
		return current < products.size();
	}

	Product* next() override {
		if (hasNext()) {
			return products[current++];
		}
		return nullptr;
	}

	Product* first() override {
	    current = 0;
	    return next();
	}
};


// Aggregate class that stores products and provides an iterator
class Inventory {
private:
    vector<Product*> products;
public:
    void addProduct(Product* product) {
        products.push_back(product);
    }

    Iterator* createIterator() {
        return new ProductIterator(products);
    }
};

int main(){
    // Create some products
    Product product1("Laptop", 99999.99);
    Product product2("Smartphone", 49999.99);
    Product product3("Headphones", 7999.99);

    // Create an inventory and add products
    Inventory inventory;
    inventory.addProduct(&product1);
    inventory.addProduct(&product2);
    inventory.addProduct(&product3);

    // Create an iterator and iterate over the products
    Iterator* iterator = inventory.createIterator();
	for (Product* p = iterator->first(); p != nullptr; p = iterator->next()) {
	    cout << "Product: " << p->getName()
	         << ", Price: $" << p->getPrice() << endl;
	}

    delete iterator;

    return 0;
}