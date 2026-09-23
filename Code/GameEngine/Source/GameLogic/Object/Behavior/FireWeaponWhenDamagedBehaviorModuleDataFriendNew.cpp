// cl: /O1 /GX- /DNDEBUG /MD
//
// ?friend_newModuleData@FireWeaponWhenDamagedBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00253703, 52 bytes. Dedicated TU: the factory news 0x144, runs
// the rowed ctor (0x253682, frameless over the shared construct block with
// the folded vtable and DamageTypes or-minus-one plus DamageAmount
// float-zero), then feeds the new data plus the rowed class parse proc
// (0x2536E1, pushed immediate) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new resolves via its row.
// Recipe: RadarUpgradeModuleDataFriendNew.cpp. Class identity is the rowed
// FireWeaponWhenDamaged proc (own table 0x00BF0400 holding StartsActive
// plus Reaction and Continuous weapons plus DamageTypes and DamageAmount
// matching the ctor stores) pushed as the factory's proc immediate; the
// FireWeaponWhenDamagedBehavior pool key at 0x4827AA names the family.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class FireWeaponWhenDamagedBehaviorModuleData
{
public:
	FireWeaponWhenDamagedBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x144];
};

// ?friend_newModuleData@FireWeaponWhenDamagedBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FireWeaponWhenDamagedBehaviorModuleData::friend_newModuleData(INI *ini)
{
	FireWeaponWhenDamagedBehaviorModuleData *data = new FireWeaponWhenDamagedBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FireWeaponWhenDamagedBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
