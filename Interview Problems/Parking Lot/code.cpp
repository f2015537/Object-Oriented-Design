#include<bits/stdc++.h>
using namespace std;

enum class ParkingSpotStatus {
	AVAILABLE,
	OCCUPIED
};

class Observer {
protected:
	int id;
public:
	Observer(int id): id(id) {}
	virtual void notify(string message) = 0;
	virtual ~Observer() = default;
};

class Admin : public Observer {
public:
	Admin(int id): Observer(id) {}
	void notify(string message){
		cout<<"Admin "<<id<<" notified: "<<message<<endl;
	}
};

class PricingStrategy {
public:
	virtual int determinePrice(int hours) = 0;
	virtual ~PricingStrategy() = default;
};

class NormalPricingStrat : public PricingStrategy {
public:
	int determinePrice(int hours) override {
		return hours * 10;
	}
};

class PremiumPricingStrat : public PricingStrategy {
public:
	int determinePrice(int hours) override {
		return hours * 15;
	}
};

class ParkingSpot {
	int id;
	ParkingSpotStatus status;
	vector<Observer*> observers;
	
public:
	PricingStrategy* strategy;
	ParkingSpot(int id, ParkingSpotStatus status, PricingStrategy* strategy): id(id), status(status), strategy(strategy) {}
	void updateStatus(ParkingSpotStatus newStatus){
		status = newStatus;
		string message = "Parking Spot" + to_string(id) + " has a new status";
		for(Observer* observer: observers){
			observer->notify(message);
		}
	}

	void attachObserver(Observer* observer){
		observers.push_back(observer);
	}

	virtual ~ParkingSpot() = default;
};

class CoveredParkingSpot : public ParkingSpot {
public:
	CoveredParkingSpot(int id, ParkingSpotStatus status, PricingStrategy* strategy): ParkingSpot(id, status, strategy) {}
};

class UncoveredParkingSpot : public ParkingSpot {
public:
	UncoveredParkingSpot(int id, ParkingSpotStatus status, PricingStrategy* strategy): ParkingSpot(id, status, strategy) {}
};

enum class PakringSpotType {
	COVERED,
	UNCOVERED
}; 

// Factory
class ParkingSpotFactory {
public:
	static ParkingSpot* createParkingSpot(PakringSpotType type, int id){
		if(type == PakringSpotType::COVERED){
			return new CoveredParkingSpot(id, ParkingSpotStatus::AVAILABLE, new PremiumPricingStrat());
		} else if(type == PakringSpotType::UNCOVERED){
			return new UncoveredParkingSpot(id, ParkingSpotStatus::AVAILABLE, new NormalPricingStrat());
		} else {
			return nullptr;
		}
	}
};

// Singleton
class ParkingManager {
private:
	static ParkingManager* instance;
	static mutex mtx;
	vector<ParkingSpot*> spots;
	ParkingManager() = default;
public:
	static ParkingManager* getInstance(){
		if(instance == nullptr){
			mtx.lock();
			if(instance == nullptr){
				instance = new ParkingManager();
			}
			mtx.unlock();
		}
		return instance;
	}

	void addParkingSpot(ParkingSpot* spot){
		spots.push_back(spot);
	}

	// remove Parking Spot

	void updateParkingSpotStatus(ParkingSpot* spot, ParkingSpotStatus newStatus){
		spot->updateStatus(newStatus);
	}
};

ParkingManager* ParkingManager::instance = nullptr;
mutex ParkingManager::mtx;

int main(){
	ParkingSpot* spot1 = ParkingSpotFactory::createParkingSpot(PakringSpotType::COVERED, 1);
	Observer* obs1 = new Admin(1);

	spot1->attachObserver(obs1);

	ParkingManager* mgr = ParkingManager::getInstance();

	mgr->addParkingSpot(spot1);
	mgr->updateParkingSpotStatus(spot1, ParkingSpotStatus::OCCUPIED);

	cout<<spot1->strategy->determinePrice(5);
}