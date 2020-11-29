#pragma once

template< typename T>
inline T MyAdd(const T& a, const T& b) {
	return a + b;
}

template< typename T>
struct MyMultiply {
	MyMultiply(T pa) : ma{pa} {}
	T operator () (T val1, T val2) {
		return val1 * val2 * ma;
	}
	T ma;
};


template< typename T>
struct MyTestTemplate
{
	MyTestTemplate(const T& pa, const T& pb) :a{ pa }, b{ pb } {

	}
	/*template< typename U>
	T compute(const U& u)const {
		return u*(a + b);
	}*/
	template< typename U>
	T anycomputation( U u)const {
		return u( a, b ); 
		//(const T&,const T&  )
		//(T,T)
	}
	T a; 
	T b;
};