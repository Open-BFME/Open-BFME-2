// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@InheritUpgradeCreateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00250CC3, 84 bytes. Dedicated TU: the factory news 0x90, runs the
// pinned ctor (0x4B9508, EH body installing vtable 0x00C59768 plus float zero
// at +8 plus member init at +0xC plus filter at +0x8C), then feeds the new
// data plus the class parse proc (rowed at 0x4B94B6, pushed immediate, no
// pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x8C pad). Recipe:
// ExperienceLevelCreateModuleDataFriendNew.cpp. Class identity is the rowed
// InheritUpgradeCreateModuleData::buildFieldParse proc (table 0x00C59728
// holds Radius at +8 plus Upgrade at +0xC plus ObjectFilter at +0x8C,
// matching the ctor stores) pushed as the factory's proc immediate; the
// InheritUpgradeCreate pool key (rowed at 0x4B949B) ends where the proc
// begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class InheritUpgradeCreateModuleData
{
public:
	InheritUpgradeCreateModuleData();
	virtual ~InheritUpgradeCreateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x90 - 4];
};

// ?friend_newModuleData@InheritUpgradeCreateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *InheritUpgradeCreateModuleData::friend_newModuleData(INI *ini)
{
	InheritUpgradeCreateModuleData *data = new InheritUpgradeCreateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, InheritUpgradeCreateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
