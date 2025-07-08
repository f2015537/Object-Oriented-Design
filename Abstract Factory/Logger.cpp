#include<bits/stdc++.h>
using namespace std;

class IButton{
public:
	virtual void pressButton() = 0;
	virtual ~IButton() = default;
};

class MacButton: public IButton{
public:
	void pressButton() override {
		cout<<"Mac button pressed\n";
	}
};

class WinButton: public IButton{
public:
	void pressButton() override {
		cout<<"Win button pressed\n";
	}
};

class ITextBox{
public:
	virtual void populateTextBox(const string& text) = 0;
	virtual ~ITextBox() = default;
};

class MacTextBox: public ITextBox{
public:
	void populateTextBox(const string& text) override{
		cout<<"Mac text: "<<text<<"\n";
	}
};

class WinTextBox: public ITextBox{
public:
	void populateTextBox(const string& text) override{
		cout<<"Win text: "<<text<<"\n";
	}
};

class IFactory {
public:
	virtual IButton* createButton() = 0;
	virtual ITextBox* createTextBox() = 0;
	virtual ~IFactory() = default;
};

class MacFactory: public IFactory {
	IButton* createButton(){
		return new MacButton();
	}
	ITextBox* createTextBox(){
		return new MacTextBox();
	}
};

class WinFactory: public IFactory {
	IButton* createButton(){
		return new WinButton();
	}
	ITextBox* createTextBox(){
		return new WinTextBox();
	}
};

class AbstractFactory {
public:
	static IFactory* createFactory(string type){
		if(type == "mac") return new MacFactory();
		else if(type == "win") return new WinFactory();
		else return nullptr;
	}
};


int main(){
	IFactory* factory = AbstractFactory::createFactory("mac");
	IButton* button = factory->createButton();
	ITextBox* textBox = factory->createTextBox();

	button->pressButton();
	textBox->populateTextBox("Divyam");

	delete textBox;
	delete button;
	delete factory;
}