// Requirements - 
// Calendar with pages for each month
// February has 29 days for leap years
// Calnedar manager to manage calendars (If time permits) - Stretch

#include<bits/stdc++.h>
using namespace std;

enum class Month {
	JANUARY,
	FEBRUARY
};

class CalendarPage {
protected:
	Month month;
	int days;
	int year;
public:
	CalendarPage(Month month, int days, int year): month(month), days(days), year(year) {}
	int getDays(){
		return days;
	}
};

class JanuaryPage : public CalendarPage {
public:
	JanuaryPage(int year): CalendarPage(Month::JANUARY, 31, year) {} 
};

class FebruaryPage : public CalendarPage {
public:
	FebruaryPage(int year) : CalendarPage(Month::FEBRUARY, (year % 4 == 0) ? 29 : 28, year) {} 
};

// TODO - Other pages later

class CalendarPageFactory {
public:
	static CalendarPage* createCalendarPage(Month month, int year){
		if(month == Month::JANUARY){
			return new JanuaryPage(year);
		} else if(month == Month::FEBRUARY){
			return new FebruaryPage(year);
		} else {
			return nullptr;
		}
	}
};

class Calendar {
	vector<CalendarPage*> pages;
	int year;
	static vector<Month> months;
public:
	Calendar(int year): year(year) {
		for(Month month: months){
			pages.push_back(CalendarPageFactory::createCalendarPage(month, year));
		}
	}

	int getDays(){
		int days = 0;
		for(CalendarPage* page: pages){
			days += page->getDays();
		}
		return days;
	}
};

vector<Month> Calendar::months = {
		Month::JANUARY,
		Month::FEBRUARY
};


// Singleton
class CalendarManager {
private:
	// vector<Calendar*> calendars;
	map<int, Calendar*> calendars;
	static CalendarManager* instance;
	CalendarManager() = default; // TODO -> Make thread safe
public:
	static CalendarManager* getInstance(){
		if(instance == nullptr){
			instance = new CalendarManager();
		}
		return instance;
	}

	void addCalendar(int year){
		// calendars.push_back(new Calendar(year));
		calendars[year] = new Calendar(year);
	}

	int getCalendarDays(int year){
		return calendars[year]->getDays();
	}
};

CalendarManager* CalendarManager::instance = nullptr;

int main(){
	CalendarManager* mgr = CalendarManager::getInstance();
	mgr->addCalendar(2025);
	cout<<mgr->getCalendarDays(2025);
}