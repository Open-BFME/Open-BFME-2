// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0CommandPointsUpgradeModuleData@@QAE@XZ, retail 0x00254891, 65 bytes.
// EH ctor over the rowed Rva00253487Base base (0x253487; its virtual
// destructor folds into 0x0049B47C and arms the single EH state): base call,
// the compact and-zero of CommandPoints at +0x118, the lea of RequiredObject
// at +0x11C, the compiler's store of retail's 31-slot table 0x00BF2658
// (ModuleData's slots with Rva00253487Base's slot 10 true), then the filter
// construction through the opaque 0x3623E5 pin (EnragedUpdateModuleDataCtor
// precedent: same mangled owner, 4 bytes of storage, declared dtor). Size
// 0x120 matches the rowed ModuleData factory at 0x2548D2 (sole raw caller,
// news 0x120). Class identity is the table 0x00C590E8 (CommandPoints at
// +0x118, RequiredObject at +0x11C) beside the rowed chained proc.

#include "../../../../Include/GameLogic/Module/Rva00253487Base.h"
#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"

class CommandPointsUpgradeModuleData : public Rva00253487Base
{
public:
	CommandPointsUpgradeModuleData();
	virtual ~CommandPointsUpgradeModuleData();

private:
	int m_commandPoints; // +0x118
	Rva003623E5Member m_requiredObject; // +0x11C
};

// ??0CommandPointsUpgradeModuleData@@QAE@XZ @0x254891
CommandPointsUpgradeModuleData::CommandPointsUpgradeModuleData()
	: m_commandPoints(0),
	m_requiredObject()
{
}
