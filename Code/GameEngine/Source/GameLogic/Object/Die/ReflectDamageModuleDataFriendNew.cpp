// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ReflectDamageModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00250DC2, 81 bytes. Dedicated TU: the factory news 0x14, runs the
// rowed nullary ctor (0x4BAB9A, frameless stores), then feeds the new data
// plus the class parse proc (rowed at 0x4BAB25, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x10 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// ReflectDamageModuleData::buildFieldParse proc (DamageTypesToReflect plus
// ReflectDamagePercentage plus MinimumDamageToReflect per the BFME1
// ReflectDamage donor) pushed as the factory's proc immediate; the ctor
// installs vtable 0x00C4ED70 and fits the 0x14 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ReflectDamageModuleData
{
public:
	ReflectDamageModuleData();
	virtual ~ReflectDamageModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x14 - 4];
};

// ?friend_newModuleData@ReflectDamageModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ReflectDamageModuleData::friend_newModuleData(INI *ini)
{
	ReflectDamageModuleData *data = new ReflectDamageModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ReflectDamageModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
