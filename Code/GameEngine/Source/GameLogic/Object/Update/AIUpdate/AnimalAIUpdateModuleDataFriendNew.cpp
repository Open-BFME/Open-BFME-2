// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AnimalAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024BED0, 84 bytes. Dedicated TU: the factory news 0x80, runs the
// rowed nullary ctor (0x24BE43, sole raw caller is this factory; frameless
// body over Transport base 0x26E5D7 with triple-10 defaults plus sunk vtable
// 0xC4B6C8 plus FleeRange/FleeDistance/WanderPercentage), then feeds the new
// data plus the class parse proc (rowed at 0x24BE7A, pushed immediate, base
// proc plus table 0x00BEEB88) to INI::initFromINIMultiProc (rowed at 0x2DEB5)
// when ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x7C pad).
// Recipe: WanderAIUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// AnimalAIUpdate pool key plus the registrar pairing behavior AnimalAIUpdate
// with this factory.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AnimalAIUpdateModuleData
{
public:
	AnimalAIUpdateModuleData();
	virtual ~AnimalAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x80 - 4];
};

// ?friend_newModuleData@AnimalAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AnimalAIUpdateModuleData::friend_newModuleData(INI *ini)
{
	AnimalAIUpdateModuleData *data = new AnimalAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AnimalAIUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
