#include<bits/stdc++.h>
using namespace std;

enum class TrainTypes {
	REGULAR,
	EXPRESS
};

class Train {
private:
	int maxSpeed;
	int maxStops;
	int compartments;
	int seatsPerCompartment;
public:
	Train(int maxSpeed, int maxStops, int compartments, int seatsPerCompartment) :
	maxSpeed(maxSpeed), maxStops(maxStops), compartments(compartments), seatsPerCompartment(seatsPerCompartment) {}
};

class RegularTrain : public Train {
public:
	RegularTrain(): Train(80, 20, 10, 50) {}
};

class ExpressTrain : public Train {
public:
	ExpressTrain(): Train(100, 10, 5, 25) {}
};

class TrainFactory{
public:
	static Train* createTrain(TrainTypes type){
		if(type == TrainTypes::REGULAR){
			return new RegularTrain();
		} else if(type == TrainTypes::EXPRESS){
			return new ExpressTrain();
		}
		return nullptr;
	}
};


// Singleton
class TrainManager {
private:
	static TrainManager* instance;
	static mutex mtx;
	unordered_map<int,Train*> trains;
	TrainManager() = default;
public:
	static TrainManager* getInstance(){
		if(instance == nullptr){
			mtx.lock();
			if(instance == nullptr){
				instance = new TrainManager();
			}
			mtx.unlock();
		}
		return instance;
	}

	void addTrain(int id, Train* train){
		trains[id] = train;
	}
};

enum class BookingStatus {
	INITIATED,
	PROCESSING,
	CONFIRMED
};

string to_string(BookingStatus status) {
    switch(status) {
        case BookingStatus::INITIATED: return "INITIATED";
        case BookingStatus::PROCESSING: return "PROCESSING";
        case BookingStatus::CONFIRMED: return "CONFIRMED";
        default: return "Unknown";
    }
}

class Observer {
public:
	virtual void update(BookingStatus status) = 0;
};

class Customer : public Observer {
public:
	virtual void update(BookingStatus status) override {
		cout<<"Customer updated about new booking status: "<<to_string(status)<<endl;
	}
};

// Observer
class BookingManager {
private:
	BookingStatus status;
	vector<Observer*> observers;
public:
	BookingManager(): status(BookingStatus::INITIATED) {}
	void updateStatus(BookingStatus newStatus){
		status = newStatus;
		for(Observer* observer : observers){
			observer->update(newStatus);
		}
	}
	void attachObserver(Observer* observer){
		observers.push_back(observer);
	}
};

TrainManager* TrainManager::instance = nullptr;
mutex TrainManager::mtx;

int main(){
	TrainManager* trainManager = TrainManager::getInstance();
	Train* train1 = TrainFactory::createTrain(TrainTypes::REGULAR);
	Train* train2 = TrainFactory::createTrain(TrainTypes::EXPRESS);
	trainManager->addTrain(1,train1);
	trainManager->addTrain(2,train2);

	BookingManager* mgr = new BookingManager();
	Observer* customer1 = new Customer();
	mgr->attachObserver(customer1);
	mgr->updateStatus(BookingStatus::PROCESSING);
	mgr->updateStatus(BookingStatus::CONFIRMED);
	return 0;
}