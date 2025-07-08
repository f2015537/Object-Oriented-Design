#include<bits/stdc++.h>
using namespace std;

class ILogger{
public:
	virtual void log(const string& msg) = 0;
	virtual ~ILogger() = default;
};

class InfoLogger : public ILogger {
public:
	void log(const string& msg) override {
		cout<<"Info: "<<msg<<"\n";
	}
};

class DebugLogger : public ILogger {
public:
	void log(const string& msg) override {
		cout<<"Debug: "<<msg<<"\n";
	}
};

class ErrorLogger : public ILogger {
public:
	void log(const string& msg) override {
		cout<<"Error: "<<msg<<"\n";
	}
};

class LoggerFactory {
public:
	static ILogger* createLogger(string type){
		if(type == "info"){
			return new InfoLogger();
		} else if(type == "debug"){
			return new DebugLogger();
		} else if(type == "error"){
			return new ErrorLogger();
		} else{
			return nullptr;
		}
	}
};

int main(){
	string type = "error"; // this can be from user input
	ILogger* logger = LoggerFactory::createLogger(type);
	logger->log("Hello");

	delete logger;
}