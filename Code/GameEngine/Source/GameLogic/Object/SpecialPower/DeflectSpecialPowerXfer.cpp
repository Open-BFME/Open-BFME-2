// cl: /DNDEBUG /MD
//
// ?xfer@DeflectSpecialPower@@MAEXPAVXfer@@@Z, retail 0x004C5571, 65 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0085DA7C (class of rowed ctor
// ??0DeflectSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z in
// DeflectSpecialPowerConstructorThunk.cpp). Base Rva00589079 xfer via rowed
// 0x00589215 then IsLightCRC early-out via Xfer slot 0x10 then Version1 via
// rowed 0x000053EE then bytes at +0x3C/+0x3D via Xfer slot 0x90. Layout is
// Rva00589079 base 0x38 plus pad to +0x3C plus two bytes (cf. rowed ctor
// zeroes m_byte3C/m_byte3D). Donor pattern is SiegeDeployHordeSpecialPowerXfer
// (IsLightCRC plus Version plus gated tail).

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase
{
	float x;
	float y;
	float z;
};
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

// Shared DeflectSpecialPower unit view: one declaration of each class for
// every body retail built into this unit. The ctor 0x004C545D installs
// vtables at +0x00, +0x0C, +0x10, +0x20, +0x24 and +0x38: ObjectModule and
// BehaviorModuleInterface (canonical BehaviorModule), UpdateModuleInterface,
// the base's two extra interfaces and the collide interface.

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class Coord3D;
class Xfer;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_updateState; // +0x1C
};

class Rva00589079_E1
{
public:
	virtual void fe() = 0;
};

class Rva00589079_E2
{
public:
	virtual void fe() = 0;
};

class Rva00589079 : public UpdateModule, public Rva00589079_E1, public Rva00589079_E2
{
public:
	virtual ~Rva00589079(); // 0x00589079

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_28;
	int m_2C;
	unsigned int m_30;
	float m_34;
};

// DeflectSpecialPower's direct base: its ctor calls 0x0058959A
// (WeaponModeSpecialPowerUpdateBase's rowed ctor) and its xfer calls
// 0x00589215 (rowed as Rva00589079::xfer). Both placeholder names stay on
// their rows; this view chains them so each call keeps its symbol.
class WeaponModeSpecialPowerUpdateBase : public Rva00589079
{
public:
	WeaponModeSpecialPowerUpdateBase(Thing *thing, const ModuleData *moduleData);
};

class CollideModuleInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};

class DeflectSpecialPower : public WeaponModeSpecialPowerUpdateBase, public CollideModuleInterface
{
public:
	DeflectSpecialPower(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);

protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_active; // +0x3C
	bool m_pending; // +0x3D
};

void DeflectSpecialPower::xfer(Xfer *xfer)
{
	Rva00589079::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_active;
	*xfer == m_pending;
}
