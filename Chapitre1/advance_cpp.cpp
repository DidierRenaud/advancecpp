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
int main()
{
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
	//DemoThread::runAtomic();
	//DemoThread::runCondition();

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
		std::cout << "Description produit : " << p->Description() << std::endl;
		//c'est un fruit
		Pomme* pomme = dynamic_cast<Pomme*>(p.get());
		if (pomme) {
			pomme->reduireEnCompote();
		}
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
	}
}
