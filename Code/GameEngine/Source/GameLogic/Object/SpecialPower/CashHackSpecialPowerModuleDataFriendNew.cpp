// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@CashHackSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00251957, 84 bytes. Dedicated TU: the factory news 0x8C, runs the
// declared-only ctor (pinned at 0x4C2889; vtable 0x00C5C688 plus Upgrades
// vector at +0x7C and MoneyAmount at +0x88), then feeds the new data plus
// the class parse proc (rowed at 0x4C2955, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x88 pad). Recipe:
// DevastateSpecialPowerModuleDataFriendNew.cpp. Class identity is retail's
// own two-entry INI table at 0x00C5C724 (landed buildFieldParse row) joined
// to BFME1's CashHackSpecialPower table (both fields verbatim).
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CashHackSpecialPowerModuleData
{
public:
	CashHackSpecialPowerModuleData();
	virtual ~CashHackSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x8C - 4];
};

// ?friend_newModuleData@CashHackSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CashHackSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	CashHackSpecialPowerModuleData *data = new CashHackSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CashHackSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
