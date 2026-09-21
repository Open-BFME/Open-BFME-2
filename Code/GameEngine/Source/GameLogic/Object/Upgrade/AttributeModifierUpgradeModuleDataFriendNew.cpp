// cl: /O1 /GX- /DNDEBUG /MD
//
// ?friend_newModuleData@AttributeModifierUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00255802, 52 bytes. Dedicated TU: the factory news 0x11C, runs
// the rowed ctor (0x2557E9, frameless over the OpenContain base with the
// folded vtable and AttributeModifier zero), then feeds the new data plus
// the rowed class parse proc (0x4B671E, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new resolves via its pin. Recipe:
// RadarUpgradeModuleDataFriendNew.cpp. Class identity is the rowed
// AttributeModifierUpgrade proc (Upgrade base proc 0x4CE29D plus table
// 0x00858818 holding AttributeModifier at +0x118 matching the ctor store)
// pushed as the factory's proc immediate; the AttributeModifierUpgrade pool
// key at 0x4B6703 ends where that proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AttributeModifierUpgradeModuleData
{
public:
	AttributeModifierUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x11C];
};

// ?friend_newModuleData@AttributeModifierUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AttributeModifierUpgradeModuleData::friend_newModuleData(INI *ini)
{
	AttributeModifierUpgradeModuleData *data = new AttributeModifierUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AttributeModifierUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
