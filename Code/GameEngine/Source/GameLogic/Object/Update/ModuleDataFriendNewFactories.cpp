// cl: /O1 /GX /DNDEBUG /MD
//
// Same-shape siblings of ?friend_newModuleData@W3DLaserDraw (0x00064962,
// 81 bytes; see W3DLaserDrawModuleDataFriendNew.cpp). Each factory news its
// ModuleData subclass (declared-only ctor resolving through that ctor's own
// row), then feeds the new data plus its class parse proc (pushed immediate,
// auto-filled by the gate, no pin) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. Owner classes carry the data-class name that
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

// 0x0024AF5C: news 0x0C, ctor ??0LockWeaponCreateModuleData (rowed 0x254C8E),
// parse proc 0x8598E1.
void LockWeaponCreateModuleDataParse_24AF5C(MultiIniFieldParse &parse);

class LockWeaponCreateModuleData
{
public:
	LockWeaponCreateModuleData();
	virtual ~LockWeaponCreateModuleData();

private:
	unsigned char m_pad[0x0C - 4];
};

class SiegeDockingBehaviorModuleData
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SiegeDockingBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeDockingBehaviorModuleData::friend_newModuleData(INI *ini)
{
	LockWeaponCreateModuleData *data = new LockWeaponCreateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, LockWeaponCreateModuleDataParse_24AF5C);
	return reinterpret_cast<ModuleData *>(data);
}

// 0x0024CF56: news 0x10, ctor ??0Rva0048BC03Base (rowed 0x48BC03),
// parse proc 0x88C0B4.
void Rva0048BC03BaseParse_24CF56(MultiIniFieldParse &parse);

class Rva0048BC03Base
{
public:
	Rva0048BC03Base();
	virtual ~Rva0048BC03Base();

private:
	unsigned char m_pad[0x10 - 4];
};

class FireWeaponUpdateModuleData
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FireWeaponUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FireWeaponUpdateModuleData::friend_newModuleData(INI *ini)
{
	Rva0048BC03Base *data = new Rva0048BC03Base;
	if (ini)
		ini->initFromINIMultiProc(data, Rva0048BC03BaseParse_24CF56);
	return reinterpret_cast<ModuleData *>(data);
}

// 0x0024FC08: news 0x0C, ctor ??0RadarUpdateModuleData (rowed 0x3ECC80),
// parse proc 0x7ECC91.
void RadarUpdateModuleDataParse_24FC08(MultiIniFieldParse &parse);

class RadarUpdateModuleData
{
public:
	RadarUpdateModuleData();
	virtual ~RadarUpdateModuleData();

private:
	unsigned char m_pad[0x0C - 4];
};

class ThreatFinderUpdateModuleData
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ThreatFinderUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ThreatFinderUpdateModuleData::friend_newModuleData(INI *ini)
{
	RadarUpdateModuleData *data = new RadarUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RadarUpdateModuleDataParse_24FC08);
	return reinterpret_cast<ModuleData *>(data);
}

// 0x002524B2 / 0x002526DF / 0x00252768 / 0x0025287D: all news 0x7C with the
// one folded ctor ??0UntamedAllegianceSpecialPowerModuleData (rowed 0x4C72D3);
// parse procs 0x8C7AEB, 0x8C856F, 0x8C8699, 0x8C89CB.
void UntamedAllegianceSpecialPowerParse_2524B2(MultiIniFieldParse &parse);
void ManTheWallsSpecialPowerParse_2526DF(MultiIniFieldParse &parse);
void RepairSpecialPowerParse_252768(MultiIniFieldParse &parse);
void HordeDispatchSpecialPowerParse_25287D(MultiIniFieldParse &parse);

class UntamedAllegianceSpecialPowerModuleData
{
public:
	UntamedAllegianceSpecialPowerModuleData();
	virtual ~UntamedAllegianceSpecialPowerModuleData();
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x7C - 4];
};

class ManTheWallsSpecialPowerModuleData
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

class RepairSpecialPowerModuleData
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

class HordeDispatchSpecialPowerModuleData
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@UntamedAllegianceSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *UntamedAllegianceSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	UntamedAllegianceSpecialPowerModuleData *data = new UntamedAllegianceSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, UntamedAllegianceSpecialPowerParse_2524B2);
	return reinterpret_cast<ModuleData *>(data);
}

// ?friend_newModuleData@ManTheWallsSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ManTheWallsSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	UntamedAllegianceSpecialPowerModuleData *data = new UntamedAllegianceSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ManTheWallsSpecialPowerParse_2526DF);
	return reinterpret_cast<ModuleData *>(data);
}

// ?friend_newModuleData@RepairSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RepairSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	UntamedAllegianceSpecialPowerModuleData *data = new UntamedAllegianceSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RepairSpecialPowerParse_252768);
	return reinterpret_cast<ModuleData *>(data);
}

// ?friend_newModuleData@HordeDispatchSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HordeDispatchSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	UntamedAllegianceSpecialPowerModuleData *data = new UntamedAllegianceSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, HordeDispatchSpecialPowerParse_25287D);
	return reinterpret_cast<ModuleData *>(data);
}

// 0x00252C13: news 0x14, ctor ??0ModelConditionSoundSelectorClientBehaviorModuleData (rowed 0x4CAEE6),
// parse proc 0x8CB0F3.
void ModelConditionSoundSelectorClientBehaviorParse_252C13(MultiIniFieldParse &parse);

class ModelConditionSoundSelectorClientBehaviorModuleData
{
public:
	ModelConditionSoundSelectorClientBehaviorModuleData();
	virtual ~ModelConditionSoundSelectorClientBehaviorModuleData();
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x14 - 4];
};

// ?friend_newModuleData@ModelConditionSoundSelectorClientBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ModelConditionSoundSelectorClientBehaviorModuleData::friend_newModuleData(INI *ini)
{
	ModelConditionSoundSelectorClientBehaviorModuleData *data = new ModelConditionSoundSelectorClientBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ModelConditionSoundSelectorClientBehaviorParse_252C13);
	return reinterpret_cast<ModuleData *>(data);
}
