// cl: /MD /GX /Ireference/shims/bfme2_ascii
//
// ??0SalvageCrateCollide@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004BD1D7, 42 bytes: calls the CrateCollide constructor (rowed at
// 0x004BC523, thing plus data), then stores SalvageCrateCollide's three
// tables in base order: the primary 0x00C5A9C0 at +0x00, the collide
// family's BehaviorModuleInterface table 0x00C5A040 at +0x0C and its own
// CollideModuleInterface table 0x00C5A9A8 at +0x10. The class adds no
// members, so the body is empty. The class views are the ones
// SalvageCrateCollide.cpp declares.

enum NameKeyType
{
	NK_UNKNOWN = 0
};
class Object;
class Xfer;
class Thing;
class ModuleData;
struct Coord3D;
struct SalvageCrateCollideModuleData;
struct BfmeWideResult;

#include "../../../../../Include/GameLogic/Module/BehaviorModule.h"

// The collide interface at +0x10. Retail's SalvageCrateCollide table there
// (0x00C5A9A8) has six slots; slot 0 is CrateCollide::onCollide 0x004BC56D.
// Only that slot carries a name yet.
class CollideModuleInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h
class CollideModule : public BehaviorModule, public CollideModuleInterface
{
public:
	CollideModule(Thing *thing, const ModuleData *moduleData);
	virtual ~CollideModule();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CrateCollide.h
// Target facts: SalvageCrateCollide's primary table 0x00C5A9C0 is
// ObjectModule's ten slots and BehaviorModule's two, then slot 12
// executeCrateBehavior 0x004BD442 and slot 13 isValidToExecute 0x004BD314;
// CrateCollide's own table 0x00C5A618 holds __purecall in slot 12.
class CrateCollide : public CollideModule
{
public:
	CrateCollide(Thing *thing, const ModuleData *moduleData);
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
protected:
	virtual void xfer(Xfer *xfer);
	virtual bool executeCrateBehavior(Object *other) = 0;
	virtual bool isValidToExecute(const Object *other) const;
private:
	bool m_everExecuted;			// +0x14, right after the three module bases
};

class SalvageCrateCollide : public CrateCollide
{
public:
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual void xfer(Xfer *xfer);
protected:
	virtual bool executeCrateBehavior(Object *other);
protected:
	virtual bool isValidToExecute(const Object *other) const;
private:
	const SalvageCrateCollideModuleData *getSalvageCrateCollideModuleData() const
	{
		return (const SalvageCrateCollideModuleData *)m_moduleData;
	}
private:
	int rva004BD281();
private:
	void rva004BD2D0(BfmeWideResult *hits);
private:
	void doMoney(Object *other);
public:
	SalvageCrateCollide(Thing *thing, const ModuleData *moduleData);
};

// ??0SalvageCrateCollide@@QAE@PAVThing@@PBVModuleData@@@Z
SalvageCrateCollide::SalvageCrateCollide(Thing *thing, const ModuleData *moduleData)
	: CrateCollide(thing, moduleData)
{
}
