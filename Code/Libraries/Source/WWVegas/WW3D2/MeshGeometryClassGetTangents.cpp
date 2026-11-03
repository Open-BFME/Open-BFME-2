// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva0016ABC0@MeshGeometryClass@@QAEPAVVector3@@XZ
//
// MeshGeometryClass::rva0016ABC0 at 0x0016ABC0 (20 bytes): returns
// VertexTangents array when its ShareBuffer count is positive else null.
// Evidence: MeshGeometry region (next 0x0016AC00 get_planes); +0x40 is
// VertexTangents per Reset/Copy TUs; ShareBuffer Array +0x0C Count +0x10
// per sharebuf.h; caller 0x0018CC38.

#include "../WWMath/Vector3Data.h"
class Vector4;

template<class T>
class ShareBufferClass
{
public:
	unsigned char m_pad00[0x0C];
public:
	T *Array;	// +0x0C
	int Count;	// +0x10
private:
	int m_align;	// +0x14
};

#include "MeshGeometryClass.h"

Vector3 *MeshGeometryClass::rva0016ABC0()
{
	ShareBufferClass<Vector3> *buf = VertexTangents;
	if (buf != 0 && buf->Count > 0) {
		return buf->Array;
	}
	return 0;
}

Vector3 *MeshGeometryClass::rva0016ABE0()
{
	ShareBufferClass<Vector3> *buf = VertexBinormals;
	if (buf != 0 && buf->Count > 0) {
		return buf->Array;
	}
	return 0;
}
