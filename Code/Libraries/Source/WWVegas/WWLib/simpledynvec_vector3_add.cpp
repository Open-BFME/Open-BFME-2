// cl: /MD
//
// SimpleDynVecClass<Vector3>::Add, retail 0x001002C5, 65 bytes.
// Dedicated TU so segline.cpp keeps its matched bodies.

#include "../WWMath/Vector3Data.h"
static __forceinline Vector3 &copyAddedVector(Vector3 &out,const Vector3 &in) {out.X=in.X;out.Y=in.Y;out.Z=in.Z;return out;}



template <class Type>
class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass();
	bool Add(const Type &object, int new_size_hint);
	bool Grow(int new_size_hint);

	Type *Vector;
	int VectorMax;
	int ActiveCount;
};

template <class Type>
bool SimpleDynVecClass<Type>::Add(const Type &object, int new_size_hint)
{
	if (ActiveCount >= VectorMax) {
		if (!Grow(new_size_hint))
			return false;
	}
	int n = ActiveCount;
	ActiveCount = n + 1;
	n *= sizeof(Vector3);
	Type *slot = (Type *)((char *)Vector + n);
	copyAddedVector(*slot, object);
	return true;
}

template bool SimpleDynVecClass<Vector3>::Add(const Vector3 &, int);
