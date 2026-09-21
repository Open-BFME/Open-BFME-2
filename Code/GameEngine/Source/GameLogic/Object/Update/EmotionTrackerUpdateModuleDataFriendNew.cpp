// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@EmotionTrackerUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024FAF0, 81 bytes. Dedicated TU: the factory news 0x40, runs the
// pinned nullary ctor (0x4B115A, sole caller, installs vtable 0x00C56530),
// then feeds the new data plus the class parse proc (rowed at 0x4B235D,
// pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5)
// when ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x3C pad).
// Recipe: AISpecialPowerUpdateModuleDataFriendNew.cpp. Class identity is the
// rowed EmotionTrackerUpdateModuleData::buildFieldParse proc (TauntAndPoint
// plus AfraidOf plus Hero/Fear scan distances, linked to the
// EmotionTrackerUpdate behavior by pool-key adjacency at 0x4B1393) pushed as
// the factory's proc immediate; the ctor installs vtable 0x00C56530 and fits
// the 0x40 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class EmotionTrackerUpdateModuleData
{
public:
	EmotionTrackerUpdateModuleData();
	virtual ~EmotionTrackerUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x40 - 4];
};

// ?friend_newModuleData@EmotionTrackerUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *EmotionTrackerUpdateModuleData::friend_newModuleData(INI *ini)
{
	EmotionTrackerUpdateModuleData *data = new EmotionTrackerUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, EmotionTrackerUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
