// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
// Westwood simplevec.h at BFME1 575ba2b04 supplies the vector constructor
// and resize semantics. Native16844F/168527/168605 identify the Vector3
// points and float widths; both vector vtable pairs have owned destructors.
// These genuine instantiations are full byte-and-relocation twins of the
// earlier opaque owners; they add no unique retail coverage.
// Copy construction reads only pointer/count words and cannot throw under
// the retail /EHsc contract. It remains shallow, as the target39B proves.
#include "always.h"
#include <string.h>
void __cdecl operator delete[](void*) throw();
class Vector3{public:float X,Y,Z;};
template<class T>class SimpleVecClass {
public:
 SimpleVecClass(int n=0);
 __forceinline SimpleVecClass(const SimpleVecClass&r) throw():Vector(r.Vector),VectorMax(r.VectorMax){}
 virtual ~SimpleVecClass();
 virtual bool Resize(int n);
 virtual bool Uninitialised_Grow(int n);
protected:T*Vector;int VectorMax;
};
template<class T>class SimpleDynVecClass:public SimpleVecClass<T>{
public:
 SimpleDynVecClass(int n=0);
 SimpleDynVecClass(const SimpleDynVecClass&r) throw();
 virtual ~SimpleDynVecClass();
 virtual bool Resize(int n);
protected:int ActiveCount;
};
template<class T> SimpleVecClass<T>::SimpleVecClass(int n):Vector(0),VectorMax(0){if(n>0)Resize(n);}
template<class T> SimpleDynVecClass<T>::SimpleDynVecClass(int n):SimpleVecClass<T>(n),ActiveCount(0){}
template<class T> SimpleDynVecClass<T>::SimpleDynVecClass(const SimpleDynVecClass&r) throw():SimpleVecClass<T>(r),ActiveCount(r.ActiveCount){}
template<class T>
inline bool SimpleVecClass<T>::Resize(int newsize)
{
	if (newsize == VectorMax) {
		return true;
	}
	
	if (newsize > 0) {

		/*
		**	Allocate a new vector of the size specified. The default constructor
		**	will be called for every object in this vector.
		*/
		T * newptr = W3DNEWARRAY T[newsize];

		/*
		**	If there is an old vector, then it must be copied (as much as is feasible)
		**	to the new vector.
		*/
		if (Vector != NULL) {

			/*
			**	Mem copy as much of the old vector into the new vector as possible.
			*/
			int copycount = (newsize < VectorMax) ? newsize : VectorMax;
			memcpy(newptr,Vector,copycount * sizeof(T));

			/*
			**	Delete the old vector.
			*/
			delete[] Vector;
			Vector = NULL;
		}

		/*
		**	Assign the new vector data to this class.
		*/
		Vector = newptr;
		VectorMax = newsize;

	} else {

		/*
		** Delete entire vector and reset counts
		*/
		VectorMax = 0;
		if (Vector != NULL) {
			delete[] Vector;
			Vector = NULL;
		}
	}
	return true;
}
template bool SimpleVecClass<float>::Resize(int);
template SimpleVecClass<float>::SimpleVecClass(int);
template SimpleDynVecClass<float>::SimpleDynVecClass(int);
template SimpleDynVecClass<float>::SimpleDynVecClass(const SimpleDynVecClass<float>&) throw();
