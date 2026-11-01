// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?xfer@Rva003FD789@@MAEXPAVXfer@@@Z, retail 0x003FD6BD, 35 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00837D78 (class of ??0Rva003FD789
// rowed at 0x003FD716 in Rva003FD789Ctor.cpp). Persists AsciiString at
// +0x1C via Xfer slot 0x6C and Coord at +0x20 via Xfer slot 0x60. No base
// call (EmptyBase has no xfer) and no IsLightCRC/Version in retail.
// Layout is the rowed Rva003FD789 class from Rva003FD789Ctor.cpp (EmptyBase
// plus m_04/m_08/m_0C/m_10/m_11/m_14/m_18 plus m_1C plus Coord at +0x20).
// Caller at 0x00212208.

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
class Thing;
class ModuleData;
class Object;
class DamageInfo;

#include "../../../Include/Common/BfmeXfer.h"

#include "ascii_string.h"

#include "../../../../Libraries/Include/Lib/Coord3DBase.h"


class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class Rva003FD789 : public EmptyBase
{
public:
	virtual ~Rva003FD789();
protected:
	virtual void xfer(Xfer *xfer);
private:
	int volatile m_04;
	float volatile m_08;
	StringBase<char> m_0c;
	bool m_10;
	bool m_11;
	float m_14;
	short m_18;
	AsciiString m_1c;
	Coord3DBase m_20;
};

void Rva003FD789::xfer(Xfer *xfer)
{
	*xfer == m_1c;
	*xfer == m_20;
}

// The empty EH-state base that about fifteen constructor views declare has no retail
// body; this transfer unit never destroys one, so it holds the one out-of-line copy.
// ?<??1EmptyBase@@QAE@XZ> absent-from-retail
EmptyBase::~EmptyBase()
{
}
