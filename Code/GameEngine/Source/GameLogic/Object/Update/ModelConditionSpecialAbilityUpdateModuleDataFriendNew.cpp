// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ModelConditionSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024D849, 81 bytes. Dedicated TU: the factory news 0x6C, runs the
// rowed nullary ctor (0x4915FD, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x4915B5, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x68 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// ModelConditionSpecialAbilityUpdateModuleData::buildFieldParse proc
// (ModelConditionFlags@8/ModelConditionCommandSet@54/WeaponSetFlags@58/
// WeaponToggleCommandSet@68 table 0xC4DA00) pushed as the factory's proc
// immediate; the ctor installs vtable 0x00C4DA50 and fits the 0x6C news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ModelConditionSpecialAbilityUpdateModuleData
{
public:
	ModelConditionSpecialAbilityUpdateModuleData();
	virtual ~ModelConditionSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x6C - 4];
};

// ?friend_newModuleData@ModelConditionSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ModelConditionSpecialAbilityUpdateModuleData::friend_newModuleData(INI *ini)
{
	ModelConditionSpecialAbilityUpdateModuleData *data = new ModelConditionSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ModelConditionSpecialAbilityUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
