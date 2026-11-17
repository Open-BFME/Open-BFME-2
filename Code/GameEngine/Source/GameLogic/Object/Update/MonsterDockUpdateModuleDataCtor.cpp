// cl: /GX /MD /DNDEBUG
// Native constructor 004A1517 (59 bytes) calls DockUpdateModuleData at 005896B0,
// constructs its filter at +10 and clears the time at +14. The factory at
// 0024EB2C allocates 18 hexadecimal bytes. The base supplies the native
// 31-slot ModuleData interface and occupies the first 10 hexadecimal bytes.
// Its complete seven-byte teardown folds with Snapshot at 0049B47C and is
// also the existing destructor provider used by SupplyCenterDockUpdate.
#include "../../../../Include/Common/ModuleData.h"
// Native Dock teardown folds with Snapshot's complete seven-byte destructor.
// Keep this existing provider visible to its constructor's EH cleanup.
inline ModuleData::~ModuleData() {}
#include "../../../../Include/GameLogic/Module/DockUpdateModuleData.h"

#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"

class MonsterDockUpdateModuleData : public DockUpdateModuleData
{
public:
	MonsterDockUpdateModuleData();
	virtual ~MonsterDockUpdateModuleData();

	Rva003623E5Member m_filter;
	int m_dockedAnimationTime;
};

MonsterDockUpdateModuleData::MonsterDockUpdateModuleData()
	: DockUpdateModuleData()
{
	m_dockedAnimationTime = 0;
}
