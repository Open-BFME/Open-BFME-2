// cl: /O1 /GX /DNDEBUG /MD

// ?friend_newModuleData@PlayerHealSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002525C7, 84 bytes. Dedicated TU: the factory news 0xAC, runs the
// declared-only ctor (pinned at 0x4C803A; vtable 0x00C5E7A8 plus HealAmount,
// HealAsPercent, HealRadius, HealAffects, HealFX and HealOCL fields over the
// pinned 0x7C-byte Rva004930A0 base), then feeds the new data plus the class
// parse proc (rowed at 0x4C7E63, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0xA8 pad).
// Recipe: DevastateSpecialPowerModuleDataFriendNew.cpp. Class identity is
// retail's own six-entry INI table at 0x00C5E298 joined to the rowed
// PlayerHealSpecialPower pool key and the BFME1 PlayerHealSpecialPower files.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class PlayerHealSpecialPowerModuleData
{
public:
	PlayerHealSpecialPowerModuleData();
	virtual ~PlayerHealSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xAC - 4];
};

// ?friend_newModuleData@PlayerHealSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PlayerHealSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	PlayerHealSpecialPowerModuleData *data = new PlayerHealSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, PlayerHealSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
