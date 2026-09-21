// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@TooltipUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002558E9, 84 bytes. Dedicated TU: the factory news 0x120, runs
// the rowed EH ctor (0x25588E, over the OpenContain base with the
// compiler-emitted vtable and the DisplayName plus Description string
// assignments), then feeds the new data plus the rowed class parse proc
// (0x4B7A2E, pushed immediate) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. Recipe: GeometryUpgradeModuleDataFriendNew.cpp. Class
// identity is the rowed TooltipUpgrade proc (Upgrade base proc 0x4CE29D
// plus table 0x00858C38 holding DisplayName at +0x118 plus Description at
// +0x11C matching the ctor members) pushed as the factory's proc
// immediate; the TooltipUpgrade pool key tail at 0x4B7A13 ends where that
// proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class TooltipUpgradeModuleData
{
public:
	TooltipUpgradeModuleData();
	virtual ~TooltipUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x120 - 4];
};

// ?friend_newModuleData@TooltipUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TooltipUpgradeModuleData::friend_newModuleData(INI *ini)
{
	TooltipUpgradeModuleData *data = new TooltipUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, TooltipUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
