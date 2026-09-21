// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@FreezingRainSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00251F70, 84 bytes. Dedicated TU: the factory news 0x88, runs the
// declared-only ctor (pinned at 0x4C4D71; FreezingRainRadius plus
// FreezingRainFX plus BurnRateModifier fields live in the class table at
// 0x00C5D6C0), then feeds the new data plus the class parse proc (pinned at
// 0x4C4B86; chained through the rowed SpecialPowerModuleData base proc at
// 0x493207, pushed immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5)
// when ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x84 pad).
// Recipe: DevastateSpecialPowerModuleDataFriendNew.cpp. Class identity is
// retail's own INI table at 0x00C5D6C0 (FreezingRain led) joined to the
// FreezingRainSpecialPower pool key at 0x4C4BEA.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class FreezingRainSpecialPowerModuleData
{
public:
	FreezingRainSpecialPowerModuleData();
	virtual ~FreezingRainSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x88 - 4];
};

// ?friend_newModuleData@FreezingRainSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FreezingRainSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	FreezingRainSpecialPowerModuleData *data = new FreezingRainSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FreezingRainSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
