// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@CloudBreakSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00251E58, 84 bytes. Dedicated TU: the factory news 0x8C, runs the
// declared-only ctor (pinned at 0x4C479A; CloudBreakRadius plus CloudBreakFX
// plus SunbeamObject fields live in the class table at 0x00C54F28), then feeds
// the new data plus the class parse proc (pinned at 0x4C44BD; chained through
// the rowed SpecialPowerModuleData base proc at 0x493207, pushed immediate)
// to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x88 pad).
// Recipe: DevastateSpecialPowerModuleDataFriendNew.cpp. Class identity is
// retail's own ten-entry INI table at 0x00C54F28 (BonusRadius led) joined to
// the CloudBreakSpecialPower pool key at 0x4C4521.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CloudBreakSpecialPowerModuleData
{
public:
	CloudBreakSpecialPowerModuleData();
	virtual ~CloudBreakSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x8C - 4];
};

// ?friend_newModuleData@CloudBreakSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CloudBreakSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	CloudBreakSpecialPowerModuleData *data = new CloudBreakSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CloudBreakSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
