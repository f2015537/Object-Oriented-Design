#include<bits/stdc++.h>
using namespace std;

class PaymentGateway{
private:
	static PaymentGateway* instance;
	static mutex mtx;
	PaymentGateway(){
		cout<<"Payment PaymentGateway created by thread "<< this_thread::get_id() << "\n";;
	}

public:
	static PaymentGateway* getPaymentGateway(){
		if(instance == nullptr){ // double locking
			mtx.lock();
			if(instance == nullptr){
				instance = new PaymentGateway();
			}
			mtx.unlock();
		}
		return instance;
	}

	void processAmount(double amount){
		cout<<"Processing amount of $"<<amount<<" with Singleton PaymentGateway\n";
	}
};

void threadFunc(int id) {
    PaymentGateway* pg = PaymentGateway::getPaymentGateway();
    pg->processAmount(id * 10);
    // Optional: check all threads get the same instance
    assert(pg == PaymentGateway::getPaymentGateway());
}

PaymentGateway* PaymentGateway::instance = nullptr;
mutex PaymentGateway::mtx;

int main(){
	const int numThreads = 10;
	vector<thread> threads;

	for(int i = 0; i < numThreads; ++i){
		threads.emplace_back(threadFunc,i);
	}

	for(thread &t : threads){
		t.join();
	}
}