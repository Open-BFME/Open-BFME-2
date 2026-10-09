// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// BaseHeightMapRenderObjClass guarded forwarders to the tree buffer (+0x3850) and shrub buffer (+0x3854) record
// move: 0x00067FCD (74 bytes, ret 0x14) forwards to W3DTreeBuffer 0x000EA327 and 0x00068017 (74 bytes) to
// W3DShrubBuffer 0x000E7140; both return 0 without a buffer. The by-value Vector3 argument is rebuilt on the
// stack with component copies. Opaque identities: honest address-derived names.
// BFME 2 passes Vector3 by value through a user copy constructor and destructor (the callee address of the
// temporary is kept in the dead argument slot), as for Coord3D in BaseHeightMapAddTree.cpp.
class Vector3
{
public:
	Vector3( const Vector3 &v ) { X = v.X; Y = v.Y; Z = v.Z; }
	~Vector3() {}
	float X;
	float Y;
	float Z;
};

class Matrix3D;

class W3DTreeBuffer
{
public:
	char rva000EA327( void *key, Vector3 position, const Matrix3D *transform );
};

class W3DShrubBuffer
{
public:
	char rva000E7140( void *key, Vector3 position, const Matrix3D *transform );
};

class BaseHeightMapRenderObjClass
{
public:
	char rva00067FCD( void *key, Vector3 position, const Matrix3D *transform );
	char rva00068017( void *key, Vector3 position, const Matrix3D *transform );
private:
	char m_unrecovered0000[ 0x3850 ];
	W3DTreeBuffer *m_treeBuffer;	///< 0x3850
	W3DShrubBuffer *m_shrubBuffer;	///< 0x3854
};

char BaseHeightMapRenderObjClass::rva00067FCD( void *key, Vector3 position, const Matrix3D *transform )
{
	if (m_treeBuffer) {
		return m_treeBuffer->rva000EA327(key, position, transform);
	}
	return 0;
}

char BaseHeightMapRenderObjClass::rva00068017( void *key, Vector3 position, const Matrix3D *transform )
{
	if (m_shrubBuffer) {
		return m_shrubBuffer->rva000E7140(key, position, transform);
	}
	return 0;
}
