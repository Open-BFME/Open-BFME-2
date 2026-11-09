// cl: /DNDEBUG /MD
//
// ??0HeightDieUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0048FCB2, 77 bytes.
// HeightDieUpdate behavior ctor over the rowed UpdateModule base (0x253390):
// sets +0x30 to -1, stores the class's three vftables (0x00C4CF18 at +0,
// UpdateModule's 0x00BEFF90 at +0x0C, 0x00C4CF0C at +0x10), zeroes the bytes
// at +0x20/+0x21, then stores -1.0f into +0x24/+0x28/+0x2C (the -1.0f literal
// pool-merges to retail 0xBBB9AC). The class is declared over the canonical
// UpdateModule.h, so the compiler stores the vptrs. The rowed name getter at
// 0x48FC30 proves the class; the rowed instance factory 0x24D37E is the sole
// raw caller. Row supersedes the ctor pin.
//
// Retail 0x00C4CF18 (13 slots): deleting dtor 0x0048FCFF, loadPostProcess
// 0x00497805 (`jmp 0x0058B03E`, UpdateModule's own; inherited here), the name
// getter 0x0048FBD3, xfer 0x0048FBD9, getModuleNameKey 0x0048FC30, then
// UpdateModule's slots. 0x00C4CF0C: update 0x0048FD1B, then UpdateModule's
// getDisabledTypesToProcess and wake slots.

enum UpdateSleepTime;

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class HeightDieUpdate : public UpdateModule
{
public:
	HeightDieUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~HeightDieUpdate();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);

private:
	bool m_20;
	bool m_21;
	float m_24;
	float m_28;
	float m_2C;
	int m_30;
};

// Primary slot 1, retail 0x00497805 (`jmp 0x0058B03E`): the UpdateModule base call that
// every module-family override without work of its own shares (ICF).
void HeightDieUpdate::loadPostProcess()
{
	UpdateModule::loadPostProcess();
}

// ??0HeightDieUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x48FCB2
HeightDieUpdate::HeightDieUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_30 = -1;
	m_20 = false;
	m_21 = false;
	m_24 = -1.0f;
	m_28 = -1.0f;
	m_2C = -1.0f;
}
