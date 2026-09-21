// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@TerrainResourceBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024C2A4, 81 bytes. Dedicated TU: the factory news 0x24, runs the
// rowed nullary ctor (0x48202F, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x48208A, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus pad). Recipe:
// SupplyWarehouseCripplingBehaviorModuleDataFriendNew.cpp. Class identity is
// the rowed TerrainResourceBehaviorModuleData::buildFieldParse proc (Income
// table 0xC494F0) pushed as the factory's proc immediate; the ctor installs
// vtable 0x00C49440 and fits the 0x24 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class TerrainResourceBehaviorModuleData
{
public:
	TerrainResourceBehaviorModuleData();
	virtual ~TerrainResourceBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x24 - 4];
};

// ?friend_newModuleData@TerrainResourceBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TerrainResourceBehaviorModuleData::friend_newModuleData(INI *ini)
{
	TerrainResourceBehaviorModuleData *data = new TerrainResourceBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, TerrainResourceBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
