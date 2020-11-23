#include "DemoArray.h"
#include <array>
#include <vector>
#include <algorithm> // for std::sort
#include <iostream>
#include "DemoUtility.h"

namespace {
    void createArray() {
        //allocated in stack no init for the 100 elements
        std::array<int, 100> array;
    }

    void createVector() {
        //allocated in stack init for 100 elements
        std::vector<int> vector(100) ;
    }
}

void DemoArray::runDemoCreationDuration() {
    //std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    DemoStartBench("Array Creation ");
    for (int i = 0; i < 10000000; ++i) {
        createArray();
        //createVector();
    }
    //std::cout << "Creation Duration " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << std::endl;
    DemoEndBench();

    DemoStartBench("Vector Creation ");
    for (int i = 0; i < 10000000; ++i) {
        //createArray();
        createVector();
    }
    //std::cout << "Creation Duration " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << std::endl;
    DemoEndBench();


}
void DemoArray::runDemo() {
    std::array<int, 5> myArray{ 1, 2, 3, 4, 5 };
    try {
        // Iterate through the array and print the value of the elements
        for (int i{ 0 }; i < myArray.size(); ++i) {
            //for (int i{ 0 }; i < myArray.size()+1; ++i) { /* bound error*/
            std::cout << myArray[i] << ' ';
            //boud checking
            //std::cout << myArray.at(i) << ' ';
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << '\n';

    // Iterate through the array with iterator
    for (std::array<int, 5>::const_iterator it = myArray.begin(); it != myArray.end(); ++it) {
    //reverse iterator
     //for (std::array<int, 5>::const_iterator it = myArray.rbegin(); it != myArray.rend(); ++it){
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}