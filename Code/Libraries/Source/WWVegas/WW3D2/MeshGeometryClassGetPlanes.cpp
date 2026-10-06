// cl: /DNDEBUG /MD /EHsc
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
void *__cdecl operator new(unsigned int size);

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

class MeshGeometryClass
{
public:
	virtual void s0(); virtual void s1(); virtual void s2();
	virtual void onPlanes(Vector4 *planes);
protected:
	Vector4 *get_planes(bool create);
	char m_pad[0x18 - 4];
	unsigned int m_flags;				// +0x18
	char m_pad1C[0x24 - 0x1C];
	int PolyCount;					// +0x24
	char m_pad28[0x48 - 0x28];
	ShareBufferClass<Vector4> *PlaneEq;	// +0x48
};

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
