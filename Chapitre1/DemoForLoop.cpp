#include "DemoForLoop.h"
#include "DemoUtility.h"

using namespace std; 

namespace {
	class CustomForCompatible {
	public:
		CustomForCompatible() {
			int j{ 20 };
			for (auto& i : tab_) {
				i = ++j;
			}
		}
		long* begin() {
			return tab_; 
		}
		long* end() {
			return tab_ + 10;
		}

		const long* begin()const {
			return tab_;
		}
		const long* end() const {
			return tab_ + 10;
		}
	private:
		long tab_[10];
	};
}

void DemoForLoop::runCustomClass() {
	CustomForCompatible sample; 
	for (auto& item : sample) {
		//item = ++i; // error item is a const ref 
		cout << item << ' ';
	}
	cout << endl;
}



void DemoForLoop::runSample() {
	std::array<int, 10> myArray;
	//fill the array
	int i{ 0 };
	for (auto& item : myArray) {
		item = ++i; 
	}
	// read const array
	const std::array<int, 10> myConstArray{ myArray };
	for (auto& item : myConstArray) {
		//item = ++i; // error item is a const ref 
		cout << item << ' ';
	}
	cout << endl;

	// the same with C style array
	int myCArray[10];
	int j{ 10 };
	for (auto& item : myCArray) {
		item = --j;
	}
	// read 
	for (auto& item : myCArray) {
		cout << item << ' ';
	}

	cout << endl;
}