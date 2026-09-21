// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "LockWeaponCreate" (addModule
// pairs the name with this factory); formerly misnamed SlotToLockUpdateModuleData.
//
// ?friend_newModuleData@LockWeaponCreateModuleData@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x002509CE, 81 bytes. Dedicated TU: the factory news 0xC, runs the
// pinned nullary ctor (0x254C8E, 12-byte inline installing the folded vtable
// 0x00C4ED70 plus zero at +8), then feeds the new data plus the class parse
// proc (rowed at 0x4B8C9C, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 8 pad). Recipe:
// AISpecialPowerUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// LockWeaponCreateModuleData::buildFieldParse proc (table 0x00C59338 whose
// first field is SlotToLock) pushed as the factory's proc immediate; the ctor
// installs vtable 0x00C4ED70 and fits the 0xC news size. The pinned ctor body
// is ICF-folded across three same-size factories (0x24AF5C plus 0x24B3B4 plus
// this one, each pushing its own proc); the pin names this use, the other two
// stay parked until their procs are identified.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class LockWeaponCreateModuleData
{
public:
	LockWeaponCreateModuleData();
	virtual ~LockWeaponCreateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xC - 4];
};

// ?friend_newModuleData@LockWeaponCreateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *LockWeaponCreateModuleData::friend_newModuleData(INI *ini)
{
	LockWeaponCreateModuleData *data = new LockWeaponCreateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, LockWeaponCreateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
