#include<bits/stdc++.h>
using namespace std;

class Image {
public:
	virtual void display() = 0;
	virtual ~Image() = default;
};

class RealImage : public Image {
private:
	string filename;
public:
	RealImage(string filename): filename(filename) {
		loadImage();
	}

	void display(){
		cout<<"Displaying image "<<filename<<endl;
	}

	void loadImage(){
		cout<<"Loading image "<<filename<<" from disk"<<endl;
	}
};

class ProxyImage: public Image {
private:
	string filename;
	RealImage* realImage;
public:
	ProxyImage(string filename): filename(filename), realImage(nullptr) {}
	void display(){
		if(realImage == nullptr){
			realImage = new RealImage(filename);
		}
		realImage->display();
	}
	~ProxyImage(){
		if(realImage){
			cout<<"Deleting image "<<filename<<endl;
			delete realImage;
		}
	}
};


int main(){
	Image* image = new ProxyImage("abc.jpg");
	image->display();
	delete(image);
	return 0;
}