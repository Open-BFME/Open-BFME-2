// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Two guarded forwarders at 0x00091E83 and 0x00091FBA (90 bytes each, ret 0x2C):
// when the target at +0x14 is set, the nine-argument terrain add is passed on to
// BaseHeightMapRenderObjClass::addTree (0x0006813B) and its shrub twin
// (0x00068223) with the by-value location going through Coord3D's user copy
// constructor, exactly as those callees' own bodies do. Owner class unknown:
// honest address-derived names.
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

class BaseHeightMapRenderObjClass
{
public:
	void addTree( unsigned int id, Rva000ECF79Coord location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD );
	void rva00068223( unsigned int id, Coord3D location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD );
};

class Rva00091E83
{
public:
	void rva00091E83( unsigned int id, Rva000ECF79Coord location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD );
private:
	char m_pad00[ 0x14 ];
	BaseHeightMapRenderObjClass *m_terrain;	///< 0x14
};

class Rva00091FBA
{
public:
	void rva00091FBA( unsigned int id, Coord3D location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD );
private:
	char m_pad00[ 0x14 ];
	BaseHeightMapRenderObjClass *m_terrain;	///< 0x14
};

void Rva00091E83::rva00091E83( unsigned int id, Rva000ECF79Coord location, Real scale, const Matrix3D *transform,
	Real randomScaleAmount, const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName,
	const AsciiString &nameD )
{
	if (m_terrain) {
		m_terrain->addTree(id, location, scale, transform, randomScaleAmount, data, shadowKind, textureName, nameD);
	}
}

void Rva00091FBA::rva00091FBA( unsigned int id, Coord3D location, Real scale, const Matrix3D *transform,
	Real randomScaleAmount, const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName,
	const AsciiString &nameD )
{
	if (m_terrain) {
		m_terrain->rva00068223(id, location, scale, transform, randomScaleAmount, data, shadowKind, textureName, nameD);
	}
}
