#include<bits/stdc++.h>
using namespace std;

//  Strategy
class MovementStrategy {
public:
	virtual void move(int src, int dest) = 0;
};

// 
class MovementStrategy1 : public MovementStrategy {
public:
	virtual void move(int src, int dest) override {
		cout<<"Moving from "<<src<<" to "<<dest<<" using MovementStrategy1."<<endl;
	}
};

class MovementStrategy2 : public MovementStrategy {
public:
	virtual void move(int src, int dest) override {
		cout<<"Moving from "<<src<<" to "<<dest<<" using MovementStrategy2."<<endl;
	}
};

// Factory
class MovementStrategyFactory {
public:
	static MovementStrategy* createStrategy(int type){
		if(type == 1){
			return new MovementStrategy1();
		} else if(type == 2){
			return new MovementStrategy2();
		} else {
			return nullptr;
		}
	}
};


enum class Elevator_Status {
	IDLE,
	MOVING,
	UNDER_MAINTENANCE
};

class Elevator {
	int id;
	MovementStrategy* strategy;
	Elevator_Status status;
public:
	Elevator(int id, MovementStrategy* strategy): id(id), strategy(strategy) {}
	void move(int src, int dest){
		cout<<"Elevator with id = "<<id<<" ";
		strategy->move(src,dest);
	}
	void setStatus(Elevator_Status newStatus){
		status = newStatus;
	}
};

// Observer
class Admin {
	int id;
public:
	Admin(int id): id(id) {}
	void notify(int elevator_id) {
		cout<<"Admin "<<id<<" notified about status change in elevator "<<
		elevator_id<<endl;
	}
};

// Singleton
class ElevatorManager {
	unordered_map<int, Elevator*> elevators;
	static ElevatorManager* instance;
	static mutex mtx;
	vector<Admin*> admins;
	ElevatorManager() = default;
public:
	static ElevatorManager* getInstance(){
		if(instance == nullptr){
			mtx.lock();
			if(instance == nullptr){
				instance = new ElevatorManager();				
			}
			mtx.unlock();
		}
		return instance;
	}

	bool addElevator(int id, Elevator* elevator){
		if(elevators.find(id) != elevators.end()) return false;
		elevators[id] = elevator;
		return true;
	}

	bool removeElevator(int id){
		if(elevators.find(id) == elevators.end()) return false;
		elevators.erase(id);
		return true;
	}

	void moveElevator(int id, int src, int dest){
		Elevator* elevator = elevators[id];
		elevator->move(src, dest);
	}

	void setStatus(int id, Elevator_Status status){
		Elevator* elevator = elevators[id];
		elevator->setStatus(status);
		for(Admin* admin: admins){
			admin->notify(id);
		}
	}

	void addAdmin(Admin* admin){
		admins.push_back(admin);
	}
};

ElevatorManager* ElevatorManager::instance = nullptr;
mutex ElevatorManager::mtx;

int main(){
	ElevatorManager* mgr = ElevatorManager::getInstance();
	Elevator* elevator1 = new Elevator(1, MovementStrategyFactory::createStrategy(1));
	Elevator* elevator2 = new Elevator(2, MovementStrategyFactory::createStrategy(2));

	mgr->addElevator(1,elevator1);
	mgr->addElevator(2,elevator2);

	mgr->moveElevator(1, 5, 10);
	mgr->moveElevator(2, 3, 5);

	Admin* admin1 = new Admin(1);
	Admin* admin2 = new Admin(2);

	mgr->addAdmin(admin1);
	mgr->addAdmin(admin2);

	mgr->setStatus(1, Elevator_Status::IDLE);
	mgr->setStatus(2, Elevator_Status::MOVING);
}