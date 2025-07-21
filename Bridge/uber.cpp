#include<bits/stdc++.h>
using namespace std;

class INavigator{
public:
	virtual void navigateTo(string destination) = 0;
};

class GoogleMaps : public INavigator {
public:
	void navigateTo(string destination){
		cout<<"Google maps\n";
	}
};

class AppleMaps : public INavigator {
public:
	void navigateTo(string destination){
		cout<<"Apple maps\n";
	}
};

class NavigationSystem {
protected:
	INavigator* navigationImpl = nullptr;
public:
	virtual void navigate(string destination) = 0;
	void setNavigationImpl(INavigator *impl)
    {
        navigationImpl = impl;
    }
};

class UberRide : public NavigationSystem {
private:
	string driverName;
public:
	UberRide(string driverName): driverName(driverName) {}
	void navigate(string destination){
		cout<<"Uber ride with " << driverName << " to " << destination << " using\n";
		if(navigationImpl){
			navigationImpl->navigateTo(destination);
		}
	}
};

class UberEats : public NavigationSystem
{
private:
    string restaurantName;

public:
    UberEats(string restaurantName) : restaurantName(restaurantName) {}

    void navigate(string destination)
    {
        cout << "Uber Eats delivery from " << restaurantName << " to " << destination << " using\n";
        if(navigationImpl){
	        navigationImpl->navigateTo(destination);        	
        }
    }
};

int main(){
    // Create an UberRide with a driver
    UberRide uber("Keerti");

    // Create an UberEats delivery
    UberEats uberEats("Pizza Palace");

    // Create different navigation implementations
    GoogleMaps googleMaps;
    AppleMaps appleMaps;

    // Set the navigation implementation for UberRide
    uber.setNavigationImpl(&googleMaps);

    // Request an Uber ride with Google Maps navigation
    uber.navigate("Central Park");

    // Switch to Apple Maps navigation for UberEats
    uberEats.setNavigationImpl(&appleMaps);

    // Request an Uber Eats delivery with Apple Maps navigation
    uberEats.navigate("123 HSR");

}