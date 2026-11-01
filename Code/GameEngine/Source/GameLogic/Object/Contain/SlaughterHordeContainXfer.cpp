// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?xfer@SlaughterHordeContain@@MAEXPAVXfer@@@Z, retail 0x0048029A, 88 bytes.
// Slot 3 of ??_7SlaughterHordeContain 0x00C48AA0 (slot 0 the rowed ??_G
// 0x00480645, slot 4 the rowed pool-name key 0x004803B6). Light-CRC
// early-out, Version(1,2) through Xfer slot 0x28, then from version 2 the
// two members the ctor 0x0048034E clears: an unsigned int at +0x9E4 (Xfer
// slot 0x78) and an AsciiString at +0x9E8 (slot 0x6C; 0x004804DD tests it
// with isEmpty and releases it), and finally the pinned
// HordeGarrisonContain::xfer 0x00479D28. Member names are not recovered.

#include "ascii_string.h"

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
class Thing;
class ModuleData;
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

class HordeGarrisonContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x9E4 - 0x04];
};

class SlaughterHordeContain : public HordeGarrisonContain
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_9E4;
	AsciiString m_9E8;
};

// ?xfer@SlaughterHordeContain@@MAEXPAVXfer@@@Z @0x0048029A
void SlaughterHordeContain::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;
	if (version.m_minimum >= 2)
	{
		*xfer == m_9E4;
		*xfer == m_9E8;
	}

	HordeGarrisonContain::xfer(xfer);
}
