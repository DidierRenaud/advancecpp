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

int main()
{
    DemoAuto::runSamplesAuto(); 

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
}
