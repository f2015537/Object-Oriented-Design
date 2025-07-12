#include<bits/stdc++.h>
using namespace std;

class Desktop {
public:
	string ram, processor, motherboard;
	void display(){
		cout<<"Specs:\n";
		cout<<"Ram: "<<ram<<"\n";
		cout<<"Processor: "<<processor<<"\n";
		cout<<"Motherboard: "<<motherboard<<"\n\n";
	}

};

class DesktopBuilder{
protected:
	Desktop desktop;
public:
	virtual void buildRam() = 0;
	virtual void buildProcessor() = 0;
	virtual void buildMotherboard() = 0;

	Desktop getDesktop(){
		return desktop;
	}
};

class DellDesktopBuilder: public DesktopBuilder{
public:
	void buildRam() override {
		desktop.ram = "Dell Ram";
	}
	void buildProcessor() override {
		desktop.processor = "Dell Processor";
	}
	void buildMotherboard() override {
		desktop.motherboard = "Dell Motherboard";
	}
};

class HpDesktopBuilder: public DesktopBuilder{
public:
	void buildRam() override {
		desktop.ram = "Hp Ram";
	}
	void buildProcessor() override {
		desktop.processor = "Hp Processor";
	}
	void buildMotherboard() override {
		desktop.motherboard = "Hp Motherboard";
	}
};

class DesktopDirector {
public:
	static Desktop buildDesktop(DesktopBuilder &builder){
		builder.buildRam();
		builder.buildProcessor();
		builder.buildMotherboard();
		return builder.getDesktop();
	}
};

int main(){
	DellDesktopBuilder dellBuilder;
	DesktopDirector::buildDesktop(dellBuilder).display();
	HpDesktopBuilder hpBuilder;
	DesktopDirector::buildDesktop(hpBuilder).display();
}