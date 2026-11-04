// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// ?get_planes@MeshGeometryClass@@IAEPAVVector4@@_N@Z
//
// MeshGeometryClass::get_planes at 0x0016AC00 (136 bytes): lazily builds
// the cached plane-equation buffer and returns its array. Ported from
// Open-BFME-1 MeshGeometryClass_Get_Planes.cpp with BFME2 adaptations:
// PlaneEq at +0x48 (B1 +0x50), PolyCount at +0x24, plain scalar new
// (no pool glue), Array at +0x0C. Only two out-of-line callees, both
// already matched: scalar operator new and ShareBufferClass<Vector4>
// constructor. /G7 for the cmp-mem create-test (load-hoist family).

class Vector4;
#include <new>
// The toolchain supplies placement operators; suppress always.h's copies.
#define _OPERATOR_NEW_DEFINED_

template<class T>
class ShareBufferClass
{
public:
	ShareBufferClass(int count, char const *name, int flags);

private:
	unsigned char m_pad00[0x0C];
public:
	T *Array;			// +0x0C
private:
	unsigned char m_pad10[0x18 - 0x10];
};

#include "MeshGeometryClass.h"

// ?get_planes@MeshGeometryClass@@IAEPAVVector4@@_N@Z
Vector4 *MeshGeometryClass::get_planes(bool create)
{
	if (create && PlaneEq == 0) {
		PlaneEq = new ShareBufferClass<Vector4>(PolyCount, "MeshGeometryClass::PlaneEq", 0);
	}
	ShareBufferClass<Vector4> *planes = PlaneEq;
	if (planes != 0) {
		return planes->Array;
	}
	return 0;
}
