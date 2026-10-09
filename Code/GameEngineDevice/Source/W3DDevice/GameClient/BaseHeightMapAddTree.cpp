// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// BaseHeightMapRenderObjClass::addTree @0x0006813B (96 bytes, ret 0x2C) and the
// shrub twin 0x00068223: guard on the tree/shrub buffer at +0x3850 / +0x3854 and
// forward the nine arguments to W3DTreeBuffer 0x000ECF79 / W3DShrubBuffer
// 0x000E91CE. The Open-BFME-1 twin is BaseHeightMap wrapper 0x006C8950
// (BfmeConv1730). Coord3D has a user copy constructor and destructor in BFME 2
// (see BaseHeightMapAddProp.cpp); the float arguments are forwarded through the
// x87 stack exactly as retail does.
typedef float Real;

// class-gate: allow Coord3D proved codegen view: BFME 2 passes Coord3D by value through a user copy constructor and destructor (as in BaseHeightMapAddProp.cpp); the shared header's trivial Coord3D would be copied with a block move
struct Coord3D
{
	Real x;
	Real y;
	Real z;
	Coord3D( const Coord3D &c ) { x = c.x; y = c.y; z = c.z; }
	~Coord3D() {}
};

// ECF79's own by-value location view; same shape and user copy semantics.
struct Rva000ECF79Coord
{
	Real x;
	Real y;
	Real z;
	Rva000ECF79Coord( const Rva000ECF79Coord &c ) { x = c.x; y = c.y; z = c.z; }
	~Rva000ECF79Coord() {}
};

#include "ascii_string.h"

class Matrix3D;
struct Rva000ECF79Data;
struct Rva000E91CEData;

class W3DTreeBuffer
{
public:
	void rva000ECF79( unsigned int id, Rva000ECF79Coord location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD );
};

class W3DShrubBuffer
{
public:
	void rva000E91CE( unsigned int id, Coord3D location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD );
};

class BaseHeightMapRenderObjClass
{
public:
	void addTree( unsigned int id, Rva000ECF79Coord location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD );
	void rva00068223( unsigned int id, Coord3D location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD );
private:
	char m_unrecovered0000[ 0x3850 ];
	W3DTreeBuffer *m_treeBuffer;	///< 0x3850
	W3DShrubBuffer *m_shrubBuffer;	///< 0x3854
};

void BaseHeightMapRenderObjClass::addTree( unsigned int id, Rva000ECF79Coord location, Real scale, const Matrix3D *transform,
	Real randomScaleAmount, const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName,
	const AsciiString &nameD )
{
	if (m_treeBuffer) {
		m_treeBuffer->rva000ECF79(id, location, scale, transform, randomScaleAmount, data, shadowKind, textureName, nameD);
	}
}

void BaseHeightMapRenderObjClass::rva00068223( unsigned int id, Coord3D location, Real scale, const Matrix3D *transform,
	Real randomScaleAmount, const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName,
	const AsciiString &nameD )
{
	if (m_shrubBuffer) {
		m_shrubBuffer->rva000E91CE(id, location, scale, transform, randomScaleAmount, data, shadowKind, textureName, nameD);
	}
}
