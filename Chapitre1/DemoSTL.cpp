#include "DemoSTL.h"
#include "DemoUtility.h"
#include <vector>
#include <functional>
#include <functional>
#include <tuple>
#include <algorithm>
#include <numeric>
using namespace std; 

void DemoSTL::capacity() {
    std::vector<int> array;
    array.reserve(5); // set capacity to 5
    array = { 0, 1, 2 };
    std::cout << "The length is: " << array.size() << '\n';
    for (int i : array)
        std::cout << i << ' ';
    std::cout << endl;
}

void DemoSTL::size() {
    std::vector<int> array{ 0, 1, 2 };
    array.resize(5); // set size to 5
    std::cout << "The length is: " << array.size() << '\n';
    for (int i : array)
        std::cout << i << ' ';
    std::cout << endl;
}
void DemoSTL::operations() {
    std::vector<int> suite{ 1,2,3 };

    std::vector<int> revert;

    cout << "revert is empty? " << revert.empty() << " capacity ? " << revert.capacity() << endl;

    revert.assign(suite.rbegin(), suite.rend());

    for (auto c : revert) {
        std::cout << c << ' ';
    }
    std::cout << endl;
    revert.insert(revert.begin(), suite.begin(), suite.end());
    for (auto c : revert) {
        std::cout << c << ' ';
    }
    std::cout << endl;
    revert.erase(revert.begin() + 2, revert.begin() + 4);
    for (auto c : revert) {
        std::cout << c << ' ';
    }
    std::cout << endl;
    revert.pop_back(); //no pop front for vector
    revert.push_back(3);//move
  //  revert.emplace_back(3); // arguments for item coonstructor

    for (auto c : revert) {
        std::cout << c << ' ';
    }
    std::cout << endl;
    revert.clear(); 
    cout << "revert is empty? " << revert.empty() << " capacity ? " << revert.capacity()<<endl;
}


//bad lambda wrapper 
//std::function<void(void)> closureWrapper2()
//{
//    int x = 10;
//    return [&x]() {x += 1; std::cout << "Value in the closure: " << x << std::endl; };
//}

//correct  lambda wrapper 
//std::function<void(void)> closureWrapper2(int& x)
//{
//    return [&x]() {x += 1; std::cout << "Value in the closure: " << x << std::endl; };
//}

void DemoSTL::lambda() {
    int x{ 0 };
    double y{ 10 };
    cout << "x value : "<< x  << " y value : "<< y << endl;
    auto f1 = [x](int a, int b) { return a * x + b; };
    cout << "[x](int a, int b) { return a * x + b; }";
    cout << " return value " << f1( 2, 3 ) << std::endl; 
    cout << "x value : " << x << " y value : " << y << endl;
    auto f2 = [&x]() {  ++x; };
    cout << "[&x]() {  ++x; }" << std::endl;
    f2();
    cout << "x value : " << x << " y value : " << y << endl;
    auto f3 = [](auto a, auto b) { return a * b; };
    cout << "[](auto a, auto b) { return a * b; }";
    cout << " return value " << f3(2, 3) << std::endl;
    cout << "x value : " << x << " y value : " << y << endl;
    auto f4 = [=]() { return x * y; };
    cout << "[=]() { return x * y; }";
    cout << " return value " << f4() << std::endl;
    cout << "x value : " << x << " y value : " << y << endl;
    auto f5 = [&x, y]() mutable {++x; ++y; };
    cout << "[&x, y]() mutable {++x; ++y; }"  << std::endl;
    f5();
    cout << "x value : " << x << " y value : " << y << endl;
    auto f6 = [=](bool param) -> double {if (param) return x; else return y;  };
    cout << "[=](bool param) -> double {if (param) return x; else return y;  }";
    cout << " return value " << f6(true) << std::endl;
    cout << "x value : " << x << " y value : " << y << endl;
    auto f7 = [&]() {++x; ++y; };
    cout << "[&]() {++x; ++y; }" << std::endl;
    f7();
    cout << "x value : " << x << " y value : " << y << endl;
    auto f8 = [=]()mutable {++x; ++y; };
    cout << "[=]()mutable {++x; ++y; }"   << std::endl;
    f8();
    cout << "x value : " << x << " y value : " << y << endl;
    auto as_tuple = [](auto... args) { return std::make_tuple(args...); };
    cout << "[](auto... args) { return std::make_tuple(args...); }";
    auto tupl = as_tuple(2, 3.3, std::string("coucou"));
    cout << " return value " << std::get<int>(tupl) << " : "<< std::get<double>(tupl)<<" : " << std::get<std::string>(tupl) <<  std::endl;
    cout << "x value : " << x << " y value : " << y << endl;
}


void DemoSTL::algoInAction() {
    std::vector<int> v{  1, 5, 3, 2, 7, 9, 10,29,29,26  };

    auto result1 = std::find(std::begin(v), std::end(v), 3);
    auto result2 = std::find_if(std::begin(v), std::end(v), [](auto a) {return !(a % 2); });

    if (result1 != std::end(v)) {
        std::cout << "v contains: " << *result1 << '\n';
    }
    if (result2 != std::end(v)) {
        std::cout << "Pair item found : " << *result2 << '\n';
    }

    auto  displayVector= [](auto v) { 
        std::for_each(v.begin(), v.end(), [](auto& n) { cout<< n<< ' '; });
        cout << endl;
    };

    // reverse sorting 
    std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) {return a>b ;});
    //reverse sorting with std utility
    //std::sort(s.begin(), s.end(), std::greater<int>());
    displayVector(v);
    // sort using the default operator<

   // sort using a custom  "old school" function object to be declared outside function
   // struct {
   //     bool operator()(int a, int b) const
   //     {
   //         return a < b;
   //     }
   // } customLess;

    std::sort(v.begin(), v.end());
    displayVector(v);
    std::vector<int> pairValues; 

    std::copy_if(v.begin(), v.end()
        , std::back_inserter(pairValues), [](const auto& a) {return !(a % 2); });
    displayVector(pairValues);
    //looking for all elemsfrom 7>= to <29
    auto lower = std::lower_bound(v.begin(), v.end(), 7);
    auto upper = std::upper_bound(v.begin(), v.end(), 29);
    std::vector<int> range(lower, upper);
    displayVector(range);

    std::cout << "range is included : " << std::includes(v.begin(), v.end(), range.begin(), range.end()) << '\n';
    range.push_back(500); 
    std::cout << "range,500 is included : " << std::includes(v.begin(), v.end(), range.begin(), range.end()) << '\n';
    //multiply all vector
    int product = std::accumulate(v.begin(), v.end(), 1, [](auto a, auto b) {return a * b; });
    cout << "multiplication of all vector v : " << product << endl;
}