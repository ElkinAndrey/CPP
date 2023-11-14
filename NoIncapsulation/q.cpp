#include "q.h"

struct MyStruct {
	int myStructInformation;
};

MyStruct* CreateMyStruct(int myStructInformation) {
	MyStruct* myStruct = new MyStruct();
	myStruct->myStructInformation = myStructInformation;
	return myStruct;
}

int GetMyStruct(MyStruct* myStruct) {
	return myStruct->myStructInformation;
}