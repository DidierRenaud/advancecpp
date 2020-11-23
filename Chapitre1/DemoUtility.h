#pragma once
#include <map>
#include <string>
#include <array>
#include <map>
#include <vector>
#include <type_traits>
#include <iostream>
#include <typeinfo>
#include <chrono>
#include <tuple>
#include <functional>

typedef decltype(std::make_tuple(std::string(), std::chrono::steady_clock::now())) DemoStartTime;

class DemoUtility
{
public:
    static const std::vector< int  > SampleIntegerVector;
    static const std::map< std::pair< int, std::string>, std::vector< std::pair< double, long long > > > StrangeEmptyMap;
    static thread_local DemoStartTime BenchInfo;
};

template < typename X>
void printResult(const std::string& s, X& x, bool isref) {
    std::cout << s << "   =>   " << typeid(x).name() << " , is const ? " << std::is_const<X>::value << ", is a ref ?  " << isref << std::endl;
    std::cout << "-----------------------"<< std::endl;
}


#define CH1_AUTO_TEST( CH1_TEST_AUTO ){ \
    CH1_TEST_AUTO  ; \
    printResult(#CH1_TEST_AUTO, x, std::is_reference<decltype(x)>::value);  \
};

 inline void DemoStartBench(const std::string& str) {
    std::cout << std::endl 
        << str 
        << "---------------------------" 
        << std::endl << std::endl;
    DemoUtility::BenchInfo = std::make_tuple (str,std::chrono::steady_clock::now());
}



inline void DemoEndBench() {
    std::cout << std::endl 
        << std::get<0>(DemoUtility::BenchInfo) 
        << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()
            - std::get<1>(DemoUtility::BenchInfo)).count() 
        << " ms " 
        <<std::endl;
}






