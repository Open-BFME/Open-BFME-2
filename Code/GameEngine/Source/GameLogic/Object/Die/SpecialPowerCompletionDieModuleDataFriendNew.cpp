// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@SpecialPowerCompletionDieModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00253B05, 81 bytes. Dedicated TU: the factory news 0x3C, runs the
// pinned nullary ctor (0x4C230E, sole raw caller is this factory; int
// zero-init per the BFME1 SpecialPowerCompletionDie donor, unrowed), then
// feeds the new data plus the class parse proc (rowed at 0x254AFC, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when
// ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x38 pad).
// Recipe: CrushDieModuleDataFriendNew.cpp. Class identity is the rowed
// SpecialPowerCompletionDieModuleData::buildFieldParse proc (single
// SpecialPowerTemplate field at +0x38 per the BFME1 donor) pushed as the
// factory's proc immediate, beside the rowed SpecialPowerCompletionDie
// pool key and behavior rows.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SpecialPowerCompletionDieModuleData
{
public:
	SpecialPowerCompletionDieModuleData();
	virtual ~SpecialPowerCompletionDieModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x3C - 4];
};

// ?friend_newModuleData@SpecialPowerCompletionDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SpecialPowerCompletionDieModuleData::friend_newModuleData(INI *ini)
{
	SpecialPowerCompletionDieModuleData *data = new SpecialPowerCompletionDieModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SpecialPowerCompletionDieModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
