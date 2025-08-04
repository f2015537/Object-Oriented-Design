#include<bits/stdc++.h>
using namespace std;

class FileSystemComponent {
protected:
	string name;
public:
	FileSystemComponent(string name): name(name) {}
	virtual int getSize() = 0;
	virtual void listContents() = 0;
	virtual ~FileSystemComponent() = default;
};

class File : public FileSystemComponent {
	string text;
public:
	File(string name, string text): FileSystemComponent(name), text(text) {}
	int getSize() override {
		return text.size();
	}
	void listContents() override {
		cout<<"File "<<name<<" contains\n"<<text<<endl;
	}
};

class Directory : public FileSystemComponent {
	vector<FileSystemComponent*> components;
public:
	Directory(string name): FileSystemComponent(name) {}

	void addComponent(FileSystemComponent* component){
		components.push_back(component);
	}

	int getSize() override {
		int ans = 0;
		for(FileSystemComponent* component: components){
			ans += component->getSize();
		}
		return ans;
	}

	void listContents() override {
		cout<<"Directory "<<name<<" contains "<<endl;
		for(FileSystemComponent* component: components){
			component->listContents();
		}
	}
};

class Observer {
	int id;
public:
	Observer(int id): id(id) {}
	virtual void notify(string message) = 0;
	virtual ~Observer() = default;
};

class Admin : public Observer {
	string name;
public:
	Admin(int id, string name): Observer(id), name(name) {}

	void notify(string message) override {
		cout<<"Admin "<<name<<" notified: "<<message<<endl;
	}
};

class ObserverFactory {
public:
	static Observer* createAdmin(int id, string name){
		return new Admin(id, name);
	}
};


enum class FileSystem_Statuses {
	LOADING,
	LOADED,
	ERROR
};

// Singleton, Facade
class FileSystemManager {
private:
	static FileSystemManager* instance;
	static mutex mtx;
	vector<FileSystemComponent*> components;
	FileSystem_Statuses status;
	vector<Observer*> observers;
	FileSystemManager(): status(FileSystem_Statuses::LOADING) {}
public:
	static FileSystemManager* getInstance(){
		if(instance == nullptr){
			mtx.lock();
			if(instance == nullptr){
				instance = new FileSystemManager();				
			}
			mtx.unlock();
		}
		return instance;
	}

	void setStatus(FileSystem_Statuses newStatus){
		status = newStatus;
		for(Observer* observer : observers){
			observer->notify("Status of FileSystemManager changed");
		}
	}

	void addComponent(FileSystemComponent* component){
		components.push_back(component);
	}

	void listAllContents(){
		for(FileSystemComponent* component: components){
			component->listContents();
		}
	}

	void deleteComponent(FileSystemComponent* component){
		components.erase(find(components.begin(), components.end(), component));
	}

	void attachObserver(Observer* observer){
		observers.push_back(observer);
	}

	int getSizeOfComponent(FileSystemComponent* component){
		return component->getSize();
	}

	int getSizeofAllComponents(){
		int ans = 0;
		for(FileSystemComponent* component: components){
			ans += getSizeOfComponent(component);
		}
		return ans;
	}
};

FileSystemManager* FileSystemManager::instance = nullptr;
mutex FileSystemManager::mtx;

// Composite, Singleton, Observer, Facade, Factory

int main(){
	auto fs = FileSystemManager::getInstance();

	Observer* admin = ObserverFactory::createAdmin(1, "Divyam");
	fs->attachObserver(admin);

	fs->setStatus(FileSystem_Statuses::LOADED);

	FileSystemComponent* file1 = new File("readme.txt", "This is a README");
	FileSystemComponent* file2 = new File("log.txt", "Log started");

	Directory* dir = new Directory("src");
	dir->addComponent(file2);

	fs->addComponent(file1);
	fs->addComponent(dir);

	cout << "\n--- Listing All Contents ---\n";
	fs->listAllContents();

	cout << "\n--- Total size ---\n";
	cout<<fs->getSizeofAllComponents()<<endl;

	cout << "\n--- Deleting file1 ---\n";
	fs->deleteComponent(file1);
	delete file1;

	cout << "\n--- Final Contents ---\n";
	fs->listAllContents();

	// Cleanup
	delete file2;
	delete dir;
	delete admin;
}

