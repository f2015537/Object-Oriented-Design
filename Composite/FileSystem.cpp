#include<bits/stdc++.h>
using namespace std;

class FileSystemComponent {
public:
	virtual void listContents() = 0;
	virtual int getSize() = 0;
	virtual ~FileSystemComponent() = default;
};

class File : public FileSystemComponent {
private:
	string name;
	string contents;
	int size;
public:
	File(string name, string contents): name(name), contents(contents), size(contents.size()) {}
	void listContents() override {
		cout<<"File "<<name<<" contains "<<contents<<endl;
	}
	int getSize() override {
		return size;
	} 
};

class Directory : public FileSystemComponent {
private:
	vector<FileSystemComponent*> components;
	string name;
public:
	Directory(string name): name(name) {}
	void addComponent(FileSystemComponent* component){
		components.push_back(component);
	}
	void listContents() override {
		cout<<"Directory "<<name<<" contains"<<endl;
		for(FileSystemComponent* component: components){
			component->listContents();
		}
	}
	int getSize() override {
		int totalSize = 0;
		for(FileSystemComponent* component: components){
			totalSize += component->getSize();
		}
		return totalSize;
	}
};

int main(){
    Directory* root = new Directory("Root");

    FileSystemComponent* file1 = new File("Document.txt", "Some random text in document");
    FileSystemComponent* file2 = new File("Image.jpg", "Image of a rainforest");

    Directory* subDir = new Directory("Subdirectory");
    FileSystemComponent* file3 = new File("Data.csv", "Some analytics data");

    subDir->addComponent(file3);

    root->addComponent(file1);
    root->addComponent(file2);
    root->addComponent(subDir);

    // List contents and calculate total size for the directory structure
    root->listContents();
    int totalSize = root->getSize();
    cout << "Total Size: " << totalSize << " KB" << endl;

    // Clean up memory (consider using smart pointers in a real application)
    delete root;
    delete file1;
    delete file2;
    delete file3;
    delete subDir;

    return 0;
}