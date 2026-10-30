// cl: /MD
// ?rva004B5E06@Rva004B5E06@@QAEXPAVXfer@@@Z retail 0x004B5E06 64B
// Slot 3 of vtables 0x008581CC 0x008583B0; Version(1 2) via Xfer slot 0x28 gating bool at +0x20 via slot 0x90 then base UpgradeModule xfer.
// Evidence: vtable slot 3 plus Xfer slot order Version 0x28 bool 0x90 from Rva005C45D2 plus rowed UpgradeModule xfer 0x004CE3F9.
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
		unsigned char m_current;
		unsigned char m_minimum;
	};

class Object;
struct SpellRechargeModifierUpgradeModuleData;

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const SpellRechargeModifierUpgradeModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

struct BehaviorModuleInterface { virtual void f0C(); };

class UpgradeMux
{
public:
	virtual bool slot0() = 0;
	virtual void gap1() = 0; virtual void gap2() = 0; virtual void gap3() = 0; virtual void gap4() = 0;
	virtual void gap5() = 0; virtual void gap6() = 0; virtual void gap7() = 0;
	virtual void upgradeRemovalImplementation() = 0;
	virtual void slot9(int a1) = 0;
	virtual void upgradeImplementation() = 0;
};

class UpgradeModule : public BehaviorModule, public BehaviorModuleInterface, public UpgradeMux
{
protected:
	virtual void xfer(Xfer *xfer);
	int m_14;
};

class Rva004B5E06 : public UpgradeModule
{
public:
	void rva004B5E06(Xfer *xfer);
};

void Rva004B5E06::rva004B5E06(Xfer *xfer)
{
	Xfer::Version version;
	version.m_current = 1;
	version.m_minimum = 2;
	*xfer == version;
	if (version.m_minimum >= 2)
		*xfer == *(bool *)((char *)this + 0x20);
	UpgradeModule::xfer(xfer);
}
