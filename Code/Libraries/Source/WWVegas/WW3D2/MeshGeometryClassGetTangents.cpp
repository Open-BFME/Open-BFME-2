// cl: /DNDEBUG /MD /EHsc /G7
// ?rva0016ABC0@MeshGeometryClass@@QAEPAVVector3@@XZ
//
// MeshGeometryClass::rva0016ABC0 at 0x0016ABC0 (20 bytes): returns
// VertexTangents array when its ShareBuffer count is positive else null.
// Evidence: MeshGeometry region (next 0x0016AC00 get_planes); +0x40 is
// VertexTangents per Reset/Copy TUs; ShareBuffer Array +0x0C Count +0x10
// per sharebuf.h; caller 0x0018CC38.

class Vector3
{
public:
	float x, y, z;
};
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

class MeshGeometryClass
{
public:
	virtual void s0(); virtual void s1(); virtual void s2();
	virtual void onPlanes(Vector4 *planes);
public:
	Vector3 *rva0016ABC0();
	Vector3 *rva0016ABE0();
	char m_pad[0x18 - 4];
	unsigned int m_flags;			// +0x18
	char m_pad1C[0x24 - 0x1C];
	int PolyCount;				// +0x24
	char m_pad28[0x40 - 0x28];		// +0x28..+0x40
	ShareBufferClass<Vector3> *VertexTangents;	// +0x40
	ShareBufferClass<Vector3> *VertexBinormals;	// +0x44
	ShareBufferClass<Vector4> *PlaneEq;		// +0x48
};

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
