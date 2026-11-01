// cl: /DNDEBUG /MD /GX
//
// Snapshot xfer methods (slot 3) of three BFME 2 model draws without a Zero
// Hour counterpart, each named by its vftable's slot-2 name literal and built on the base
// W3DScriptedModelDraw::xfer (pinned 0x000C5C04), in the Xfer view of
// W3DTankDrawXfer.cpp:
//
//  - W3DQuadrupedDraw::xfer, retail 0x000CA137 (27 bytes; vftable 0x00BCBC40):
//    version then the base, like W3DTankDraw.
//  - W3DHordeModelDraw::xfer, retail 0x00078BBB (51 bytes; vftable 0x00BC68F0):
//    the base, then (skipped for a light CRC) the Int at +0x2EC and a
//    trailing version.
//  - W3DSailModelDraw::xfer, retail 0x000D0816 (72 bytes; vftable 0x00BCDC60):
//    the base, then version, the Real at +0x2E8 and the Bool at +0x2EC.
//
// Members are labelled by offset and Xfer overload only.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../../../GameEngine/Include/Common/BfmeXfer.h"

#include "../../../../../../GameEngine/Include/Common/XferVersion.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

class W3DScriptedModelDraw
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
};

class W3DQuadrupedDraw : public W3DScriptedModelDraw
{
protected:
	virtual void xfer( Xfer *xfer );
};

class W3DHordeModelDraw : public W3DScriptedModelDraw
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x2EC - 0x04 ];
	Int m_bfmeValue2EC;																												///< 0x2EC
};

class W3DSailModelDraw : public W3DScriptedModelDraw
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x2E8 - 0x04 ];
	Real m_bfmeReal2E8;																												///< 0x2E8
	Bool m_bfmeFlag2EC;																												///< 0x2EC
};

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void W3DQuadrupedDraw::xfer( Xfer *xfer )
{
	xfer->Version1();
	W3DScriptedModelDraw::xfer( xfer );
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void W3DHordeModelDraw::xfer( Xfer *xfer )
{
	W3DScriptedModelDraw::xfer( xfer );
	if( xfer->IsLightCRC() )
		return;
	*xfer == m_bfmeValue2EC;
	xfer->Version1();
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method */
// ------------------------------------------------------------------------------------------------
void W3DSailModelDraw::xfer( Xfer *xfer )
{
	W3DScriptedModelDraw::xfer( xfer );
	Xfer::Version version( 1, 1 );
	*xfer == version;
	*xfer == m_bfmeReal2E8;
	*xfer == m_bfmeFlag2EC;
}  // end xfer
