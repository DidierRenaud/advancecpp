#include "DemoUtility.h"
const std::vector< int  > DemoUtility::SampleIntegerVector = std::vector< int  >({ 10,11,12,13,20,21,22,23,30,31,32,33 });
const std::map< std::pair< int, std::string>, std::vector< std::pair< double, long long > > > DemoUtility::StrangeEmptyMap;
thread_local DemoStartTime DemoUtility::BenchInfo;


