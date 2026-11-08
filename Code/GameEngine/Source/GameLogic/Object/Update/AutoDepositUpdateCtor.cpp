// cl: /DNDEBUG /MD
//
// ??0AutoDepositUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0049A20F,
// 68 bytes. AutoDepositUpdate behavior ctor over the rowed UpdateModule base
// (0x253390, thing plus data): stores the class's three vftables (0x00C504EC
// at +0, UpdateModule's 0x00BEFF90 at +0x0C, 0x00C504E0 at +0x10), clears two
// flags, then sets the deposit frame at +0x20 from the module data's +0x08
// plus TheGameLogic's frame. The class is declared over the canonical
// UpdateModule.h, so the compiler stores the vptrs.
//
// The rowed ModuleData pair (ctor 0x2540ED plus factory 0x254152) and the
// rowed instance factory 0x24E4ED (sole caller, ModuleFactory registration
// literal) prove the class. Row supersedes the ctor pin.
//
// Retail 0x00C504EC (13 slots): deleting dtor 0x0049A253, loadPostProcess
// 0x00497805 (`jmp 0x0058B03E`, UpdateModule's own; inherited here), the name
// getter 0x0049A1C4, xfer 0x004A0CC3 (a body retail folds with
// RadarUpdate::xfer: the same +0x20 uint and +0x24/+0x25 bools),
// getModuleNameKey 0x0049A1CA, then UpdateModule's slots. 0x00C504E0: update
// 0x0049A3AE, then UpdateModule's getDisabledTypesToProcess and wake slots.

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../Common/Thing/thing.h"

extern GameLogic *TheGameLogic;

enum UpdateSleepTime;

#include "../../../Common/Thing/thing.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

// The one module-data field the constructor reads (AutoDepositUpdate.cpp's
// view of the same class).
class AutoDepositUpdateModuleData
{
public:
	char m_unknown00[0x08];
	unsigned int m_depositFrame; // +0x08
};

class AutoDepositUpdate : public UpdateModule
{
public:
	AutoDepositUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AutoDepositUpdate();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_depositOnFrame; // +0x20
	bool m_awardInitialCaptureBonus; // +0x24
	bool m_initialized; // +0x25
};

// Primary slot 1, retail 0x00497805 (`jmp 0x0058B03E`): the UpdateModule base call that
// every module-family override without work of its own shares (ICF).
void AutoDepositUpdate::loadPostProcess()
{
	UpdateModule::loadPostProcess();
}

// ??0AutoDepositUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x49A20F
AutoDepositUpdate::AutoDepositUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const AutoDepositUpdateModuleData *data = (const AutoDepositUpdateModuleData *)getModuleData();
	m_awardInitialCaptureBonus = false;
	m_initialized = false;
	m_depositOnFrame = data->m_depositFrame + TheGameLogic->getFrame();
}

// Slot 3 of 0x00C504EC: 0x004A0CC3, UpdateModule's xfer, then (unless a light
// CRC) version 1 and the three fields; retail folds it with RadarUpdate::xfer.
void AutoDepositUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_depositOnFrame;
	*xfer == m_awardInitialCaptureBonus;
	*xfer == m_initialized;
}
