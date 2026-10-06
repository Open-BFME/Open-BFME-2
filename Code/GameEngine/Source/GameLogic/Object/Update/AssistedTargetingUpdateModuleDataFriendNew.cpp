// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AssistedTargetingUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00253C23, 68 bytes. Dedicated TU: the factory news 0x18 with an
// inline trivial ctor (assisting clip size 1 plus zeroed weapon slot and laser
// name pointers plus explicit m_vtable literal), then feeds the new data plus
// the class parse proc (rowed at 0x486E7C, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new resolves via its row. The TU-local class keeps only size and layout
// (vptr literal plus base pad plus two ints plus two pointers). Recipe:
// DeletionUpdateModuleDataFriendNew.cpp with the Deletion explicit-m_vtable
// precedent. Class identity is retail's own INI table at 0x00C4AFE8
// (AssistingClipSize plus AssistingWeaponSlot plus LaserFromAssisted plus
// LaserToTarget per ZH AssistedTargetingUpdate.h) beside the rowed
// AssistedTargetingUpdate bodies (pool key plus name plus isFreeToAssist).

extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AssistedTargetingUpdateModuleData
{
public:
	AssistedTargetingUpdateModuleData()
	{
		m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00C4ED70));
		m_assistingClipSize = 1;
		m_assistingWeaponSlot = 0;
		m_laserFromAssisted = 0;
		m_laserToTarget = 0;
	}
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	void *m_vtable;
	int m_basePad;
	int m_assistingClipSize;
	int m_assistingWeaponSlot;
	const char *m_laserFromAssisted;
	const char *m_laserToTarget;
};

// ?friend_newModuleData@AssistedTargetingUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AssistedTargetingUpdateModuleData::friend_newModuleData(INI *ini)
{
	AssistedTargetingUpdateModuleData *data = new AssistedTargetingUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AssistedTargetingUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
