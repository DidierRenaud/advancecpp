#include "DemoRAI.h"
#include "DemoUtility.h"

#include <memory> // for std::shared_ptr

class Resource
{
public:
	Resource(int i = 0)  { std::cout << "Resource acquired param :" << i <<"\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

void DemoRAI::runSharedPointer() 
{
	DemoStartBench("1--Test init by copy from local variable");
	// allocate a Resource object and have it owned by std::shared_ptr
	auto ptr1 = std::make_shared<Resource>(); //
	{
		auto ptr2 = ptr1; // create ptr2 using copy initialization of ptr1

		std::cout << "Killing one shared pointer\n";
	} // ptr2 goes out of scope here, but nothing happens
	std::cout << "Killing another shared pointer\n";
	DemoEndBench();
}


class Buddy
{
public:
	Buddy(const std::string& s ) : name_{ s  } {
		std::cout << "You are my friend"<< name_ << " \n ";
	}
	void youAreMyPal(const std::shared_ptr<Buddy>& myFriend) { myFriend_ = myFriend; }
	~Buddy() {
		std::cout << name_ <<" is dead \n"; 
	}
	void anyFriend()const {
		auto f = myFriend_.lock(); //weak_ptr
		//auto f = myFriend_; //shared ptr
		if (f) {
			std::cout << name_ << " have " << f->getName() << " as friend :) " << std::endl;
		}
		else {
			std::cout << name_ << " got no friend  :( " << std::endl;
		}
	}
	const std::string getName()const {
		return name_;
	}
private:
	std::string name_; 
	//std::shared_ptr<Buddy> myFriend_;
	std::weak_ptr<Buddy> myFriend_;
};

void DemoRAI::runWeakPointer() {
	DemoStartBench("Cyclic reference and weak ptr");
	std::shared_ptr<Buddy> john = std::make_shared<Buddy>("john");
	{
		std::shared_ptr<Buddy> jack = std::make_shared<Buddy>("jack");
		john->youAreMyPal(jack);
		jack->youAreMyPal(john);
		john->anyFriend(); 
	}
	john->anyFriend();
	DemoEndBench();
}


void DemoRAI::DemoUniquePtrMove() {
	std::unique_ptr<Resource> res1{ new Resource{} }; // Resource created here
	std::unique_ptr<Resource> res2{}; // Start as nullptr
	std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n");
	std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n");
	// res2 = res1; // Won't compile: copy assignment is disabled
	res2 = std::move(res1); // res2 assumes ownership, res1 is set to null
	std::cout << "Ownership transferred\n";
	std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n");
	std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n");
}

void DemoRAI::DemoUniquePtrLeakageAndArray() {
	auto* ptr{ new Resource() };
	//std::unique_ptr<Resource> ptr{ new Resource() };
	//new ressource with param 1
	//auto ptr{ std::make_unique<Resource>(1) };
	// Create a dynamically allocated array of length 4 with param 0
	//auto ptr{ std::make_unique<Resource[]>(4) };

	int x{};
	std::cout << "Enter an integer: ";
	std::cin >> x;

	if (x == 0)
		throw 0; // the function returns early, and ptr won’t be deleted!

	// do stuff with ptr here

	delete ptr;
}
namespace {
	// helper class for runtime polymorphism demo below
	struct B {
		virtual void bar() { std::cout << "B::bar\n"; }
		virtual ~B() = default;
	};
	struct D : B
	{
		D() { std::cout << "D::D\n"; }
		~D() { std::cout << "D::~D\n"; }
		void bar() override { std::cout << "D::bar\n"; }
	};
}


void DemoRAI::DemoUniquePtrPolymorphisme()
{
	std::unique_ptr<B> p = std::make_unique<D>(); // p is a unique_ptr that owns a D
												  // as a pointer to base
	p->bar(); // virtual dispatch

	std::vector<std::unique_ptr<B>> v;  // unique_ptr can be stored in a container
	v.push_back(std::make_unique<D>());
	v.push_back(std::move(p));
	v.emplace_back(new D);
	for (auto& p : v) p->bar(); // virtual dispatch
} // ~D called 3 times
