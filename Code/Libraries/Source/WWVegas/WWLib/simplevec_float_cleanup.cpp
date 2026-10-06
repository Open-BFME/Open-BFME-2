// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// StreakLine's matched constructor initializes the float widths member at +0xF0.
// Its derived/base tables BD41B8/BD41AC point to these deleting destructors.
// /O1 preserves the target's separate base and derived cleanup calls.
#include "always.h"
#include <assert.h>
void __cdecl operator delete[](void *) throw();

// LINK-COMDAT 2026-10-02: this TU owns only the two dtors, the two deleting
// dtors and Add. A whole-class instantiation emitted its own /O1 copies of 8
// inline members (both ctors, Delete_All, Grow, both Resizes, Shrink,
// Uninitialised_Grow) that the census keeps from streak.cpp/lookuptable.cpp.
// Declare the rest instead of defining it, so calls reach the kept copies.
// Trivial inlines (operator[], Length, Count) stay inline so Add's bytes keep
// their inlined indexing; Add calls (not inlines) Grow and the dtors touch no
// other member, so their bytes are unchanged. Layout and virtual order match
// simplevec.h.
template<class T> class SimpleVecClass
{
public:
	SimpleVecClass(int size = 0);
	virtual ~SimpleVecClass(void);
	T & operator[](int index) { assert(index < VectorMax); return(Vector[index]); }
	T const & operator[](int index) const { assert(index < VectorMax); return(Vector[index]); }
	int Length(void) const { return VectorMax; }
	virtual bool Resize(int newsize);
	virtual bool Uninitialised_Grow(int newsize);
	void Zero_Memory(void);
protected:
	T *Vector;
	int VectorMax;
};

template<class T> class SimpleDynVecClass : public SimpleVecClass<T>
{
public:
	SimpleDynVecClass(int size = 0);
	virtual ~SimpleDynVecClass(void);
	int Count(void) const { return ActiveCount; }
	T & operator[](int index) { assert(index < ActiveCount); return this->Vector[index]; }
	T const & operator[](int index) const { assert(index < ActiveCount); return this->Vector[index]; }
	virtual bool Resize(int newsize);
	bool Add(T const & object, int new_size_hint = 0);
	T * Add_Multiple(int number_to_add);
	bool Delete(int index, bool allow_shrink = true);
	bool Delete(T const & object, bool allow_shrink = true);
	bool Delete_Range(int start, int count, bool allow_shrink = true);
	void Delete_All(bool allow_shrink = true);
protected:
	bool Grow(int new_size_hint);
	bool Shrink(void);
	int Find_Index(T const & object);
	int ActiveCount;
};

template<class T>
inline SimpleVecClass<T>::~SimpleVecClass(void)
{
	if (Vector != NULL) {
		delete[] Vector;
		Vector = NULL;
		VectorMax = 0;
	}
}

template<class T>
inline SimpleDynVecClass<T>::~SimpleDynVecClass(void)
{
	if (Vector != NULL) {
		delete[] Vector;
		Vector = NULL;
	}
}

template<class T>
inline bool SimpleDynVecClass<T>::Add(T const & object, int new_size_hint)
{
	if (ActiveCount >= VectorMax) {
		if (!Grow(new_size_hint)) {
			return false;
		}
	}
	(*this)[ActiveCount++] = object;
	return true;
}

// LINK-COMDAT 2026-10-02: this TU owns only the two dtors, the two deleting
// dtors and Add. A whole-class instantiation emitted its own /O1 copies of 8
// inline members (both ctors, Delete_All, Grow, both Resizes, Shrink,
// Uninitialised_Grow) that the census keeps from streak.cpp/lookuptable.cpp.
// Explicitly instantiate only the owned members so calls reach the kept
// copies; Add still calls Grow (not inlined) and the dtors touch no other
// member, so their bytes are unchanged.
template SimpleVecClass<float>::~SimpleVecClass();
template SimpleDynVecClass<float>::~SimpleDynVecClass();
template bool SimpleDynVecClass<float>::Add(float const &, int);
