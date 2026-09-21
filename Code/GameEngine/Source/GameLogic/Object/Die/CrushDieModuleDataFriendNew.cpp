// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@CrushDieModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00253A27, 81 bytes. Dedicated TU: the factory news 0x58, runs the
// pinned nullary ctor (0x2539B3, sole raw caller is this factory; big-EH
// AudioEventRTS-member ctor per the BFME1 CrushDie donor, unrowed), then
// feeds the new data plus the class parse proc (rowed at 0x253A05, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when
// ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x54 pad).
// Recipe: UpgradeDieModuleDataFriendNew.cpp. Class identity is the rowed
// CrushDieModuleData::buildFieldParse proc (crush-sound fields per the
// BFME1 CrushDie donor, field_names vote 6/6) pushed as the factory's proc
// immediate.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CrushDieModuleData
{
public:
	CrushDieModuleData();
	virtual ~CrushDieModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x58 - 4];
};

// ?friend_newModuleData@CrushDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CrushDieModuleData::friend_newModuleData(INI *ini)
{
	CrushDieModuleData *data = new CrushDieModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CrushDieModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
