#include<bits/stdc++.h>
using namespace std;

class Book {
	int id;
	string name;
protected:
	Book(int id, string name): id(id), name(name) {}
public:
	int getId(){
		return id;
	}
	string getName(){
		return name;
	}
	virtual void printDetails() = 0; 
};

class PaperBack : public Book {
int weight; // weight in lbs
public:
	PaperBack(int id, string name, int weight): Book(id, name), weight(weight) {}
	int getWeight(){
		return weight;
	}
	void printDetails() override{
		cout<<"Paperback with id: "<<this->getId()<<" ,name: "<<this->getName()<<" ,weight"<<weight<<" lbs"<<endl;
	}
};

class EBook: public Book {
int size; // size in MBs
public:
	EBook(int id, string name, int size): Book(id, name), size(size) {}
	int getSize(){
		return size;
	}
	void printDetails() override {
		cout<<"Ebook with id: "<<this->getId()<<" ,name: "<<this->getName()<<" ,size"<<size<<" MBs"<<endl;
	}
};

enum class BookTypes {
	PAPERBACK,
	EBOOK
};

class BookFactory {
public:
	static Book* createBook(BookTypes type, int id, string name){
		if(type == BookTypes::PAPERBACK){
			return new PaperBack(id, name, 2);
		} else if(type == BookTypes::EBOOK){
			return new EBook(id, name, 2);
		} else {
			return nullptr;
		}
	}
};

// Singleton -> this of this like a database of books
class BookManagementSystem {
private:
	static BookManagementSystem* instance;
	BookManagementSystem(){
		cout<<"Creating singleton book management system"<<endl;
	}
	map<int, Book*> books;
	static mutex mtx;
public:
	static BookManagementSystem* getInstance(){
		if(instance == nullptr){
			mtx.lock();
			if(instance == nullptr){
				instance = new BookManagementSystem();
			}
			mtx.unlock();
		}
		return instance;
	}
	bool addBook(Book* book){
		int id = book->getId();
		// validation and possibly return false
		books[id] = book;
		return true;
	}

	void printBooks(){
		for(auto& k_v: books){
			Book* book = k_v.second;
			book->printDetails();
		}
	}
};

BookManagementSystem* BookManagementSystem::instance = nullptr;
mutex BookManagementSystem::mtx;

int main(){
	Book* book1 = BookFactory::createBook(BookTypes::PAPERBACK, 1, "Title 1");
	Book* book2 = BookFactory::createBook(BookTypes::EBOOK, 2, "Title 2");

	BookManagementSystem* bms = BookManagementSystem::getInstance();

	bms->addBook(book1);
	bms->addBook(book2);

	bms->printBooks();
}