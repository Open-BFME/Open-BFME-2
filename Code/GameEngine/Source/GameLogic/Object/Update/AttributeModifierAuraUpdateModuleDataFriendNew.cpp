// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AttributeModifierAuraUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E65C, 84 bytes. Dedicated TU: the factory news 0x154, runs
// the pinned ctor (0x49BBD5, EH body over vector plus filter plus member
// setup with vtable 0xC50EE8), then feeds the new data plus the class parse
// proc (rowed double-add link at 0x49BBB3, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x150 pad). Recipe:
// ReplaceSelfUpgradeModuleDataFriendNew.cpp. Class identity is the rowed
// AttributeModifierAuraUpdateModuleData::buildFieldParse proc (getter table
// plus table 0x00C50DC8 holding BonusName at +0x8 plus RefreshDelay at +0x18
// plus Range at +0x1C plus TargetEnemy at +0x21 plus AllowPowerWhenAttacking
// at +0x20 plus ObjectFilter at +0x24 plus StartsActive at +0x138) pushed as
// the factory's proc immediate; the AttributeModifierAuraUpdate pool key at
// 0x49B5DC sits in the same retail cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AttributeModifierAuraUpdateModuleData
{
public:
	AttributeModifierAuraUpdateModuleData();
	virtual ~AttributeModifierAuraUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x154 - 4];
};

// ?friend_newModuleData@AttributeModifierAuraUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AttributeModifierAuraUpdateModuleData::friend_newModuleData(INI *ini)
{
	AttributeModifierAuraUpdateModuleData *data = new AttributeModifierAuraUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AttributeModifierAuraUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
