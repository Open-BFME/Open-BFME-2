// cl: /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// VectorClass<NamedPivotMapClass::WeightInfoStruct>::Resize at 0x00197270,
// split out of hanim.cpp because retail built it with /G7 (cmp-mem count and
// flag tests plus add-reg growth, where the default build hoists loads and
// emits inc). Self-contained like TextureStatisticsVectorResize.cpp: the
// nested element replica mangles identically, and the VectorClass template
// plus Resize body are the WWLib Vector.H canonical source verbatim.

#include <new.h>
#include <assert.h>
#include "nstrdup.h"

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer);

// upstream layout: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
// (nested scope replica; public here for access, which changes no bytes)
class NamedPivotMapClass
{
public:
	struct WeightInfoStruct {
		WeightInfoStruct() : Name(0) {}
		~WeightInfoStruct() { if(Name) delete [] Name; }

		char *Name;
		float Weight;

		WeightInfoStruct & operator = (WeightInfoStruct const &that);
		bool operator == (WeightInfoStruct const &that) const { return &that == this; }
		bool operator != (WeightInfoStruct const &that) const { return &that != this; }
	};
};

inline NamedPivotMapClass::WeightInfoStruct & NamedPivotMapClass::WeightInfoStruct::operator = (WeightInfoStruct const &that)
{
	if(Name) delete [] Name;
	assert(that.Name != 0);
	Name = nstrdup(that.Name);
	Weight = that.Weight;
	return *this;
}

template<class T>
class VectorClass
{
public:
	VectorClass(unsigned size, T const *array);
	VectorClass(VectorClass const &);
	virtual ~VectorClass();
	VectorClass &operator=(VectorClass const &);
	virtual bool operator==(VectorClass const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);
	int Length() const { return VectorMax; }
	T &operator[](int index) { return Vector[index]; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
bool VectorClass<T>::Resize(int newsize, T const *array)
{
	if (newsize)
	{
		T *newptr;
		IsValid = false;
		if (!array)
		{
			newptr = new T[newsize];
		}
		else
		{
			newptr = new ((void *)array) T[newsize];
		}
		IsValid = true;
		if (!newptr)
			return false;

		if (Vector != 0)
		{
			int copycount = (newsize < VectorMax) ? newsize : VectorMax;
			for (int index = 0; index < copycount; ++index)
				newptr[index] = Vector[index];

			if (IsAllocated)
			{
				delete [] Vector;
				Vector = 0;
			}
		}

		Vector = newptr;
		VectorMax = newsize;
		IsAllocated = (Vector && !array);
	}
	else
	{
		Clear();
	}
	return true;
}

// ?Resize@?$VectorClass@UWeightInfoStruct@NamedPivotMapClass@@@@UAE_NHPBUWeightInfoStruct@NamedPivotMapClass@@@Z
template bool VectorClass<NamedPivotMapClass::WeightInfoStruct>::Resize(int, NamedPivotMapClass::WeightInfoStruct const *);
