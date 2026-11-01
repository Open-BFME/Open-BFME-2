// cl: /MD
//
// ?xfer@AutoHealBehavior@@MAEXPAVXfer@@@Z, retail 0x00452401, 95 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0083FCDC (class of rowed AutoHealBehavior
// ctor 0x00452592). Version(1,2) via Xfer slot 0x28 then base UpdateModule
// xfer via rowed 0x0044DF9F then UpgradeMux member at +0x20 via rowed
// 0x004CE397 then uint at +0x2C via Xfer slot 0x78 plus bool at +0x30 via
// Xfer slot 0x90 plus version-gated uint at +0x34 via Xfer slot 0x78.
// Layout is UpdateModule base 0x20 plus UpgradeMux member plus neutral
// members (retail diverges from the BFME1 donor which xfers user/uint/bool).
// Recipe is the FireWeaponWhenDamagedBehaviorXfer version-gated slot-3 pattern.

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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class AutoHealBehavior;

class UpgradeMux
{
	friend class AutoHealBehavior;
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

class AutoHealBehavior : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	UpgradeMux m_mux20;
	unsigned int m_28;
	unsigned int m_2C;
	bool m_stopped30;
	unsigned char m_pad31[3];
	unsigned int m_34;
};

void AutoHealBehavior::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	UpdateModule::xfer(xfer);
	m_mux20.UpgradeMux::upgradeMuxXfer(xfer);
	*xfer == m_2C;
	*xfer == m_stopped30;
	if (version.m_minimum >= 2) {
		*xfer == m_34;
	}
}
