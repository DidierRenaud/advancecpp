#include "DemoRTTI.h"
#include "DemoUtility.h"
#include <typeinfo>

using namespace std;

namespace {
	// helper class for runtime polymorphism demo below
	struct Abstract_A {
		virtual void func(const std::string&) {}
		virtual ~Abstract_A() = default;
	};
	struct Abstract_B : Abstract_A
	{
		virtual void func(const std::string&) override {}
		virtual ~Abstract_B() = default;
	};

	// helper class for runtime polymorphism demo below
	struct Static_A {
		void func(const std::string&) {}
		~Static_A() = default;
	};
	struct Static_B : Static_A
	{
		void func(const std::string&)  {}
		~Static_B() = default;
	};
}

void DemoRTTI::runTypeInfo() {
	int i{ 0 };
	cout << typeid(i).name() << endl;
	const double& f={ 0.0 };
	cout << typeid(f).name() << endl;
	cout << typeid(&f).name() << endl;
	cout << typeid(const double).name() << endl;
	cout << typeid(Abstract_A).name() << endl;
	{
		Abstract_A* b = new Abstract_B{};
		cout << typeid(b).name() << endl;
		cout << typeid(*b).name() << endl;
		delete b;
	}
	{
		Static_A* b = new Static_B{};
		cout << typeid(b).name() << endl;
		cout << typeid(*b).name() << endl;
		delete b;
	}
	cout << typeid(&Abstract_B::func).name() << endl;
	cout << typeid(std::vector<std::string>).name() << endl;
}


namespace {
	// helper class for runtime polymorphism demo below
	struct StaticCast_A {
		StaticCast_A(int a) :i{ a } {}
		int i;
	};
	struct StaticCast_B {
		StaticCast_B(double b) :i{ b } {}
		StaticCast_B(const StaticCast_A& b) :i{
			static_cast<double>(b.i)
		} {
			cout << "Call StaticCast_B::StaticCast_B(const StaticCast_A& b) " << endl;
		}
		double i;
	};
	struct StaticCast_C {
		StaticCast_C(double b) :i{ b } {}
		operator StaticCast_A () const {
			cout << "operator StaticCast_C::StaticCast_A () const " << endl;
			return StaticCast_A{static_cast<int>(i)};
		}
		double i;
	};

}


void DemoRTTI::runStaticCast() {
	double i = 1.5; 
	int j = static_cast<int>(i); 
	StaticCast_A a{ 1 };
	StaticCast_B b = static_cast<StaticCast_B>(a);
	StaticCast_C c{ 1.1 };
	StaticCast_A a2 = static_cast<StaticCast_A>(c);
}


namespace StaticCast {
	struct B {};
	struct D : B {};

	enum class E { ONE, TWO, THREE };
	enum EU { ONE, TWO, THREE };
}

void DemoRTTI::runStaticCast2() {
	using namespace StaticCast;
	// 1: initializing conversion
	int n = static_cast<int>(3.14);
	std::cout << "n = " << n << '\n';
	std::vector<int> v = static_cast<std::vector<int>>(10);
	std::cout << "v.size() = " << v.size() << '\n';

	// 2: static downcast
	D d;
	B& br = d; // upcast via implicit conversion
	D& another_d = static_cast<D&>(br); // downcast

	// 3: lvalue to xvalue
	std::vector<int> v2 = static_cast<std::vector<int>&&>(v);
	std::cout << "after move, v.size() = " << v.size() << '\n';

	// 4: discarded-value expression
	static_cast<void>(v2.size());

	// 5. inverse of implicit conversion
	// todo

	// 6. array-to-pointer followed by upcast
	D a[10];
	B* dp = static_cast<B*>(a);

	// 7. scoped enum to int or float
	E e = E::ONE;
	int one = static_cast<int>(e);

	// 8. int to enum, enum to another enum
	E e2 = static_cast<E>(one);
	EU eu = static_cast<EU>(e2);

	// 9. pointer to member upcast
	// todo

	// 10. void* to any type
	void* voidp = &e;
	std::vector<int>* p = static_cast<std::vector<int>*>(voidp);
}


namespace DynamicCast {
struct V {
	virtual void f() {};  // must be polymorphic to use runtime-checked dynamic_cast
};
struct A : virtual V {};
struct B : virtual V {
	B(V* v, A* a) {
		// casts during construction
		dynamic_cast<B*>(v); // well-defined: v of type V*, V base of B, results in B*
		dynamic_cast<B*>(a); // undefined behavior: a has type A*, A not a base of B
	}
};
struct D : A, B {
	D() : B((A*)this, this) { }
};

struct Base {
	virtual ~Base() {}
};

struct Derived : Base {
	virtual void name() {}
};
}

void DemoRTTI::runDynamicCast()
{
	using namespace DynamicCast;
	D d; // the most derived object
	A& a = d; // upcast, dynamic_cast may be used, but unnecessary
	D& new_d = dynamic_cast<D&>(a); // downcast
	B& new_b = dynamic_cast<B&>(a); // sidecast


	Base* b1 = new Base;
	if (Derived* d = dynamic_cast<Derived*>(b1))
	{
		std::cout << "downcast from b1 to d successful\n";
		d->name(); // safe to call
	}

	Base* b2 = new Derived;
	if (Derived* d = dynamic_cast<Derived*>(b2))
	{
		std::cout << "downcast from b2 to d successful\n";
		d->name(); // safe to call
	}

	delete b1;
	delete b2;
	

	Derived dref;
	Base bref;
	Base& bout = dynamic_cast<Base&>(dref);
	//Derived& dout = dynamic_cast<Derived&>(bref);
}

namespace ReinterpretCast {
	struct A {
		A(int i = 5) : j{ i }, k{ i* 2} {}
		int j;
		int k;
	};
}

void DemoRTTI::runReinterpretCast() {
	using namespace ReinterpretCast; 
	A a; 
	int* ptr = reinterpret_cast<int*> (&a);
	cout << " reinterpret_cast<int*>  result " << *ptr << "  "<< * (ptr + 1) << endl;
	double zero{ 0.0 }; 
	double bignumber{ 1e+5 };
	uint64_t * zptr  = reinterpret_cast<uint64_t*> (&zero);
	cout << " double in bytes " << zero <<" " << std::hex << *zptr << endl;
	uint64_t* bptr = reinterpret_cast<uint64_t*> (&bignumber);
	cout << " double in bytes " << bignumber << " " << std::hex << *bptr << endl;

}