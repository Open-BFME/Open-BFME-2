// cl: /GX /DNDEBUG /MD
// Split from ModuleDataFriendNewFactories84.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Same-shape siblings of ?friend_newModuleData@FakePathfindPortalBehaviourModuleData
// (0x0024B545, 84 bytes; see UpdateModuleDataFriendNew.cpp). The 84-byte form
// is the same code as the 81-byte factory family (ModuleDataFriendNewFactories.cpp)
// with the new-size over 0x7F so retail pushes it as imm32 (+3 bytes). Each
// factory news its ModuleData subclass (declared-only ctor resolving through
// that ctor's own row), then feeds the new data plus its class parse proc
// (pushed immediate, auto-filled by the gate, no pin) to INI::initFromINIMultiProc
// (rowed at 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve
// via their rows. Owner classes carry the data-class name that
// ModuleFactory::init registers each factory under (each registration pushes
// the module name string, then its instance and data factories).

class ModuleData;
class INI;
class MultiIniFieldParse;

#include "../../../../Include/Common/INI/INI.h"

// 0x00251DCC: news 0x80, ctor ??0DefectorSpecialPowerModuleData (rowed 0x4C2A6A),
// parse proc 0x8C4338.

class DefectorSpecialPowerModuleData
{
public:
	DefectorSpecialPowerModuleData();
	virtual ~DefectorSpecialPowerModuleData();

private:
	unsigned char m_pad[0x80 - 4];
};

#include "../../../../Include/GameLogic/Module/ScavengerSpecialPowerModuleData.h"

// ?friend_newModuleData@ScavengerSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ScavengerSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	DefectorSpecialPowerModuleData *data = new DefectorSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ScavengerSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

// 0x002531B0 / 0x0025327A: both news 0xC8 with the one folded ctor
// ??0EvacuateGarrisonSpecialPowerModuleData (rowed 0x4CDFD9); parse procs
// 0x8CDBE1 and 0x8CDFEB.

