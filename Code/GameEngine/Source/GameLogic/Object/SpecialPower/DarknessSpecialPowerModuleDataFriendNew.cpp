// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DarknessSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00251FFC, 84 bytes. Dedicated TU: the factory news 0x84, runs the
// declared-only ctor (pinned at 0x4C4F63; DarknessRadius plus DarknessFX
// fields live in the class table at 0x00C5D7BC), then feeds the new data plus
// the class parse proc (pinned at 0x4C4D9E; chained through the rowed
// SpecialPowerModuleData base proc at 0x493207, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x80 pad).
// Recipe: DevastateSpecialPowerModuleDataFriendNew.cpp. Class identity is
// retail's own INI table at 0x00C5D7BC (Darkness led) joined to the
// DarknessSpecialPower pool key at 0x4C4E02.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DarknessSpecialPowerModuleData
{
public:
	DarknessSpecialPowerModuleData();
	virtual ~DarknessSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x84 - 4];
};

// ?friend_newModuleData@DarknessSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DarknessSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	DarknessSpecialPowerModuleData *data = new DarknessSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DarknessSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
