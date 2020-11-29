#include "TestThread.h"
#include "DemoUtility.h"


#include <thread>
#include <functional>
#include <chrono>
#include <shared_mutex>
#include <mutex>
#include <future>

using namespace std;

std::mutex g_num_mutex;


struct MyGuard {
	MyGuard(std::mutex& d) : md { d } {
		cout << " lock  " << endl;
		md.lock();
	}
	~MyGuard() {
		cout << " unlock  " << endl;
		md.unlock();
	}
	std::mutex& md;
};
//reentrant 
void testException(int i, bool testdeadlock) {
	if ((testdeadlock) && (i > 0)) {
		throw std::exception(" exception");
	}
}
//reentrant 
void longComputation() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void testThread1(bool testdeadlock=false)
{
	try {

		for (int i = 0; i < 10; ++i) {
			//g_num_mutex.lock();
			{
				std::lock_guard<std::mutex> guard(g_num_mutex);
				//----
				std::cout << "Mon thread est vivant " << std::this_thread::get_id() << " " << i << " executing\n";
			}//destruction du lock guard <<<-----
			//testException(i, testdeadlock);
			longComputation();
			//	
			//g_num_mutex.unlock();
		}
	}
	catch (const std::exception& e) {
		cout << " exception " << e.what() << endl;
	}
}

int f2(int a) {

	std::lock_guard<std::mutex> guard(g_num_mutex);
	std::cout << "f2 : " << a + 1 << endl;

}

void f1(int a) {
	++a; 
	std::lock_guard<std::mutex> guard(g_num_mutex); 
	std::cout << "f1 : " << f2(2) << endl;
}


struct Test {
	Test() :a{ 0 }, b{ 0 }{}
	Test(const Test& c) :a{ c.a }, b{ c.b }{}
    Test& operator=(const Test& c){
		a = c.a;
		b = c.b;
		return *this;
	}
	int getA()const {
		//protect a 
		std::lock_guard<std::recursive_mutex> guard(mtx_a);
		return a; //( return copy a to a temporary var so that ok )

	}
	int getB()const {
		//protect b 
		std::lock_guard<std::recursive_mutex> guard(mtx_b);
		return b; //( return copy a to a temporary var so that ok )
	}

	void setA( int i) {
		//protect a 
		std::lock_guard<std::recursive_mutex> guard(mtx_a);
		 a=i; //( return copy a to a temporary var so that ok )

	}
	void setB(int i) {
		//protect b 
		std::lock_guard<std::recursive_mutex> guard(mtx_b);
		b = i; //( return copy a to a temporary var so that ok )
	}
	int add() {
		//std::scoped_lock lock(e1.m, e2.m);
		cout << "enter add" << endl;
		//std::lock_guard<std::recursive_mutex> guard(mtx_a);
		cout << "Add take mtx_a " << endl;
		//std::lock_guard<std::recursive_mutex> guard2(mtx_b);
		cout << "Add take mtx_b " << endl;
		return  getA() +  getB();
	}

	int sub() {
		//std::scoped_lock lock(e1.m, e2.m);
		cout << "enter Sub" << endl;
		//std::lock_guard<std::recursive_mutex> guard2(mtx_a);
		cout << "Sub take mtx_a " << endl;
		//std::lock_guard<std::recursive_mutex> guard(mtx_b);
		cout << "Sub take mtx_b " << endl;

		return getA() - getB();
	}

private:
	mutable recursive_mutex mtx_a; 
	int a=0; 
	mutable recursive_mutex mtx_b;
	int b=0;
};




void getInputForProm(
	std::promise<std::string>& accumulate_promise)
{
	std::string n;
	std::cout << "Enter n: "; // no flush needed
	std::cin >> n;
	if (n.size() > 4) {
		try {
			// code that may throw
			throw std::runtime_error("Example");
		}
		catch (...) {
			accumulate_promise.set_exception(std::current_exception());
		}
	}
	else {
		accumulate_promise.set_value(n);  // Notify future
	}
}
/*
void waitpromise(std::promise<void>& barrier)
{
	std::string s;
	std::cout << "Enter anything: "; // no flush needed
	std::cin >> s;
	//unlock waits
	barrier.set_value();
}*/



void runFutureSample()
{
	std::promise<std::string> input_promise;
	std::future<std::string> input_future = input_promise.get_future();
	std::thread input_thread([&]() { getInputForProm(input_promise);  });
	std::cout << "wait for input" << endl;
	try {
		std::cout << "result= " << input_future.get() << '\n';
	}
	catch (...) {
		std::cout << "exception" << endl;
	}
	input_thread.join();  // wait for thread completion
}
/*
{		  
    // Demonstrate using promise<void> to signal state between threads.
	//std::promise<void> barrier;
	//std::future<void> barrier_future = barrier.get_future();
	//std::thread new_work_thread([&]() { waitpromise(barrier);  });
	//barrier_future.wait();
	//new_work_thread.join();
}*/


std::string getValeur(const string& toprint) {
	std::string s;
	std::cout << toprint << " type something :" << std::endl;
	std::cin >> s;
	return s;
}

void runAsync()
{
	auto a1 = std::async([]() {return getValeur("a1"); });
	
	auto a2 = std::async(std::launch::deferred, []() { return getValeur("a2"); });
	// auto a2 = std::async(std::launch::deferred, &AsyncSample::print, x, "Goodby ");
	std::cout << " wait " << std::endl;

	if (a1.get() == "compute") {
		std::cout << " valeur " << a2.get() << std::endl;
	}
}
#include <numeric>
void tpSumVector() {
	vector<double> v(10000000, 2.0);
	//v.begin(), v.end()
	auto a1 = std::async( [&v]() { return std::accumulate(v.begin() + (v.size() / 2), v.end(), 0.0); });
	auto a2 = std::async([&v]() { return std::accumulate(v.begin(), v.begin() + (v.size() / 2), 0.0); });
	double sum = a1.get() + a2.get(); 
	cout << "Somme vecteur" << sum << endl;
}


void TestThread::runDemo() {
	DemoStartBench(" Test thread");
	//runFutureSample();
	tpSumVector();
	cout << "Debut demo thread" << endl;

	//appeller un thread appelle testThread1 


	//std::thread t1(testThread1, false);//T1
	//testThread1();

	//std::thread t1(f1, 10); //T1
	//f2(1);//T2

	/*Test t1; 
	t1.setA(1);
	t1.setB(2);
	std::thread th1([&t1]() { for (int i = 0; i < 50; ++i) { t1.add(); } });
	std::thread th2([&t1]() { for (int i = 0; i < 50; ++i) { t1.sub(); } });*/

	//cout << "Wait thread " << endl;
	//th1.join();
	//th2.join();
	//cout << "Resultat " << t1.getA() << " " << t1.getB() << endl;/// 1 2 
	//cout << "thread joined " << endl;
	//faire le join ici
	DemoEndBench();
} 