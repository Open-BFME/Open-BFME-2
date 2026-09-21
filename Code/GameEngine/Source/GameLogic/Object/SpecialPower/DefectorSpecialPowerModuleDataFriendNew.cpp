// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DefectorSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002519E3, 81 bytes. Dedicated TU: the factory news 0x80, runs
// the pinned ctor (0x4C2A6A, trivial 26B body over the SpecialPower base
// with the FatCursorRadius float-zero at +0x7C; shared with the Bounty
// factory 0x251DCC which news the same size for its BountyPercent table,
// SlotToLock shared-fold precedent), then feeds the new data plus the class
// parse proc (rowed base-call link at 0x4C2970, pushed immediate, SpecialPower
// base proc plus table 0x00C5C764 holding FatCursorRadius at +0x7C, the sole
// field matching BFME1's DefectorSpecialPowerModuleData table) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x7C pad). Recipe:
// ElvenWoodSpecialPowerModuleDataFriendNew.cpp. Class identity is the rowed
// DefectorSpecialPowerModuleData::buildFieldParse proc pushed as the
// factory's proc immediate (unique image-wide); the DefectorSpecialPower
// pool key at 0x4C29D3 sits in the same cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DefectorSpecialPowerModuleData
{
public:
	DefectorSpecialPowerModuleData();
	virtual ~DefectorSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x80 - 4];
};

// ?friend_newModuleData@DefectorSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DefectorSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	DefectorSpecialPowerModuleData *data = new DefectorSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DefectorSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
