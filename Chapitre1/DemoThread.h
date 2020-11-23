#pragma once
class DemoThread
{
public:
	static void runThread(); 
	static void runMutex();
	static void runCondition();
	static void sharedMutex(); 
	static void runFuture();
	static void runAsync();
	static void runAtomic();
};