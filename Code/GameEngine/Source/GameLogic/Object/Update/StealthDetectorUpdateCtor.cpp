// cl: /GX /DNDEBUG /MD
//
// ??0StealthDetectorUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x004A2CB9, 116 bytes. Behavior-side ctor in the StealthDetectorUpdate
// file-unit (pool key 0x4A2C74 plus ModuleData proc 0x4A2D82 plus ModuleData
// ctor plus both factories all rowed): the rowed UpdateModule base ctor
// (0x253390 thing plus data) runs first, the class's three vftables are
// stored, then the module parks itself awake with setWakeFrame(obj frames)
// through the pin at 0x44DF71 - a GetGameLogicRandomValue (rowed) roll over
// the module data's rate when its flag byte is clear else
// UPDATE_SLEEP_FOREVER. The row supersedes the sole-caller pin at the same
// address.
//
// Target facts (vftables are VAs): the ctor and the destructor 0x004A2BD1
// store 0x00C51FC0 at +0, UpdateModule's 0x00BEFF90 at +0x0C and 0x00C51FB4
// at +0x10; the class is declared over the canonical UpdateModule.h, so the
// compiler stores them.
//  - 0x00C51FC0 (13 slots): deleting dtor 0x004A2D2D, loadPostProcess
//    0x00497805 (`jmp 0x0058B03E`, UpdateModule's own body; inherited here),
//    the name getter 0x004A2BEA (rowed as the non-virtual
//    ?name@StealthDetectorUpdate@@QBEPBDXZ, so slot 2 stays UpdateModule's),
//    xfer 0x004A2C30, getModuleNameKey 0x004A2C74, then UpdateModule's slots.
//  - 0x00C51FB4: update 0x004A2D93; slot 1 0x004A2D67 is a body retail folds
//    with other classes' (rowed under a free-function placeholder), so it
//    stays UpdateModule's; slot 2 UpdateModule's wake slot.

class Thing;
class ModuleData;
class Object;
class Xfer;

enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };

#include "../../../../Include/GameLogic/Module/UpdateModule.h"
// BitFlags<11> by value (the mask AIUpdate.h builds): the update-interface getter below.
#include "../../../../Include/Common/BitFlags11.h"

enum NameKeyType;

// The module data fields the ctor reads: the update rate at +0x08 and the
// initially-disabled flag at +0x10.
struct StealthDetectorUpdateCtorData
{
	int m_pad00;
	int m_pad04;
	int m_updateRate;
	int m_pad0C;
	unsigned char m_initiallyDisabled;
};

static const char s_file[] = "StealthDetectorUpdate";

int __cdecl GetGameLogicRandomValue(int low, int high, char *file, int line);

class StealthDetectorUpdate : public UpdateModule
{
public:
	StealthDetectorUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~StealthDetectorUpdate();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	// Update-interface slot 1 (retail table 0x00C51FB4): Zero Hour's held-only mask
	// (DISABLED_HELD, bit 3), ICF-folded with AIUpdateInterface's at 0x004A2D67.
	virtual DisabledMaskType getDisabledTypesToProcess() const
	{
		return DisabledMaskType(DisabledMaskType::kInit, 3);
	}

protected:
	virtual void xfer(Xfer *xfer);
};

// ??0StealthDetectorUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
StealthDetectorUpdate::StealthDetectorUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const StealthDetectorUpdateCtorData *data = (const StealthDetectorUpdateCtorData *)getModuleData();
	unsigned int wake;
	if (data->m_initiallyDisabled == 0)
		wake = GetGameLogicRandomValue(1, data->m_updateRate, const_cast<char *>(s_file), 79);
	else
		wake = UPDATE_SLEEP_FOREVER;
	setWakeFrame(getObject(), (UpdateSleepTime)wake);
}

// ??1StealthDetectorUpdate@@UAE@XZ @0x004A2BD1: vftable 0x00851FC0 slot 0 is its deleting dtor
// 0x004A2D2D (formerly the placeholder Rva004A2BD1 in Rva0024A797Derived.cpp).
StealthDetectorUpdate::~StealthDetectorUpdate()
{
}
