// cl: /DNDEBUG /MD
//
// ??0AutoFindHealingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00495139, 46 bytes.
// AutoFindHealingUpdate behavior ctor over the rowed UpdateModule base
// (0x253390): zeroes +0x20, then stores the class's three vftables
// (0x00C4EC10 at +0, UpdateModule's 0x00BEFF90 at +0x0C, 0x00C4EC04 at
// +0x10). The class is declared over the canonical UpdateModule.h, so the
// compiler stores the vptrs. The rowed pool key at 0x4950B4 and ModuleData
// triple (proc 0x495128 plus ctor 0x4950F9 plus factory 0x24DEFE) prove the
// class; the rowed instance factory 0x24DEC6 is the sole caller. Row
// supersedes the ctor pin.
//
// Retail 0x00C4EC10 (13 slots): deleting dtor 0x00495167, loadPostProcess
// 0x00497805 (`jmp 0x0058B03E`, UpdateModule's own; inherited here), the name
// getter 0x00495087, xfer 0x0049508D, getModuleNameKey 0x004950B4, then
// UpdateModule's slots. 0x00C4EC04: update 0x0049520B, then UpdateModule's
// getDisabledTypesToProcess and wake slots.

enum UpdateSleepTime;

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class AutoFindHealingUpdate : public UpdateModule
{
public:
	AutoFindHealingUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AutoFindHealingUpdate();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);

private:
	int m_20;
};

// ??0AutoFindHealingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x495139
AutoFindHealingUpdate::AutoFindHealingUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_20 = 0;
}
