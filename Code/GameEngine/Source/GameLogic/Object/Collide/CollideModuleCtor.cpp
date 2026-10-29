// cl: /DNDEBUG /MD /GX
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
// +0/+0xC/+0x10 (retail 0x00C5A130, 0x00C5A040, 0x00C5A00C; the primary's
// slot 2 is CollideModule's snapshot-name getter Rva004BB733Get). The class
// views are FireWeaponCollide.cpp's, so this body merges into it.

class Thing;

class ModuleData;

class Object;

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface
{
public:
	virtual void *behaviorSlot() { return 0; }
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~BehaviorModule();				// census COMDAT ??1BehaviorModule@@MAE@XZ
	virtual void loadPostProcess();				// slot 1
	virtual const char *GetSnapshotName() const;		// slot 2
};

class CollideModuleInterface
{
public:
	virtual void *collideSlot() { return 0; }
};

class CollideModule : public BehaviorModule, public CollideModuleInterface
{
public:
	CollideModule(Thing *thing, const ModuleData *moduleData);
	virtual ~CollideModule();
};

// ??0CollideModule@@QAE@PAVThing@@PBVModuleData@@@Z @0x004BB702
CollideModule::CollideModule(Thing *thing, const ModuleData *moduleData) :
	BehaviorModule(thing, moduleData)
{
}
