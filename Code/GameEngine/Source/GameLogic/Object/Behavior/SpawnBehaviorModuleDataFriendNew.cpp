// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@SpawnBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025769F, 84 bytes. Dedicated TU: the factory news 0x174, runs
// the declared-only nullary ctor (rowed at 0x2575C2, sole caller is this
// factory), then feeds the new data plus the class parse proc (rowed at
// 0x253542, pushed immediate, no pin) to INI::initFromINIMultiProc (rowed
// at 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve
// via their rows. The TU-local class keeps only size and virtuality (vptr
// plus 0x170 pad). Class identity is the rowed
// SpawnBehaviorModuleData::buildFieldParse proc (fifteen-field Spawn table
// 0xBF0200) pushed as the factory's proc immediate; the ctor installs
// vtable 0x00BF4128 and fits the 0x174 news size (FadeInTime at +0x16C).

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SpawnBehaviorModuleData
{
public:
	SpawnBehaviorModuleData();
	virtual ~SpawnBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x174 - 4];
};

// ?friend_newModuleData@SpawnBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpawnBehaviorModuleData::friend_newModuleData(INI *ini)
{
	SpawnBehaviorModuleData *data = new SpawnBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SpawnBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
