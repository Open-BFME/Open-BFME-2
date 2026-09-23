// cl: /O1 /DNDEBUG /MD
//
// ??0CollideModule@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004BB702,
// 49 bytes. CollideModule intermediate base ctor: five raw callers are
// Collide-family behavior ctors (Squish 0x4BB9CF plus HordeMember 0x4BC389
// plus three), so this is the shared base, not a leaf.
//
// Donor: BFME1 CollideModule.h (CollideModule : BehaviorModule,
// CollideModuleInterface with an inline ctor). BFME2 outlines it: the rowed
// BehaviorModule ctor runs first, the inline CollideModuleInterface ctor
// stores its vtable at +0x10, then the derived installs its three vtables at
// +0/+0xC/+0x10. Zero new pins (all callees rowed; vtable immediates are
// DIR32-masked). Row supersedes the pin at the same address.

class Thing;
class ModuleData;
class Object;
class Coord3D;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class CollideModuleInterface
{
public:
	CollideModuleInterface() {}
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
	virtual bool wouldLikeToCollideWith(const Object *other) const = 0;
	virtual bool isHijackedVehicleCrateCollide() const = 0;
	virtual bool isSabotageBuildingCrateCollide() const = 0;
	virtual bool isCarBombCrateCollide() const = 0;
	virtual bool isRailroad() const = 0;
	virtual bool isSalvageCrateCollide() const = 0;
};

class CollideModule : public BehaviorModule, public CollideModuleInterface
{
public:
	CollideModule(Thing *thing, const ModuleData *moduleData);
	virtual ~CollideModule();
	virtual CollideModuleInterface *getCollide();
};

// ??0CollideModule@@QAE@PAVThing@@PBVModuleData@@@Z @0x004BB702
CollideModule::CollideModule(Thing *thing, const ModuleData *moduleData) :
	BehaviorModule(thing, moduleData)
{
}
