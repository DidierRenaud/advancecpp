#include "DemoReferences.h"
#include "DemoUtility.h"
using namespace std;



struct ClassA {
	ClassA(int i) : a{ i } {}
	int a;
};

void fun(const ClassA& lref) // l-value arguments will select this function
{
	std::cout << "l-value reference to const\n";
}

void fun(ClassA&& rref) // r-value arguments will select this function
{
	std::cout << "r-value reference\n";
}

void DemoReferences::runBasic() {

	ClassA w{ 5 };
	fun(w); // calls l-value version of function
	ClassA& x = w;
	fun(x); // calls l-value version of function
	fun(ClassA{ 5 }); //calls r-value version of function
	const ClassA& y = ClassA{ 5 };
	fun(y); // calls l-value version of function
	ClassA&& z = ClassA{ 5 };
	fun(z); // calls l-value version of function
	fun(std::forward<ClassA>(x)); // l-value argument calls r-value version of function
	fun(std::forward<ClassA>(z)); // r-value argument calls r-value version of function
}

void DemoReferences::runDemoMove(){
	std::vector<string> v1{1000000, std::string{ "blablabla" }};
	DemoStartBench("lvalue copy ");
	std::vector<string> v_copy_slow{ v1 }; 
	DemoEndBench();
	DemoStartBench("rvalue copy ");
	std::vector<string> v_copy_fast{ std::move(v1) };
	DemoEndBench();
};

void DemoReferences::runDemocontentAfterMove() {
	std::string s1{ "hello" };
	std::string s2{ "goodby" };
	s2 = move(s1); 
	//what happened to s1 ??? 
	cout << "String content after move " << s1 << endl;
};

//-------------- default 
//           s(std::move(o.s)),       // explicit move of a member of class type
//(std::exchange(o.k, 0))
namespace {
	class RValueTestClass{
	public:
		RValueTestClass(const std::string& s) :
			s_{ s }, 
			test_{ new char[s.size()+1] } {
			cout << "RValueTestClass(const std::string& ) called " << endl;
			strcpy_s(test_, s.size() + 1,s.c_str());
		}
		RValueTestClass() : RValueTestClass{""} {
			cout << "RValueTestClass() called " <<endl ; 
		}
		RValueTestClass(const RValueTestClass& c) : RValueTestClass{ c.s_ }
		{
			cout << "RValueTestClass(const RValueTestClass& c) called " << endl;
		}

		RValueTestClass(RValueTestClass&& c) :
			s_{ std::move(c.s_)}, 
			test_{ std::exchange(c.test_,nullptr) } //C++14
		{
			cout << "RValueTestClass(RValueTestClass&& c) called " << endl;
		}
		RValueTestClass& operator=(const RValueTestClass& t) {
			cout << "RValueTestClass& operator=(const RValueTestClass& t) called " << endl;
			s_ = t.s_;
			if (test_) delete[] test_;
			test_ = new char[s_.size() + 1]; 
			strcpy_s(test_, s_.size() + 1, s_.c_str());
			return *this;
		}
		RValueTestClass& operator=(RValueTestClass&& t) {
			cout << "RValueTestClass& operator=(RValueTestClass&& t) called " << endl;
			s_ = std::move(t.s_);
			test_ = std::exchange(t.test_, nullptr);
			return *this;
		}
		virtual ~RValueTestClass() {
			//cout << "~RValueTestClass() called " << endl;
			if (test_) delete[] test_; 
		}
	private:
		std::string  s_;
		char* test_; 
	};

	class TestDefault {
	public :
		TestDefault() :t{"Coucou"} {};
		//TestDefault(const TestDefault& d) :t{ d.t } {};
		//TestDefault(const TestDefault& d) = default;
		//TestDefault(const TestDefault & d) = delete;
		//TestDefault(TestDefault&& d) :t{ std::move(d.t) } {};
		//TestDefault(TestDefault&& d) = default;
		//TestDefault(TestDefault&& d) = delete;
		//TestDefault& operator=(const TestDefault& d) {t = d.t;return *this;}
		//TestDefault& operator=(const TestDefault& d) = default;
		//TestDefault& operator=(const TestDefault& d) = delete;
		//TestDefault& operator=(TestDefault&& d) {t = std::move(d.t);return *this;}
		//TestDefault& operator=(TestDefault&& d)= default;
		//TestDefault& operator=(TestDefault&& d) = delete;
	private:
		RValueTestClass t;
	};
}

void DemoReferences::runDemoConstructorTest() {
	{
		DemoStartBench("1--Test init by copy from local variable");
		TestDefault td1;
		TestDefault td2{ td1 };
		DemoEndBench();
	}
	{
		DemoStartBench("2--Test init by copy from temporary variable");
		TestDefault td2{ TestDefault{} };
		DemoEndBench();
	}
	{
		DemoStartBench("3--Test init by moving local variable");
		TestDefault td1;
		TestDefault td2{ std::move(td1) };
		DemoEndBench();
	}
	{
		DemoStartBench("4--Copy local variable");
		TestDefault td1;
		TestDefault td2;
		td1= td2;
		DemoEndBench();
	}
	{
		DemoStartBench("5--Copy temporary variable");
		TestDefault td1;
		td1 = TestDefault();
		DemoEndBench();
	}
};