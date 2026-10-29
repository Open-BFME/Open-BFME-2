// cl: /O1 /DNDEBUG /MD /GX
// stlport
//
// GiantBirdAIUpdate::xfer, retail 0x0036AC73 (390 bytes). BFME 2 only: neither
// Zero Hour nor the BFME 1 tree has a GiantBirdAIUpdate xfer. Evidence, all
// read from retail:
//
//  - it is slot 3 of GiantBirdAIUpdate's primary vftable 0x00C17A80;
//  - Version(1,2) through Xfer slot 0x28, then the base AIUpdateInterface::xfer
//    (0x00267EDD), then the light-CRC gate (slot 0x10);
//  - the fields are those the rowed constructor 0x0036B717 lays out: the
//    +0x3F0 command storage's doXfer (0x003533BF), the +0x4B4 int list
//    through the rowed list helper 0x0036ABAF, ObjectIDs through the rowed
//    XferObjectID 0x003060B2, Xfer::XferRawBytes for the two 4-byte fields
//    +0x528 and +0x55C, and the Xfer operator== slots for the rest (Coord3D
//    0x60, float 0x70, int 0x7C, bool 0x90 -- MSVC groups the overloads in
//    reverse declaration order);
//  - +0x560, +0x56C and +0x578 are transferred only from version 2 on.
//
// Field names stay offset-derived; their semantics are not recovered.

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

#include "../../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef bool Bool;
typedef int Int;
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

// The real STLport list provides the mangled name and 4-byte size.
#include <list>

Xfer *Rva0036ABAFXfer( Xfer *xfer, _STL::list<Int> *value );

class Rva0026AFDAMember
{
public:
	void doXfer( Xfer *xfer );
private:
	unsigned char m_unrecovered00[ 0xC4 ];
};

class AIUpdateInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
};

class GiantBirdAIUpdate : public AIUpdateInterface
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	unsigned char m_unrecovered04[ 0x3E4 - 0x04 ];
	Coord3DBase m_3E4;								///< 0x3E4
	Rva0026AFDAMember m_3F0;						///< 0x3F0
	_STL::list<Int> m_4B4;							///< 0x4B4
	Int m_4B8;										///< 0x4B8
	Real m_4BC;										///< 0x4BC
	ObjectID m_4C0;									///< 0x4C0
	ObjectID m_4C4;									///< 0x4C4
	unsigned char m_unrecovered4C8[ 0x60 ];			///< 0x4C8
	Int m_528;										///< 0x528
	Real m_52C;										///< 0x52C
	Real m_530;										///< 0x530
	Bool m_534;										///< 0x534
	Real m_538;										///< 0x538
	Real m_53C;										///< 0x53C
	Real m_540;										///< 0x540
	Coord3DBase m_544;								///< 0x544
	Bool m_550;										///< 0x550
	ObjectID m_554;									///< 0x554
	Bool m_558;										///< 0x558
	Int m_55C;										///< 0x55C
	Coord3DBase m_560;								///< 0x560
	Coord3DBase m_56C;								///< 0x56C
	Bool m_578;										///< 0x578
};

void GiantBirdAIUpdate::xfer( Xfer *xfer )
{
	Xfer::Version version(1, 2);
	*xfer == version;

	AIUpdateInterface::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	m_3F0.doXfer( xfer );
	*xfer == m_3E4;
	Rva0036ABAFXfer( xfer, &m_4B4 );
	*xfer == m_4B8;
	*xfer == m_4BC;
	XferObjectID( xfer, &m_4C0 );
	XferObjectID( xfer, &m_4C4 );
	xfer->XferRawBytes( &m_528, 4 );
	*xfer == m_530;
	XferObjectID( xfer, &m_554 );
	*xfer == m_558;
	xfer->XferRawBytes( &m_55C, 4 );
	*xfer == m_534;
	*xfer == m_550;
	*xfer == m_544;
	*xfer == m_52C;
	*xfer == m_538;
	*xfer == m_53C;
	*xfer == m_540;

	if( version.m_minimum >= 2 )
	{
		*xfer == m_560;
		*xfer == m_56C;
		*xfer == m_578;
	}
}
