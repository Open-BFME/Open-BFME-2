// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@HijackerUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025616B, 56 bytes. Dedicated TU: the factory news 0x10 with an
// inline trivial ctor (explicit m_vtable literal 0x00BF36C0 plus the
// and-zeros of the AttachToTargetBone word at +8 and the ParachuteName
// word at +0xC; the _ReadWriteBarrier pins the mov ahead of the ands,
// since source order alone emits and-first under /O1 per the SpawnPoint
// 0x256137 precedent), then feeds the new data plus the class parse proc
// (rowed at 0x25437B, pushed immediate, no pin) to INI::initFromINIMultiProc
// (rowed at 0x2DEB5) when ini is non-null. Operator new resolves via its
// row. The TU-local class keeps only size and layout (vptr literal plus
// unused +4 plus two ints). Recipe:
// SpawnPointProductionExitUpdateModuleDataFriendNew.cpp. Class identity is
// the rowed HijackerUpdateModuleData::buildFieldParse proc (AttachToTarget
// Bone at +8 plus ParachuteName at +0xC per ZH HijackerUpdate.h) pushed as
// the factory's proc immediate.

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

class HijackerUpdateModuleData
{
public:
	HijackerUpdateModuleData()
	{
		m_vtable = reinterpret_cast<void *>(0x00BF36C0);
		_ReadWriteBarrier();
		m_attachBoneName = 0;
		m_parachuteName = 0;
	}
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	void *m_vtable;
	int m_unused04;
	int m_attachBoneName;
	int m_parachuteName;
};

// ?friend_newModuleData@HijackerUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HijackerUpdateModuleData::friend_newModuleData(INI *ini)
{
	HijackerUpdateModuleData *data = new HijackerUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, HijackerUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
