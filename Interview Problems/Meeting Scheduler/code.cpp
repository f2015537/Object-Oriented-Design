#include<bits/stdc++.h>
using namespace std;

enum class MeetingType {
	SHORT,
	LONG
};

enum class MeetingStatus {
	NOT_STARTED,
	IN_PROGRESS,
	COMPLETED
};


class User {
	string name;
public:
	User(string name): name(name) {}
	void notify(int id){
		cout<<"User "<<name<<" notified about newStatus of meeting id "<<id<<endl;
	}
};

class Meeting {
	int id;
	int startTime; // timstamp in minutes
	int endTime;
	vector<User*> participants;
	MeetingStatus status;
public:
	Meeting(int id, int startTime, int endTime): id(id), startTime(startTime), endTime(endTime), status(MeetingStatus::NOT_STARTED) {}
	
	void addParticipant(User* participant){
		participants.push_back(participant);
	}

	void updateStatus(MeetingStatus newStatus){ // Observer design pattern
		status = newStatus;
		for(User* participant: participants){
			participant->notify(id);
		}
	}
};


// Assume we support only 2 types of meetings 
class ShortMeeting : public Meeting {
public:
	ShortMeeting(int id, int startTime): Meeting(id, startTime, startTime + 30) {}
};

class LongMeeting : public Meeting {
public:
	LongMeeting(int id, int startTime): Meeting(id, startTime, startTime + 60) {}
};

// Factory design pattern
class MeetingFactory {
public:
	static Meeting* createMeeting(int id, int startTime, MeetingType type){
		if(type == MeetingType::SHORT){
			return new ShortMeeting(id, startTime);
		} else if(type == MeetingType::LONG){
			return new LongMeeting(id, startTime);
		} else {
			return nullptr;
		}
	}
};

class MeetingRoom {
	int id;
	vector<Meeting*> meetings;
public:
	MeetingRoom(int id): id(id) {}

	bool addMeeting(Meeting* meeting){
		// if meeting already exists or conflicts with another meeting 
		// return false
		meetings.push_back(meeting);
		return true;
	}
};

// Singleton -> for now assuming one manager manages all meeting rooms
// Facade
class MeetingManager {
private:
	static MeetingManager* instance;
	vector<MeetingRoom*> meetingRooms;
	static mutex mtx;
	MeetingManager() = default;
public:
	static MeetingManager* getInstance(){
		if(instance == nullptr){
			mtx.lock();
			if(instance == nullptr){
				instance = new MeetingManager();				
			}
			mtx.unlock();
		}
		return instance;
	}
	bool addMeetingRoom(MeetingRoom* meetingRoom){
		// assuming validation passes
		meetingRooms.push_back(meetingRoom);
		return true;
	}
	bool scheduleMeeting(MeetingRoom* meetingRoom, Meeting* meeting){
		return meetingRoom->addMeeting(meeting);
	}
};

MeetingManager* MeetingManager::instance = nullptr;
mutex MeetingManager::mtx;

int main(){
	MeetingManager* mgr = MeetingManager::getInstance();
	MeetingRoom* room1 = new MeetingRoom(1);
	MeetingRoom* room2 = new MeetingRoom(2);

	Meeting* shortMeeting1 = MeetingFactory::createMeeting(1, 30, MeetingType::SHORT);
	Meeting* longMeeting1 = MeetingFactory::createMeeting(2, 70, MeetingType::LONG);

	User* user1 = new User("Test User 1");
	User* user2 = new User("Test User 2");

	// ideally this should be done by the meeting manager

	shortMeeting1->addParticipant(user1);
	shortMeeting1->addParticipant(user2);

	shortMeeting1->updateStatus(MeetingStatus::IN_PROGRESS);

	room1->addMeeting(shortMeeting1);

	mgr->addMeetingRoom(room1);
	mgr->addMeetingRoom(room2);
}