// cl: /DNDEBUG /MD
//
// ?xfer@GiveUpgradeUpdate@@MAEXPAVXfer@@@Z, retail 0x0049C41C, 85 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00851220 (class of ??0GiveUpgradeUpdate
// rowed at 0x0049C3AC in GiveUpgradeUpdateCtor.cpp).
//
// Evidence: rowed base ?xfer@SpecialAbilityUpdate@@MAEXPAVXfer@@@Z at
// 0x0044F996, IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed
// 0x000053EE, then bool at +0x88 via Xfer slot 0x90, float at +0x8C via Xfer
// slot 0x70, bool at +0x89 via Xfer slot 0x90. Layout is the rowed
// GiveUpgradeUpdate class from GiveUpgradeUpdateCtor.cpp (SpecialAbilityUpdate
// base 0x88 plus bool m_firstFlag at +0x88 plus bool m_secondFlag at +0x89
// plus float m_value at +0x8C). BFME1 donor GiveUpgradeUpdate.cpp has the same
// two-bool plus trailing member shape.

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

#include "../../../../Include/Common/BfmeXfer.h"
#include "../../../Common/GameLogicObjectLookupView.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};
class SpecialPowerTemplate;
struct Coord3D;
class Waypoint;
class Rva0049C5D9;
class GiveUpgradeUpdateModuleData;

class Rva0049C73AHandler
{
public:
	virtual void rva0049C73ASlot0(int what, Object *obj, int a, int b, int c);
};

class SpecialAbilityUpdate
{
	friend class Rva0049C5D9;
public:
	virtual UpdateSleepTime update();
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate, const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions, const Waypoint *way);
	bool rva00450AE9();

protected:
	virtual void onExit(bool a, bool b);
	virtual void xfer(Xfer *xfer);

	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	char m_pad0C[0x20 - 0x0C];
	Rva0049C73AHandler m_20;	// +0x20
	char m_pad24[0x40 - 0x24];
	ObjectID m_40;			// +0x40
	char m_pad44[0x88 - 0x44];
};

class GiveUpgradeUpdate : public SpecialAbilityUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
	void GetDeliveryTarget();
	unsigned char rva0049C8E9();

protected:
	virtual void xfer(Xfer *xfer);
	const GiveUpgradeUpdateModuleData *getGiveUpgradeUpdateModuleData() const
	{
		return (const GiveUpgradeUpdateModuleData *)m_moduleData;
	}

	bool m_firstFlag;		// +0x88
	bool m_89;			// +0x89
	unsigned char m_pad8A[2];
	float m_value;			// +0x8C
};

void GiveUpgradeUpdate::xfer(Xfer *xfer)
{
	SpecialAbilityUpdate::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_firstFlag;
	*xfer == m_value;
	*xfer == m_89;
}
