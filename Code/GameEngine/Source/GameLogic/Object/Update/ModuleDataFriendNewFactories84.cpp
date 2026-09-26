// cl: /O1 /GX /DNDEBUG /MD
//
// Same-shape siblings of ?friend_newModuleData@FakePathfindPortalBehaviourModuleData
// (0x0024B545, 84 bytes; see UpdateModuleDataFriendNew.cpp). The 84-byte form
// is the same code as the 81-byte factory family (ModuleDataFriendNewFactories.cpp)
// with the new-size over 0x7F so retail pushes it as imm32 (+3 bytes). Each
// factory news its ModuleData subclass (declared-only ctor resolving through
// that ctor's own row), then feeds the new data plus its class parse proc
// (pushed immediate, auto-filled by the gate, no pin) to INI::initFromINIMultiProc
// (rowed at 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve
// via their rows. Owner classes carry the data-class name that
// ModuleFactory::init registers each factory under (each registration pushes
// the module name string, then its instance and data factories).

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

// 0x00251DCC: news 0x80, ctor ??0DefectorSpecialPowerModuleData (rowed 0x4C2A6A),
// parse proc 0x8C4338.
void DefectorSpecialPowerModuleDataParse_251DCC(MultiIniFieldParse &parse);

class DefectorSpecialPowerModuleData
{
public:
	DefectorSpecialPowerModuleData();
	virtual ~DefectorSpecialPowerModuleData();

private:
	unsigned char m_pad[0x80 - 4];
};

class ScavengerSpecialPowerModuleData
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ScavengerSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ScavengerSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	DefectorSpecialPowerModuleData *data = new DefectorSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DefectorSpecialPowerModuleDataParse_251DCC);
	return reinterpret_cast<ModuleData *>(data);
}

// 0x002531B0 / 0x0025327A: both news 0xC8 with the one folded ctor
// ??0EvacuateGarrisonSpecialPowerModuleData (rowed 0x4CDFD9); parse procs
// 0x8CDBE1 and 0x8CDFEB.
void EvacuateGarrisonSpecialPowerParse_2531B0(MultiIniFieldParse &parse);
void UnleashSpecialPowerParse_25327A(MultiIniFieldParse &parse);

class EvacuateGarrisonSpecialPowerModuleData
{
public:
	EvacuateGarrisonSpecialPowerModuleData();
	virtual ~EvacuateGarrisonSpecialPowerModuleData();
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xC8 - 4];
};

class UnleashSpecialPowerModuleData
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@EvacuateGarrisonSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *EvacuateGarrisonSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	EvacuateGarrisonSpecialPowerModuleData *data = new EvacuateGarrisonSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, EvacuateGarrisonSpecialPowerParse_2531B0);
	return reinterpret_cast<ModuleData *>(data);
}

// ?friend_newModuleData@UnleashSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *UnleashSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	EvacuateGarrisonSpecialPowerModuleData *data = new EvacuateGarrisonSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, UnleashSpecialPowerParse_25327A);
	return reinterpret_cast<ModuleData *>(data);
}
