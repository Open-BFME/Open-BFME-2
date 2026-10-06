// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// VectorClass<float>::VectorClass(int, const float *) at 0x001A37E0, split out
// of the hanim.cpp instantiation chain because retail built it with /G7 -- the
// array-new size multiply is add eax,eax twice, not shl eax,2 -- while the
// rest of hanim.cpp only matches without that flag. Same pattern as
// hanim_weight_vector_add.cpp. Explicit instantiation keeps the TU to one
// line of real code; headers copied from hanim.cpp.
// LINK-COMDAT 2026-10-02: this TU owns only the (int, const T *) ctor row.
// Including hanim.h pulled in vector.h's full template bodies, so this unit
// emitted its own differing copies of the virtuals (operator==, Resize,
// Clear, both IDs, deleting dtor) that the census keeps from pointgr.cpp /
// ode.cpp. Declare the rest instead of defining it, so calls reach the kept
// copies. The dtor is really virtual (UAE, rowed from pointgr); it is
// declared non-virtual here only to suppress our own ??_G, which would
// otherwise differ the way the inlined Clear version does (71B kept with
// inlined Clear vs 34B calling Clear). No vtable is emitted here; the ctor's
// vptr store resolves to the kept table at link. Precedent:
// vector_class_vector3_ctor.cpp (dd808c3101).
#include "always.h"
#include <new.h>

template<class T>
class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	~VectorClass();
	virtual bool operator==(const VectorClass<T> &that) const;
	virtual bool Resize(int newsize, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &ptr);
protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
VectorClass<T>::VectorClass(int size, T const *array) :
	Vector(0),
	VectorMax(size),
	IsValid(true),
	IsAllocated(false)
{
	if (size) {
		if (array) {
			Vector = new((void *)array) T[size];
		} else {
			Vector = new T[size];
			IsAllocated = true;
		}
	}
}

template VectorClass<float>::VectorClass(int, float const *);
