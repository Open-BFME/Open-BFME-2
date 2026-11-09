// cl: /DNDEBUG /MD
//
// ??0VeterancyCrateCollide@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004BCE32, 42 bytes. VeterancyCrateCollide behavior ctor: calls
// ??0CrateCollide 0x004BC523 (thing plus data), then stores the class's
// three vptrs: 0x00C5A954 at +0 (the behavior vtable, whose slot 4 is the
// pool-key getter 0x004BCE7B and slot 12 executeCrateBehavior 0x004BCFF0),
// the family's shared BehaviorModuleInterface table 0x00C5A040 at +0x0C and
// 0x00C5A600 at +0x10, the three the class's destructor 0x004BCE62 stores
// before it jumps to ??1CrateCollide 0x004BC4FC. The instance factory at
// 0x00251261 is the sole raw caller. The view declares the virtuals
// VeterancyCrateCollide.cpp declares, so the stores name the class's tables.

enum NameKeyType
{
	NK_UNKNOWN = 0
};
class Thing;
class ModuleData;
class Object;
class Xfer;
struct Coord3D;
#include "../../../../../Include/GameLogic/Module/BehaviorModule.h"

// The class views SalvageCrateCollide.cpp compiles for the family.
// The collide interface at +0x10: retail's crate tables there (0x00C5A600
// for VeterancyCrateCollide) have six slots; slot 0 is CrateCollide::onCollide
// 0x004BC56D. Only that slot carries a name yet.
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
	// BehaviorModuleInterface slot 1 (retail VA 0x00C5A040): CollideModule's override,
	// rowed at 0x002533D3 (header-inline in CollideModule.h; SquishCollideCtor.cpp).
	virtual CollideModuleInterface *getCollide();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CrateCollide.h
class CrateCollide : public CollideModule
{
public:
	CrateCollide(Thing *thing, const ModuleData *moduleData);
	// Out of line: retail 0x004BC4FC (Rva004BB68EDerived.cpp).
	virtual ~CrateCollide();
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
protected:
	virtual void xfer(Xfer *xfer);
	virtual bool executeCrateBehavior(Object *other) = 0;
	virtual bool isValidToExecute(const Object *other) const;
private:
	bool m_everExecuted;			// +0x14, right after the three module bases
};

// Target facts: VeterancyCrateCollide's primary table 0x00C5A954 has slot 4
// getModuleNameKey 0x004BCE7B, slot 12 executeCrateBehavior 0x004BCFF0 and
// slot 13 isValidToExecute 0x004BCEF0.
class VeterancyCrateCollide : public CrateCollide
{
public:
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual bool executeCrateBehavior(Object *other);
	virtual bool isValidToExecute(const Object *other) const;
public:
	VeterancyCrateCollide(Thing *thing, const ModuleData *moduleData);
	virtual ~VeterancyCrateCollide();
};

// ??0VeterancyCrateCollide@@QAE@PAVThing@@PBVModuleData@@@Z
VeterancyCrateCollide::VeterancyCrateCollide(Thing *thing, const ModuleData *moduleData)
	: CrateCollide(thing, moduleData)
{
}
