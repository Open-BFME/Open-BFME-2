// cl: /DNDEBUG /MD
//
// ??0InheritUpgradeCreate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B9428, 42 bytes.
// InheritUpgradeCreate behavior ctor over the rowed CreateModule base
// (0x4B8CF7): re-stores the primary vtable slot and the +0x0C/+0x10
// secondary slots (address-of TU-local dummies, DIR32-masked). The rowed
// name getter at 0x4B9471 and ModuleData pair (proc 0x4B94B6 plus factory
// 0x250CC3) prove the class; the rowed instance factory 0x250C8B is the sole
// raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;
class Xfer;
enum NameKeyType;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/CreateModuleClass.h"

// novtable: the compiler stores no vptr of its own, so the three explicit
// stores below stay the body's only ones, in retail order.
class __declspec(novtable) InheritUpgradeCreate : public CreateModule
{
public:
	InheritUpgradeCreate(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void onBuildComplete();
	void rva004B959C();

protected:
	virtual void xfer(Xfer *xfer);
};

// ??0InheritUpgradeCreate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B9428
InheritUpgradeCreate::InheritUpgradeCreate(Thing *thing, const ModuleData *moduleData)
	: CreateModule(thing, moduleData)
{
	*(const void **)this = &s_vtable;
	*(const void **)((char *)this + 0x0C) = &s_secondary0C;
	*(const void **)((char *)this + 0x10) = &s_secondary10;
}
