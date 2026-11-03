// cl: /MD
//
// ?xfer@ObjectCreationUpgrade@@MAEXPAVXfer@@@Z @0x004B421D (62B).
// Slot 3 (offset 0x0C) of vtable 0x0085762C (class of ??1ObjectCreationUpgrade
// rowed at 0x004B3F90 in ObjectCreationUpgradeDtor.cpp).
//
// ObjectCreationUpgrade xfer: Version1 via rowed 0x53EE, then bool at +0x2C
// via Xfer slot 0x90, then uint at +0x28 via Xfer slot 0x78, then base
// UpdateModule xfer via rowed 0x44DF9F, then UpgradeMux base at +0 via rowed
// upgradeMuxXfer 0x4CE397 (this-8). No IsLightCRC early-out. Layout is the
// rowed ctor class (UpgradeMux base 8 plus UpdateModule base 0x20 plus uint
// at +0x28 plus bool at +0x2C) from ObjectCreationUpgradeCtor.cpp. Donor is ZH
// ObjectCreationUpgrade.cpp:117 version-plus-base; BFME2 adds the two members
// and the UpgradeMux split. Recipe is the slot-3 xfer pattern.

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

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

enum NameKeyType
{
	NK_UNKNOWN = 0
};
class ObjectCreationUpgrade : public UpgradeMux, public UpdateModule
{
public:
	void rva004B463C();
	static NameKeyType rva004B3FF5();
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned int m_status28; // +0x28
	bool m_flag2C; // +0x2C
	char m_pad2D[0x3];
};

void ObjectCreationUpgrade::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_flag2C;
	*xfer == m_status28;
	UpdateModule::xfer(xfer);
	UpgradeMux::upgradeMuxXfer(xfer);
}
