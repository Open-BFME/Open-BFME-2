// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@RadiateFearUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E6E8, 84 bytes. Dedicated TU: the factory news 0x130, runs
// the pinned ctor (0x49C06C, EH body), then feeds the new data plus the class
// parse proc (pinned chained link at 0x49C0E4, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x12C pad). Recipe:
// MissileUpdateModuleDataFriendNew.cpp. Class identity is the pinned
// RadiateFearUpdateModuleData::buildFieldParse proc (base proc plus table
// 0x00C510B8 holding InitiallyActive plus WhichSpecialPower plus
// GenerateTerror plus GenerateFear plus EmotionPulseRadius plus
// EmotionPulseInterval plus VictimFilter) pushed as the factory's proc
// immediate; the RadiateFearUpdate pool key at 0x49C007 sits in the same
// retail cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RadiateFearUpdateModuleData
{
public:
	RadiateFearUpdateModuleData();
	virtual ~RadiateFearUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x130 - 4];
};

// ?friend_newModuleData@RadiateFearUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RadiateFearUpdateModuleData::friend_newModuleData(INI *ini)
{
	RadiateFearUpdateModuleData *data = new RadiateFearUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RadiateFearUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
