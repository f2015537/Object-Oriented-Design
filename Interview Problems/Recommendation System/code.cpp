#include<bits/stdc++.h>
using namespace std;

class Content {
protected:
	string name;
public:
	Content(string name): name(name) {}
	virtual void displayDetails() = 0;
};

class TVShow : public Content {
int numberOfEpisodes;
public:
	TVShow(string name, int numberOfEpisodes): Content(name), numberOfEpisodes(numberOfEpisodes) {}
	void displayDetails() override {
		cout << "TV Show: " <<name <<" with " << numberOfEpisodes << "episodes" << endl;
	}
};

class Movie : public Content {
	int duration;
public:
	Movie(string name, int duration): Content(name), duration(duration) {}
	void displayDetails() override {
		cout << "Movie: " <<name <<" running " << duration << " minutes long." << endl;
	}
};

class ContentFactory {
public:
	static Content* createMovie(string name, int duration) {
		return new Movie(name, duration);
	}

	static Content* createTVShow(string name, int numberOfEpisodes) {
		return new TVShow(name, numberOfEpisodes);
	}
};

class User {
protected:
	string name;
public:
	User(string name): name(name) {}

	virtual void displayDetails() = 0;
};

class Customer : public User {
	vector<Content*> watchHistory;
public:
	Customer(string name): User(name) {}

	void addToWatchHistory(Content* content){
		watchHistory.push_back(content);
	}

	// TODO - remove from watch history

	vector<Content*> getWatchHistory(){
		return watchHistory;
	}

	virtual void displayDetails(){
		cout<<"Customer "<<name<<" has watched shows\n";
		for(Content* content: watchHistory){
			content->displayDetails();
		}
	}
};

// Strategy
class RecommendationStrategy {
public:
	virtual Content* recommendContent(vector<Content*> watchHistory, vector<Content*> availableShows) = 0; 
};

class ConcreteStrategy1 : public RecommendationStrategy {
	Content* recommendContent(vector<Content*> watchHistory, vector<Content*> availableShows){
		// apply business logic here
		return nullptr;
	}
};

// TODO -> other concrete strategies
// Singleton
class RecommendationManager {
private:
	static RecommendationManager* instance;
	RecommendationStrategy* strategy = nullptr;
	RecommendationManager() = default;
public:
	static RecommendationManager* getInstance(){
		if(instance == nullptr){
			instance = new RecommendationManager();
		}
		return instance;
	}

	void setStrategy(RecommendationStrategy* strategy){
		this->strategy = strategy;
	}

	Content* recommendContent(Customer* customer, vector<Content*> availableShows){
		return strategy->recommendContent(customer->getWatchHistory(), availableShows);
	}
};

RecommendationManager* RecommendationManager::instance = nullptr;

int main(){

}