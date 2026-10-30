// cl: /DNDEBUG /MD
//
// ?xfer@Rva004B4CDF@@MAEXPAVXfer@@@Z, retail 0x004B4F67, 42 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00857C40 (class of rowed dtor
// ??1Rva004B4CDF@@UAE@XZ in FireWeaponWhenDeadBehaviorDerived.cpp):
// Version1 via rowed 0x000053EE then bool at +0x20 via Xfer slot 0x90
// then base UpgradeModule xfer via rowed 0x004CE3F9. Layout is UpgradeModule
// base 0x1C plus pad to +0x20 with bool there (loadPostProcess in the donor
// TU tests byte at +0x20). Identity is slot 3 plus the UpgradeModule base
// call; shape follows GeometryUpgradeXfer/ReplaceSelfUpgradeXfer (Version
// plus base via 0x004CE3F9) with Version1-plus-bool order as retail shows.

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

class Thing;
class Object;
class ModuleData;

class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
	Object *getObject() const { return m_object; }
};

class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};

template <int N> class SubObjectsUpgradeMuxSlots : public SubObjectsUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class SubObjectsUpgradeMuxSlots<0>
{
};

class UpgradeMuxIface : public SubObjectsUpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};

class UpgradeModule : public ObjectModuleBase,
	public UpgradeModuleInterface,
	public UpgradeMuxIface
{
public:
	void rva004CE4A0();
public:
	void rva004CE4A8();
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void xfer(Xfer *xfer);
	virtual ~UpgradeModule(); // retail ??1UpgradeModule@@MAE@XZ, 0x0046089D
};

class Rva004B4CDF : public UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad14[0x1C - 0x14];
	void *m_1C;
	bool m_flag20; // +0x20
};

void Rva004B4CDF::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_flag20;
	UpgradeModule::xfer(xfer);
}
