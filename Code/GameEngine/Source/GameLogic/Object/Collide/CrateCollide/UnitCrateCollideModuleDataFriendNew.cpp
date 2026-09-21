// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@UnitCrateCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00255AB8, 81 bytes. Dedicated TU: the factory news 0x64, runs the
// rowed nullary ctor (0x255A72, 70 bytes over the rowed CrateCollide base
// 0x4BC657 with UnitCount zero plus UnitName string set), then feeds the new
// data plus the class parse proc (rowed chained leaf at 0x2511F3, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x60 pad).
// Recipe: MoneyCrateCollideModuleDataFriendNew.cpp. Class identity is the
// rowed UnitCrateCollideModuleData::buildFieldParse proc (base table plus
// UnitCount/UnitName at 0x00BEFAF4, joined to the ZH UnitCrateCollide.h donor)
// pushed as the factory's proc immediate; the ctor installs vtable 0x00BF39C0
// and fits the 0x64 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class UnitCrateCollideModuleData
{
public:
	UnitCrateCollideModuleData();
	virtual ~UnitCrateCollideModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x64 - 4];
};

// ?friend_newModuleData@UnitCrateCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *UnitCrateCollideModuleData::friend_newModuleData(INI *ini)
{
	UnitCrateCollideModuleData *data = new UnitCrateCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, UnitCrateCollideModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
