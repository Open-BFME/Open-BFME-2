// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@CrateCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002510DF, 81 bytes. Dedicated TU: the factory news 0x5C, runs the
// pinned ctor (0x4BC657, EH body installing vtable 0x00C5A660 plus 0x24C7B3
// member clears at +8/+0x24), then feeds the new data plus the class parse
// proc (rowed at 0x4BC7FE in the twin Collide TU, pushed immediate, no pin)
// to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x58 pad). Recipe:
// SlotToLockUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// CrateCollideModuleData::buildFieldParse proc (RequiredKindOf plus
// ForbiddenKindOf plus BuildingPickup plus HumanOnly table) pushed as the
// factory's proc immediate; the pinned ctor is shared as a base by four
// derived ctors, documented on the pin.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CrateCollideModuleData
{
public:
	CrateCollideModuleData();
	virtual ~CrateCollideModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x5C - 4];
};

// ?friend_newModuleData@CrateCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CrateCollideModuleData::friend_newModuleData(INI *ini)
{
	CrateCollideModuleData *data = new CrateCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CrateCollideModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
