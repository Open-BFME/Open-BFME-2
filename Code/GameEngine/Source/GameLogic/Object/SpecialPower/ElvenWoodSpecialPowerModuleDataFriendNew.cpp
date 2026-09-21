// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ElvenWoodSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00251CB4, 84 bytes. Dedicated TU: the factory news 0x9C, runs
// the pinned ctor (0x4C3DA9, frameless body over the SpecialPower base with
// the vector member plus the Elven fields), then feeds the new data plus the
// class parse proc (rowed base-call link at 0x4C3FC2, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x98 pad). Recipe:
// CashHackSpecialPowerModuleDataFriendNew.cpp. Class identity is the rowed
// ElvenWoodSpecialPowerModuleData::buildFieldParse proc (SpecialPower base
// proc plus table 0x0085D018 holding ElvenGroveObject at +0x88 plus
// ElvenNumObjects at +0x8C plus ElvenWoodRadius at +0x90 plus ElvenWoodFX at
// +0x94 plus ElvenWoodOCL at +0x98) pushed as the factory's proc immediate;
// the ElvenWoodSpecialPower pool key at 0x4C3943 sits in the same cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ElvenWoodSpecialPowerModuleData
{
public:
	ElvenWoodSpecialPowerModuleData();
	virtual ~ElvenWoodSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x9C - 4];
};

// ?friend_newModuleData@ElvenWoodSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ElvenWoodSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	ElvenWoodSpecialPowerModuleData *data = new ElvenWoodSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ElvenWoodSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
