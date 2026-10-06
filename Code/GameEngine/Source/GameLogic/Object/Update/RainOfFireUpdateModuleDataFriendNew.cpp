// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@RainOfFireUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024F3EB, 81 bytes. Dedicated TU: the factory news 0x30, runs the
// pinned ctor (0x4AC03D, 89-byte frameless SSE body with float/int stores),
// then feeds the new data plus the class parse proc (rowed at 0x4AC097,
// pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5)
// when ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x2C pad).
// Recipe: AIGateUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// RainOfFireUpdateModuleData::buildFieldParse proc (table 0x00C54B00 holds
// StartRainTime at +8 through RainOffset at +0x28, matching the ctor stores)
// pushed as the factory's proc immediate; the RainOfFireUpdate pool key at
// 0x4AC172 sits in the same retail cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RainOfFireUpdateModuleData
{
public:
	RainOfFireUpdateModuleData();
	virtual ~RainOfFireUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x30 - 4];
};

// ?friend_newModuleData@RainOfFireUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RainOfFireUpdateModuleData::friend_newModuleData(INI *ini)
{
	RainOfFireUpdateModuleData *data = new RainOfFireUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RainOfFireUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
