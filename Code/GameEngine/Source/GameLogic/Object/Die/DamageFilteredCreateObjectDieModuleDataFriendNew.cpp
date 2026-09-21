// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DamageFilteredCreateObjectDieModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024C9D3, 81 bytes. Dedicated TU: the factory news 0x48, runs the
// rowed nullary ctor (0x485F42, frameless over the pinned SEH base), then
// feeds the new data plus the class parse proc (rowed at 0x485F65, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when
// ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x44 pad).
// Recipe: RebuildHoleExposeDieModuleDataFriendNew.cpp. Class identity is
// the rowed pool key (0x485EFD) ending where the ctor begins, plus the
// rowed DamageFilteredCreateObjectDieModuleData::buildFieldParse proc
// (CreationList at +0x38 plus damage-trigger fields) pushed as the
// factory's proc immediate.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DamageFilteredCreateObjectDieModuleData
{
public:
	DamageFilteredCreateObjectDieModuleData();
	virtual ~DamageFilteredCreateObjectDieModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x48 - 4];
};

// ?friend_newModuleData@DamageFilteredCreateObjectDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DamageFilteredCreateObjectDieModuleData::friend_newModuleData(INI *ini)
{
	DamageFilteredCreateObjectDieModuleData *data = new DamageFilteredCreateObjectDieModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DamageFilteredCreateObjectDieModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
