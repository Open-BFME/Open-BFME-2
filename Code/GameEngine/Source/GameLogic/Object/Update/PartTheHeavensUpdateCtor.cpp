// cl: /DNDEBUG /MD
//
// ??0PartTheHeavensUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004AC998,
// 70 bytes. PartTheHeavensUpdate behavior ctor over the rowed UpdateModule
// base (0x253390, thing plus data): zero +0x24 (and-RMW), store the class's
// tables (retail 0x00C54DA4 at +0, 0x00BEFF90 at +0x0C, 0x00C54D98 at +0x10,
// the three PartTheHeavensUpdate.cpp emits and its destructor installs),
// default +0x20 to 0x3FFFFFFF, then overwrite it from TheGameLogic+0x40
// unless the module data pointer at +4 is null. The class is declared over
// the canonical UpdateModule.h, so the compiler stores the tables.
//
// The rowed name getter at 0x4AC93C (PartTheHeavensUpdate literal), the pool
// key at 0x4AC942 and the ModuleData pair (proc 0x4AC987 plus factory
// 0x24F4FD) prove the class; the rowed instance factory 0x24F4C5 is the sole
// raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum UpdateSleepTime;
enum NameKeyType;

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class PartTheHeavensUpdatePointee;

class PartTheHeavensUpdate : public UpdateModule
{
public:
	PartTheHeavensUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~PartTheHeavensUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;

private:
	unsigned int m_startFrame;	// +0x20
	PartTheHeavensUpdatePointee *m_pointee;	// +0x24
};

// ??0PartTheHeavensUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4AC998
PartTheHeavensUpdate::PartTheHeavensUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_pointee = 0;
	m_startFrame = 0x3FFFFFFF;
	if (m_moduleData != 0)
		m_startFrame = TheGameLogic->getFrame();
}
