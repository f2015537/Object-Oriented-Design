#include<bits/stdc++.h>
using namespace std;

class ActionListenerCommand{
public:
	virtual void execute() = 0;
	virtual ~ActionListenerCommand() = default;
};


// Receiver - performing the operation
class Document {
private:
	string name;
public:
	Document(string name): name(name) {}
	void open() {
		cout << "Document "<<name<<" opened\n";
	}

	void save() {
		cout << "Document "<<name<<" saved\n";
	}
};

// Concrete command
class ActionOpen : public ActionListenerCommand {
private:
	Document* doc;

public:
	ActionOpen(Document* document): doc(document) {}

	void execute() override {
		doc->open();
	}
};

// Concrete command
class ActionSave : public ActionListenerCommand {
private:
	Document* doc;

public:
	ActionSave(Document* document): doc(document) {}

	void execute() override {
		doc->save();
	}
};

// Invoker
class MenuOptions {
private:
	vector<ActionListenerCommand*> commands;

public:
	void addCommand(ActionListenerCommand* command){
		commands.push_back(command);
	}

	void executeCommands(){
		for(ActionListenerCommand* command : commands){
			command->execute();
		}
	}
};

int main(){
	Document doc1("test document");
	ActionListenerCommand* command1 = new ActionOpen(&doc1);
	ActionListenerCommand* command2 = new ActionSave(&doc1);

	MenuOptions menuOptions1;
	menuOptions1.addCommand(command1);
	menuOptions1.addCommand(command2);

	menuOptions1.executeCommands();

	delete command1;
	delete command2;
}