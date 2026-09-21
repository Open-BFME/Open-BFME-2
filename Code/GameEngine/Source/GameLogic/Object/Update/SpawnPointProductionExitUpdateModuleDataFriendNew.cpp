// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@SpawnPointProductionExitUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00256137, 52 bytes. Dedicated TU: the factory news 0xC with an
// inline trivial ctor (explicit m_vtable literal 0x00BF3740 plus the
// and-zero of the SpawnPointBoneName word at +8; the _ReadWriteBarrier
// pins the mov ahead of the and, since both source orders emit and-first
// under /O1), then feeds the new data
// plus the class parse proc (rowed at 0x25436A, pushed immediate, no pin)
// to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new resolves via its row. The TU-local class keeps only size
// and layout (vptr literal plus unused +4 plus one int). Recipe:
// DeletionUpdateModuleDataFriendNew.cpp with the Lifetime
// explicit-m_vtable precedent. Class identity is the rowed
// SpawnPointProductionExitUpdateModuleData::buildFieldParse proc (single
// SpawnPointBoneName field per ZH SpawnPointProductionExitUpdate.h) pushed
// as the factory's proc immediate.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SpawnPointProductionExitUpdateModuleData
{
public:
	SpawnPointProductionExitUpdateModuleData()
	{
		m_vtable = reinterpret_cast<void *>(0x00BF3740);
		_ReadWriteBarrier();
		m_boneName = 0;
	}
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	void *m_vtable;
	int m_unused04;
	int m_boneName;
};

// ?friend_newModuleData@SpawnPointProductionExitUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpawnPointProductionExitUpdateModuleData::friend_newModuleData(INI *ini)
{
	SpawnPointProductionExitUpdateModuleData *data = new SpawnPointProductionExitUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SpawnPointProductionExitUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
