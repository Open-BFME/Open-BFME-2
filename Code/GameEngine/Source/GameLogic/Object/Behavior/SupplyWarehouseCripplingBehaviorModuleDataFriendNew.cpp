// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@SupplyWarehouseCripplingBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024C4BC, 81 bytes. Dedicated TU: the factory news 0x14, runs the
// rowed nullary ctor (0x483A61, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x483A7A, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x10 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// SupplyWarehouseCripplingBehaviorModuleData::buildFieldParse proc (SelfHeal
// table 0xC49B40) pushed as the factory's proc immediate; the ctor installs
// folded vtable 0x00C4ED70 and fits the 0x14 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SupplyWarehouseCripplingBehaviorModuleData
{
public:
	SupplyWarehouseCripplingBehaviorModuleData();
	virtual ~SupplyWarehouseCripplingBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x14 - 4];
};

// ?friend_newModuleData@SupplyWarehouseCripplingBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SupplyWarehouseCripplingBehaviorModuleData::friend_newModuleData(INI *ini)
{
	SupplyWarehouseCripplingBehaviorModuleData *data = new SupplyWarehouseCripplingBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SupplyWarehouseCripplingBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
