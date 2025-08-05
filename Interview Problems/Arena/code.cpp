#include<bits/stdc++.h>
using namespace std;

enum class UserTypes {
	PLAYER,
	ADMIN
};

class User {
protected:
	string name;
public:
	User(string name): name(name) {}
	virtual void notify(string message) = 0;
};

class Player : public User {
	int health;
public:
	Player(string name): User(name), health(100) {}
	Player(string name, int health): User(name), health(health) {}
	virtual void notify(string message){
		cout<<"Player "<<name<<"notified: "<<message<<endl;
	}
};


// TODO -> Concrete class for Admin

class UserFactory {
public:
	static Player* createPlayer(string name){
		return new Player(name);
	}
};

class DiceRollingStrategy {
	// TODO set seed -> use seed to generate randomess
public:
	virtual int rollDice() = 0;
};

class FairDiceRollingStrategy : public DiceRollingStrategy { // equal prob of getting 1 through 6
public:
	int rollDice() override {
		return rand() % 6 + 1;
	}
};

// TODO -> other conrete rolling strategies

class DiceUtility {
DiceRollingStrategy* strategy;
public:
	DiceUtility(DiceRollingStrategy* strategy): strategy(strategy) {}
	int rollDice(){
		return strategy->rollDice();
	}
};


// Singleton -> responsible for manging game state
class GameManager {
private:
	Player* p1;
	Player* p2;
	static GameManager* instance;
	static mutex mtx;
	DiceUtility* util;
	bool gameOver = false;
	GameManager() {
		p1 = UserFactory::createPlayer("Player 1");
		p2 = UserFactory::createPlayer("Player 2");
		util = new DiceUtility(new FairDiceRollingStrategy());
	}
public:
	static GameManager* getInstance(){
		if(instance == nullptr){
			mtx.lock();
			if(instance == nullptr){
				instance = new GameManager();
			}
			mtx.unlock();
		}
		return instance;
	}

	void playMove(Player* attacker, Player* defender){
		int attackerDiceValue = util->rollDice(); // TODO: provide seed
		int defenderDiceValue = util->rollDice(); // TODO: provide seed

		int attackPotency = 0; // some math to determin this
		int defensePotency = 0; // some math to determine this

		// defender's health reduces

		// defender dead -> notify defender and attacker -> gameOver = true
	}
};

GameManager* GameManager::instance = nullptr;
mutex GameManager::mtx;


// Design patterns covered -> Factory, Singleton, Observer, Strategy

int main(){

}