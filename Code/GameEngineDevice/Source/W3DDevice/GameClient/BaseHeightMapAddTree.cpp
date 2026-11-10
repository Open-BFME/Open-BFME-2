// cl: /D_OPERATOR_NEW_DEFINED_ /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// BaseHeightMapRenderObjClass::addTree @0x0006813B (96 bytes, ret 0x2C) and the
// shrub twin 0x00068223: guard on the tree/shrub buffer at +0x3850 / +0x3854 and
// forward the nine arguments to W3DTreeBuffer 0x000ECF79 / W3DShrubBuffer
// 0x000E91CE. The Open-BFME-1 twin is BaseHeightMap wrapper 0x006C8950
// (BfmeConv1730). Coord3D has a user copy constructor and destructor in BFME 2
// (see BaseHeightMapAddProp.cpp); the float arguments are forwarded through the
// x87 stack exactly as retail does.
typedef float Real;

// Coord3D: retail user ctors, opt-in view (Lib/Coord3DCtorView.h); no private copy.
#define COORD3D_VIEW_DTOR
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"

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

#include "../../../Include/W3DDevice/GameClient/W3DTreeBufferClass.h"

class W3DShrubBuffer
{
public:
	void addShrub( unsigned int id, Coord3D location, Real scale, const Matrix3D *transform, Real randomScaleAmount,
		const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD );
};

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

void BaseHeightMapRenderObjClass::addTree( unsigned int id, Rva000ECF79Coord location, Real scale, const Matrix3D *transform,
	Real randomScaleAmount, const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName,
	const AsciiString &nameD )
{
	if (m_treeBuffer) {
		m_treeBuffer->addTree(id, location, scale, transform, randomScaleAmount, data, shadowKind, textureName, nameD);
	}
}

void BaseHeightMapRenderObjClass::rva00068223( unsigned int id, Coord3D location, Real scale, const Matrix3D *transform,
	Real randomScaleAmount, const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName,
	const AsciiString &nameD )
{
	if (m_shrubBuffer) {
		m_shrubBuffer->addShrub(id, location, scale, transform, randomScaleAmount, data, shadowKind, textureName, nameD);
	}
}
