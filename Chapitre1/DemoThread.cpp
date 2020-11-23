#include "DemoThread.h"

#include <iostream>
#include <utility>
#include <thread>
#include <shared_mutex>
#include <chrono>
#include <functional>
#include <atomic>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <chrono>
#include <future>
#include <numeric>
#include <atomic>
#include <execution>

void f1()
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 1 " << std::this_thread::get_id()<<" " << i << " executing\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void f2(int& n)
{
    for(int i=0; i<5; ++i) {
        std::cout << "Thread 2 " << std::this_thread::get_id() << " " << i << " executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void f3()
{
    for (int i = 0; i < 5; ++i) {
        std::cout << " Thread 3 " << std::this_thread::get_id() << " " << i << " executing\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}


struct Foo  {
    Foo() :t{ nullptr } {}
    ~Foo() {
        if (t) {
            t->join();
            delete t;
        }
    }
    void run(int n, int m)
    {
        std::cout << "Start Foo with param " << n << " " << m << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << " Method Foo executing " << std::this_thread::get_id() << " " << i << " executing\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
    void startThread() {
        auto f6 = std::bind(&Foo::run, this, 2, std::placeholders::_1);
        t =new std::thread(f6, 60);
    }
    std::thread *t;
};

void DemoThread::runThread() {
    int n = 0;
    int m = 0;
    std::thread t1; // t1 is not a thread
    std::thread t2(f1); // pass by value
    std::thread t3(f2, std::ref(n)); // pass by reference
    std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
    //call lambda
    std::thread t6([&m]() {
        std::cout << "Thread lambda executing\n";
        ++m;
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        }); 

    std::function<void()> f_display = f3;
    std::thread t5(f_display);
    //start a method as a thread 
    {
        Foo foo;
        auto f_bind = std::bind(&Foo::run, foo, 1, std::placeholders::_1);
        std::thread t7(f_bind, 50);
        t7.join();
        foo.startThread();
    }
    t2.join();
    t4.join();
    t5.join();
    t6.join();

    std::cout << "Final value of n is " << n << " m is "<< m<< '\n';
}

struct FooMutex {
    void sleep_inc()
    {
        std::lock_guard<std::recursive_mutex> lock(mutex_g);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        safe_increment();
    }
    
    void safe_increment()
    {
        std::lock_guard<std::recursive_mutex> lock(mutex_g);
        ++g_i;
        // mutex is automatically released when lock
        // goes out of scope
    }

    void both_increment()
    {
        // don't actually take the locks yet
        std::unique_lock<std::recursive_mutex> lock1(mutex_g, std::defer_lock);
        std::unique_lock<std::recursive_mutex> lock2(mutex_h, std::defer_lock);

        // lock both unique_locks without deadlock
        std::lock(lock1, lock2);
        //possible dead lock 
        //std::lock_guard<std::recursive_mutex> lock(mutex_g);
        //std::lock_guard<std::recursive_mutex> lock(mutex_h);
        ++g_i;
        ++h_i;
        // mutex is automatically released when lock
        // goes out of scope
    }

    void both_decrement()
    {    // don't actually take the locks yet
        std::unique_lock<std::recursive_mutex> lock1(mutex_h, std::defer_lock);
        std::unique_lock<std::recursive_mutex> lock2(mutex_g, std::defer_lock);

        // lock both unique_locks without deadlock
        std::lock(lock1, lock2);
        //possible dead lock 
        //std::lock_guard<std::recursive_mutex> lock(mutex_h);
        //std::lock_guard<std::recursive_mutex> lock(mutex_g);
        ++g_i;
        ++h_i;
        // mutex is automatically released when lock
        // goes out of scope
    }

    int h_i = 1000;
    std::recursive_mutex mutex_h;
    int g_i = 0;
    std::recursive_mutex mutex_g;  
};

void DemoThread::runMutex()
{
    FooMutex  f;
    std::thread t1([&] (){f.safe_increment(); });
    std::thread t2([&]() {f.sleep_inc(); });

    t1.join();
    t2.join();
}
class ThreadSafeCounter {
public:
    ThreadSafeCounter() = default;

    // Multiple threads/readers can read the counter's value at the same time.
    unsigned int get() const {
        std::shared_lock<std::shared_mutex>  lock(mutex_);
        return value_;
    }

    // Only one thread/writer can increment/write the counter's value.
    void increment() {
        std::unique_lock<std::shared_mutex>  lock(mutex_);
        value_++;
    }

    // Only one thread/writer can reset/write the counter's value.
    void reset() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        value_ = 0;
    }

private:
    mutable std::shared_mutex mutex_;
    unsigned int value_ = 0;
};

void DemoThread::sharedMutex(){
    ThreadSafeCounter counter;

    auto increment_and_print = [&counter]() {
        for (int i = 0; i < 3; i++) {
            counter.increment();
            std::cout << std::this_thread::get_id() << ' ' << counter.get() << '\n';

            // Note: Writing to std::cout actually needs to be synchronized as well
            // by another std::mutex. This has been omitted to keep the example small.
        }
    };

    std::thread thread1(increment_and_print);
    std::thread thread2(increment_and_print);

    thread1.join();
    thread2.join();
}


void DemoThread::runCondition()
{
    std::queue<int> produced_nums;
    std::mutex m;
    std::condition_variable cond_var;
    bool done = false;
    bool notified = false;

    std::thread producer([&]() {
        for (int i = 0; i < 5; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::unique_lock<std::mutex> lock(m);
            std::cout << "producing " << i << '\n';
            produced_nums.push(i);
            notified = true;
            cond_var.notify_one();
        }

        done = true;
        cond_var.notify_one();
        });

    std::thread consumer([&]() {
        std::unique_lock<std::mutex> lock(m);
        while (!done) {
            while (!notified) {  // loop to avoid spurious wakeups
                cond_var.wait(lock);
            }
            while (!produced_nums.empty()) {
                std::cout << "consuming " << produced_nums.front() << '\n';
                produced_nums.pop();
            }
            notified = false;
        }
        });

    producer.join();
    consumer.join();
}


void getInput(
    std::promise<std::string>& accumulate_promise)
{
    std::string n;
    std::cout << "Enter n: "; // no flush needed
    std::cin >> n;
    accumulate_promise.set_value(n);  // Notify future
}

void waitpromise(std::promise<void>& barrier)
{
    std::string s;
    std::cout << "Enter anything: "; // no flush needed
    std::cin >> s;
    //unlock waits
    barrier.set_value();
}



void DemoThread::runFuture()
{
    std::promise<std::string> input_promise;
    std::future<std::string> input_future = input_promise.get_future();
    std::thread input_thread([&]() { getInput(input_promise);  });
    // future::get() will wait until the future has a valid result and retrieves it.
    // Calling wait() before get() is not needed
    //accumulate_future.wait();  // wait for result
    std::cout << "result= " << input_future.get() << '\n';
    input_thread.join();  // wait for thread completion
    // Demonstrate using promise<void> to signal state between threads.
    std::promise<void> barrier;
    std::future<void> barrier_future = barrier.get_future();
    std::thread new_work_thread([&]() { waitpromise(barrier);  });
    barrier_future.wait();
    new_work_thread.join();
} 

std::mutex m_cout;
struct AsyncSample {
    void print( const std::string& str) const{
        std::lock_guard<std::mutex> lk(m_cout);
        std::cout << str << ' ' << '\n';
        std::cout.flush();
    }
    std::string getInput() const {
        std::string str; 
        std::cin >> str;
        return std::move(str); 
    }
};
void DemoThread::runAsync()
{
    AsyncSample x;
    auto a1 = std::async(&AsyncSample::print, &x, "Hello ? ");
    auto a2 = std::async(std::launch::deferred, &AsyncSample::print, x, "Goodby ");
    std::string me = x.getInput(); 
    a2.wait();                     
    std::cout << me << std::endl; 
} 




struct AtomicTest {
    void setFlag(bool flg) { flag = flg; }
    void wait()const {
        while (flag) {
//hidden barrier that mask the bug
//bug may be masked by debug compilation too => because no optimization 
//           std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    //std::atomic_bool flag=true;
    bool flag=true;
};


void DemoThread::runAtomic() {
    AtomicTest t; 
    auto a1 = std::async([&]() {t.setFlag(false); });
    t.wait(); 
    std::cout << "End reached" << std::endl;
}