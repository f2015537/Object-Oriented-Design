#include<bits/stdc++.h>
using namespace std;

class JSONAnalyticsTool {
private:
	string pJsonData;
public:
	void setJsonData(string jsonData){
		pJsonData = jsonData;
	}
	void analyzeData(){
		if(pJsonData.find("json") != string::npos){
			cout<<"Analysing JSON Data - "<<pJsonData<<endl;
		} else{
			cout<<"Incorrect format. Can't analyze"<<endl;
		}
	}
};

class AnalyticsTool {
public:
	virtual void analyzeData(string xmlData) = 0;
	virtual ~AnalyticsTool() = default;
};

class XMLToJSONAdapter : public AnalyticsTool {
private:
	JSONAnalyticsTool jsonAnalyticsTool;
public:
	 void analyzeData(string xmlData) override {
	 	cout<<"Converting the XML Data '" << xmlData <<"' to JSON Data!"<<endl;
	 	string newData = xmlData + " in json";
	 	jsonAnalyticsTool.setJsonData(newData);
	 	jsonAnalyticsTool.analyzeData();
	 }
};

int main()
{
    string xmlData = "Sample Data";
    JSONAnalyticsTool tool1;
    tool1.setJsonData(xmlData);
    tool1.analyzeData();

    cout<<"----------------------------------------------"<<endl;

    AnalyticsTool* tool2 = new XMLToJSONAdapter();
    tool2->analyzeData(xmlData);
    delete tool2;
    return 0;
}