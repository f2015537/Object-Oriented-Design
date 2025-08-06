#include<bits/stdc++.h>
using namespace std;

class Operation {
public:
	virtual double compute(double a, double b) = 0;
	virtual string getSymbol() = 0;
};

class Addition : public Operation {
public:
	double compute(double a, double b) override {
		return a + b;
	}
	string getSymbol() override {
		return "+";
	}
};

class Multiplication : public Operation {
public:
	double compute(double a, double b) override {
		return a * b;
	}
	string getSymbol() override {
		return "*";
	}
};


// Singleton
class Calculator {
private:
	static Calculator* instance;
	Calculator() = default;
	map<string,Operation*> ops;
public:
	static Calculator* getInstance(){
		if(instance == nullptr){
			instance = new Calculator();
		}
		return instance;
	}

	void registerOperation(Operation* newOperation){
		ops[newOperation->getSymbol()] = newOperation;
	}

	double compute(string operationSymbol, double a, double b){
		if(ops.find(operationSymbol) == ops.end()) throw runtime_error("Operation not supported");
		return ops[operationSymbol]->compute(a,b);
	}
};

Calculator* Calculator::instance = nullptr;

int main(){
	Calculator* calc = Calculator::getInstance();

	Operation* op1 = new Multiplication();

	calc->registerOperation(op1);

	cout<<calc->compute("+", 2, 3);
}
