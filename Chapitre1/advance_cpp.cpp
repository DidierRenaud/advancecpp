// Chapitre1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "DemoAuto.h"
#include "DemoArray.h"
#include "DemoForLoop.h"
#include "DemoEnum.h"
#include "DemoReferences.h"
#include "DemoRAI.h"
#include "DemoRTTI.h"
#include "DemoSTL.h"
#include "DemoThread.h"
#include "Magasin.h"
#include "ExempleTemplate.h"
#include <vector>
#include < algorithm >
#include < set >
#include <map>
#include "TestThread.h"


void funcTestLambda(double a, double b) {
	double x = a / b;
	std::string str = "Coucou ";
	//MyMultiply<double> mult{ x };
	MyTestTemplate<double> testTemplate(5.5, 6.5);
	std::cout << "Result "
		<< testTemplate.anycomputation([x](double p1, double p2) {return x + p1 + p2; }) << std::endl;
	MyTestTemplate<std::string> testTemplateString(" tout ", " le monde ");
	// str1=str2+str3; 
	std::cout << "Result 2 " << testTemplateString.anycomputation([str](const std::string& p1, const std::string& p2) {return str + p1 + p2; }) << std::endl;
}




template<typename T>
void funcTestLambda(const T& a, const T& b, const T& c ) {
	MyTestTemplate<T> testTemplate(b, c);
	T x{};
	T y{}; //= 0.0 pour double
	//auto f = [&a](const auto& b1, const auto& c1) {return a + b1 + c1; };
	//capture toute les variables locales enreference
	//auto f = [&](const auto& b1, const auto& c1) {return a+x + b1 + c1; };

	//capture toute les variables locales copie 
	auto f = [=](const auto& b1, const auto& c1) {return a + b1 + c1+y; };

    //capture toute les variables locales copie 
	//auto f = [x,&a](const auto& b1, const auto& c1) {return a + b1 + c1; };

	std::cout << "Result "
		<< testTemplate.anycomputation(f) << std::endl;
}

void testMap() {
	std::map<std::string, int> letter_counts{ {"b", 3},{"a", 27},  {"c", 1} };
	

	letter_counts["d"] = 50;

	std::cout << "map  " << letter_counts["d"] << std::endl;


	auto it = letter_counts.find("b"); 
	if (it != letter_counts.end()) {
		std::cout << it->first << ": " << it->second << '\n';
	}
	else {
		std::cout << " not found" << std::endl;
	}
}


void testVector(size_t loop) {
	std::vector<int> v{ 0, 1, 2 };
	v.reserve(loop + 5);
	v.resize(5, 10); // set size to 5
	///-----------
	for (int i{ 0 }; i != v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << "---------" << std::endl;
	//--------------------------
	for (auto it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "---------" << std::endl;
	//--------------------------
	for (auto& item:v ) {
		std::cout << item << " " ;
	}
	std::for_each(v.begin(), v.end(), [](auto& item ) {  std::cout << item << " ";  } );
	v.pop_back(); 

	for (int j = 0; j < loop; ++j) {
		v.push_back(j);
	}

	v.clear(); 
	v.push_back(10);
	v.shrink_to_fit();
	//
	//iterator insert( const_iterator pos, std::initializer_list<T> ilist );
	v.insert(v.begin(), 10);
	v.insert(v.begin(), { 10,11,12 });
	std::cout << "size vs capacité " << v.size() << " " << v.capacity() << std::endl;
	for (auto& item : v) {
		std::cout << item << " ";
	}
	std::cout << "---------" << std::endl;
	v.insert(v.begin() + 3, 13); 
	for (auto& item : v) {
		std::cout << item << " ";
	}
	std::cout << "---------" << std::endl;

	std::vector<int> v2{ 20, 21, 22,23 };
	std::set<double> v3{ 30, 31, 32,33 };
	v.insert(v.end(), v2.begin(), v2.end());
	for (auto& item : v) {
		std::cout << item << " ";
	}
	std::cout << "---------" << std::endl;
	v.insert(v.end(), v2.end() -2, v2.end());
	for (auto& item : v) {
		std::cout << item << " ";
	}
	std::cout << "---------" << std::endl;
	v.erase(v.begin() + 1, v.end() - 1);
	for (auto& item : v) {
		std::cout << item << " ";
	}
	std::cout << "---------" << std::endl;
}

struct ObjectToSort{
	ObjectToSort(int a = 0, const std::string& s = "") :
		ma{ a }, ms{ s }{
	}
	bool operator<(const ObjectToSort& op)const {
		return std::make_pair(ma, ms) < std::make_pair(op.ma, op.ms);
	}
	int ma;
	std::string ms; 
};
/*
template< typename IT, typename PRED>
bool mfindif(IT itb, IT itend, PRED p) {
	for (auto it = itb; it != itend; ++it) {
		if (p(*it)) {
			return it; 
		}
	}
	return it; 
}*/

void testAlgo() {
	std::vector<int> v{ 5,1,4,2,3 };
	std::sort(v.begin(), v.end(), std::greater<int>() );
	for (auto& item : v) {
		std::cout << item << " ";
	}
	std::cout << "---------" << std::endl;
	std::vector<ObjectToSort> vObj{ ObjectToSort(50, "a"),
			ObjectToSort(20, "b"),
			ObjectToSort(30, "d"),ObjectToSort(20, "a") };

	std::sort(vObj.begin(), vObj.end());
	for (auto& item : vObj) {
		std::cout << item.ma<<" "<<item.ms << " ";
	}
	std::cout << "---------" << std::endl;
	std::string s;
	std::cin >> s; 
	//InputIt find_if(InputIt first, InputIt last,
	//	UnaryPredicate p);
	for (auto itb = vObj.begin(); itb != vObj.end(); ++itb) {

		auto it = std::find_if(itb, vObj.end(), [&s](const auto& p) {return  p.ms == s; });
		if (it != vObj.end()) {
			std::cout << it->ma << " " << it->ms << std::endl;
			itb = it;
		}
		else {
			std::cout << "not found " << std::endl;
		}
	}


}



int main()
{
	//TestThread testThread; 
	//testThread.runDemo();

	//testAlgo();
	//funcTestLambda<std::string>("Coucou ", " tout ", " le monde");
	//funcTestLambda<double >(1.0,2.1,3.3);
	//funcTestLambda(10., 20.2);
	
	
	//MyTestTemplate<std::string> b("Coucou ", " tout le monde");
//	std::cout << "Result " /*<< b.compute() */<< a.compute<int>(2 ) <<" " <<a.compute<double>(2.1) << std::endl;
	//std::cout << "Result " /*<< b.compute() */<< a.anycomputation(mult) << std::endl;
	//a.anycomputation(MyAdd<double>) << std::endl;
	//b.anycomputation(MyAdd<double>) << std::endl;
	//c.anycomputation(MyAdd<double>) << std::endl;
	//d.anycomputation(MyAdd<double>) << std::endl;
	//e.anycomputation(MyAdd<double>) << std::endl;

    //DemoAuto::runSamplesAuto(); 

	//DemoArray::runDemo();
	//DemoArray::runDemoCreationDuration();

	//DemoForLoop::runSample();
	//DemoForLoop::runCustomClass();

	//DemoEnum::runDemo();

	//DemoReferences::runBasic();
	//DemoReferences::runDemoMove();
	//DemoReferences::runDemocontentAfterMove();
	//DemoReferences::runDemoConstructorTest();

	//DemoRAI::DemoUniquePtrMove();
	//DemoRAI::DemoUniquePtrLeakageAndArray();
	//DemoRAI::DemoUniquePtrPolymorphisme();
	//DemoRAI::runSharedPointer();
	//DemoRAI::runWeakPointer();

	//DemoRTTI::runTypeInfo();
	//DemoRTTI::runStaticCast();
	//DemoRTTI::runStaticCast2();
	//DemoRTTI::runDynamicCast();
	//DemoRTTI::runReinterpretCast();

	// DemoSTL::capacity();
	// DemoSTL::size();
	// DemoSTL::operations();
	// DemoSTL::lambda();
	//DemoSTL::algoInAction();

	//DemoThread::runThread();
	//DemoThread::runMutex();
	//DemoThread::sharedMutex();
	//DemoThread::runFuture();
	//DemoThread::runAsync();
	DemoThread::runAtomic();
	//DemoThread::runCondition();
	/*
	Magasin m;
	m.addProduct(Pomme());
	m.addProduct(Jean());
	m.addProduct(Choux());
	m.addProduct(Jean());
	m.addProduct(Jean());
	m.addProduct(Pomme());
	m.addProduct(Jean());
	m.addProduct(Choux());
	m.addProduct(Jean());
	m.addProduct(Jean());
	std::cout << "Valeur du  stock " << m.totalAmmount() << std::endl;

	auto p = m.buyProduct(Famille::Fruit, TypeProduit::Pomme);
	std::cout << "Nombre produitcommestible : " << m.nombreCommestible() << std::endl;

	if (p) {
		//p->reduireEnCompote(); 

		std::cout << "Description produit : " << p->Description() << std::endl;
		//c'est un fruit

		Pomme* pomme = static_cast<Pomme*>(p.get());
		pomme->reduireEnCompote();
	
	}
	else {
		std::cout << "Plus de stock !!!" << std::endl;
	}
	auto p2 = m.buyProduct(Famille::Fruit, TypeProduit::Pomme);
	if (p2) {
		std::cout << "Description produit : " << p2->Description() << std::endl;
	}
	else {
		std::cout << "Plus de stock !!!" << std::endl;
	}*/
}
