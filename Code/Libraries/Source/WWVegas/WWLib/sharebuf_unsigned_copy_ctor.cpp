// cl: /DNDEBUG /MD /EHsc
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
//
// ShareBufferClass<unsigned> copy constructor at target RVA 0x0015B000.
//
// BFME's ShareBufferClass carries an Alignment member beside Zero Hour's Count:
// zero means a plain new[] with Array aliasing RawBuffer, anything else means a
// raw char buffer over-allocated by Alignment with Array rounded up inside it.
// The matched aligned Vector2 donor is adapted only where target evidence
// identifies the element type. /G7 writes add reg,1 and add reg,-1 where /G6
// writes inc and dec.

#include <new>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
// Retail's out-of-line RefCountClass deleting-dtor copy is the /O1 form
// (pop ecx after the delete call); this TU builds /G7 which emits add esp,4
// instead. Compile just the base class for size so our COMDAT matches the
// first copy in link order. Code this TU's rows inline keeps this TU's flags.
#pragma optimize("s", on)
#include "RefCountData.h"
inline RefCountClass::~RefCountClass() {}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/sharebuf.h,
// with BFME's RawBuffer/Alignment pair around Zero Hour's Array and Count.
template <class Type>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(const ShareBufferClass &);
	~ShareBufferClass();

protected:
	Type *RawBuffer;
	Type *Array;
	int Count;
	int Alignment;
};

// The region supplies /O2 /arch:SSE /G7. Keep the explicit copy constructor
// in its native speed profile and emit the deferred virtual wrapper for size.
// No new imported symbols or virtual slots are introduced.
template <> ShareBufferClass<unsigned>::ShareBufferClass(const ShareBufferClass<unsigned> &);
template class ShareBufferClass<unsigned>;
#pragma optimize("gt", on)
template <>
ShareBufferClass<unsigned>::ShareBufferClass(const ShareBufferClass<unsigned> &that) :
	Count(that.Count)
{
	Alignment = that.Alignment;
	if (Alignment == 0) {
		RawBuffer = new unsigned[Count];
		Array = RawBuffer;
	} else {
		RawBuffer = (unsigned *)new char[Count * sizeof(unsigned) + Alignment];
		Array = (unsigned *)(((unsigned int)RawBuffer + Alignment - 1) &
			~(unsigned int)(Alignment - 1));
	}
	for (int index = 0; index < Count; ++index) {
		Array[index] = that.Array[index];
	}
}

#pragma optimize("s", on)

// Color cloning15B840 calls this175-byte constructor. Its vtableBCE330
// agrees with the unsigned-buffer constructor used by Get_Color_Array D1FBD.
