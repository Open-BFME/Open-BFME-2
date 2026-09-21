// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@FireSpreadUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024CECD, 81 bytes. Dedicated TU: the factory news 0x18, runs the
// rowed nullary ctor (0x48B73C, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x48B758, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x14 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// FireSpreadUpdateModuleData::buildFieldParse proc (OCLEmbers table 0xC4C000
// per BFME1 FireSpreadUpdate donor) pushed as the factory's proc immediate;
// the ctor installs folded vtable 0x00C4ED70 and fits the 0x18 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class FireSpreadUpdateModuleData
{
public:
	FireSpreadUpdateModuleData();
	virtual ~FireSpreadUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@FireSpreadUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FireSpreadUpdateModuleData::friend_newModuleData(INI *ini)
{
	FireSpreadUpdateModuleData *data = new FireSpreadUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FireSpreadUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
