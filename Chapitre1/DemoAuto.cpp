#include "DemoAuto.h"


#include "DemoUtility.h"


using namespace std; 
namespace {
    int testPointerFunction(int a, const int* b = nullptr, int* const* c = nullptr, const int** d = nullptr) {
        return a;
    }

    int max_value_fct(int a, int b) {
        return std::max(a, b);
    }

    auto returnValue(const std::map<string, string>& m) {
        return m.begin();
    }
}
void DemoAuto::runSamplesAuto() {
    int a = 1;
    const int const_a = 1;
    CH1_AUTO_TEST(auto x = 1 + 2);
    CH1_AUTO_TEST(auto const x = 1 + 2);
    CH1_AUTO_TEST(auto x = (const int)(1 + 2));
    CH1_AUTO_TEST(auto& x = a); 

    CH1_AUTO_TEST(const auto & x = const_a);

    CH1_AUTO_TEST(auto& x = testPointerFunction);

    CH1_AUTO_TEST(const auto & x =DemoUtility::StrangeEmptyMap.begin());

    auto fct = max_value_fct;
    cout << "call max_value_fct from pointer function " << fct(10, 20) << endl;
}

