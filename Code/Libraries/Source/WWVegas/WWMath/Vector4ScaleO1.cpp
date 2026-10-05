// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
//
// vector4.h's scalar-first operator * (float, const Vector4 &), retail
// 0x00308182 69B: an out-of-line /O1 /arch:SSE copy that no retail call
// reaches, placed uniquely by a Zero Hour WWMath sweep at /O1 /G7 /arch:SSE.
// The scalar is read from [esp+8] and the vector from [esp+0xC] (the hidden
// return pointer is [esp+4]), which tells it from the vector-first
// operator * (0x00191070) of the same size. The anchor below only makes
// this unit emit the copy; it is not retail code.
#include "vector4.h"

#pragma inline_depth(0)
// ?_bfmeVector4ScaleAnchor@@YAXAAVVector4@@ABV1@@Z absent-from-retail
void _bfmeVector4ScaleAnchor(Vector4 &out, const Vector4 &in)
{
	out = 2.0f * in;
}
#pragma inline_depth()
