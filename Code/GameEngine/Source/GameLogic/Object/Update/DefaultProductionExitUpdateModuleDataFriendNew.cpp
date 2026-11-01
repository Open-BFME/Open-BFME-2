// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DefaultProductionExitUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002543C7, 81 bytes. Dedicated TU: the factory news 0x20 with an
// inline trivial ctor (explicit m_vtable literal plus zeroed unit create
// point and natural rally point), then feeds the new data plus the class
// parse proc (rowed at 0x253CCC, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new resolves via its row. The TU-local class keeps only size and
// layout (vptr literal plus base field plus two Coord3D). Recipe:
// DeletionUpdateModuleDataFriendNew.cpp with float stores for the points.
// Class identity is retail's own INI table at 0x00BF2398 (UnitCreatePoint
// plus NaturalRallyPoint per ZH DefaultProductionExitUpdate.h; the
// SupplyCenter twin is already rowed elsewhere) beside the rowed
// DefaultProductionExitUpdate bodies (setRallyPoint plus getRallyPoint plus
// pool key).

extern "C" const void *const __identifier("??_7ObjectHelperModuleData@@6B@")[];  // folded nine-class vftable 0x00C4ED70, by its data-ledger name

class ModuleData;
class INI;
class MultiIniFieldParse;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../Include/Common/INI/INI.h"

class DefaultProductionExitUpdateModuleData
{
public:
	__forceinline DefaultProductionExitUpdateModuleData()
	{
		m_vtable = reinterpret_cast<void *>(((unsigned int)__identifier("??_7ObjectHelperModuleData@@6B@")));
		m_unitCreatePoint.x = 0.0f;
		m_unitCreatePoint.y = 0.0f;
		m_unitCreatePoint.z = 0.0f;
		m_naturalRallyPoint.x = 0.0f;
		m_naturalRallyPoint.y = 0.0f;
		m_naturalRallyPoint.z = 0.0f;
	}
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	void *m_vtable;
	int m_baseField;
	Coord3D m_unitCreatePoint;
	Coord3D m_naturalRallyPoint;
};

// ?friend_newModuleData@DefaultProductionExitUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DefaultProductionExitUpdateModuleData::friend_newModuleData(INI *ini)
{
	DefaultProductionExitUpdateModuleData *data = new DefaultProductionExitUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DefaultProductionExitUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
