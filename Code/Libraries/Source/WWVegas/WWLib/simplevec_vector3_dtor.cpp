// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O1 /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// ??1?$SimpleVecClass@VVector3@@@@UAE@XZ, retail 0x0007E1AE, 33 bytes.
// Target evidence: the body stores vtable 0x00BC6F44, which the matched
// SegmentedLine/StreakLine bodies encode as ??_7SimpleVecClass<Vector3>;
// the shape (vptr store, delete[] of Vector via 0x0002FD80, zero Vector and
// VectorMax) is the vendor simplevec.h dtor. Recipe from the matched
// SimpleVecClass<float> dtor in simplevec_float_cleanup.cpp. The scalar
// deleting dtor at 0x0007E320 calls this body.
#include <new>
// Use the toolchain allocation declarations and placement operators.
#define _OPERATOR_NEW_DEFINED_
#include "always.h"
#include "simplevec.h"

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

// Resize and Uninitialised_Grow are owned by SimpleVecVector3ResizeO1.cpp and
// SimpleVecVector3O1.cpp: retail builds the array through the EH vector
// constructor iterator, which this unit's bare Vector3 cannot reproduce, so
// its copies would differ from retail's (and, first in link order, displace
// them). Only the bodies this unit owns are instantiated here.
template <> bool SimpleVecClass<Vector3>::Resize(int newsize);
template <> bool SimpleVecClass<Vector3>::Uninitialised_Grow(int newsize);
template SimpleVecClass<Vector3>::SimpleVecClass(int size);
template SimpleVecClass<Vector3>::~SimpleVecClass();

// ??1?$SimpleDynVecClass@VVector3@@@@UAE@XZ, retail 0x0007E2D7, 35 bytes:
// stores 0x00BC6F50 (SimpleDynVecClass<Vector3> per the matched segline and
// streak bodies), frees and zeroes Vector, then tail-jumps to the base dtor
// above (0x0007E1AE).
template SimpleDynVecClass<Vector3>::~SimpleDynVecClass();
// ?Resize@?$SimpleDynVecClass@VVector3@@@@UAE_NH@Z retail 0x0007E9BA 37B Dyn
// clamp of ActiveCount to Length after Base Resize. Evidence: chain calls
// 0x0007E1CF; vslot 1 of 0x007C6F50.
bool inline SimpleDynVecClass<Vector3>::Resize(int newsize)
{
	if (SimpleVecClass<Vector3>::Resize(newsize))
	{
		if (Length() < ActiveCount)
			ActiveCount = Length();
		return true;
	}
	return false;
}
// ??0?$SimpleDynVecClass@VVector3@@@@QAE@H@Z retail 0x0007E99E 28B Dyn ctor
// via Base ctor plus ActiveCount 0. Evidence: chain calls 0x0007E3D9;
// callers at 0x0007EEB5 0x0007FBB0 0x0007FBF1 0x0010070F 0x0010071B
// 0x0016847E.
inline SimpleDynVecClass<Vector3>::SimpleDynVecClass(int size) :
	SimpleVecClass<Vector3>(size),
	ActiveCount(0)
{
}

// Emit the owned constructor and Resize as select-any template bodies.
template SimpleDynVecClass<Vector3>::SimpleDynVecClass(int size);
template bool SimpleDynVecClass<Vector3>::Resize(int newsize);
