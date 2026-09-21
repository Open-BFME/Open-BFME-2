// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@HeightDieUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024D3B6, 81 bytes. Dedicated TU: the factory news 0x1C, runs the
// rowed nullary ctor (0x48FC75, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x48FCA1, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus pad). Recipe:
// HordeGarrisonContainModuleDataFriendNew.cpp. Class identity is the rowed
// HeightDieUpdateModuleData::buildFieldParse proc (Height table 0xC4CFC8)
// pushed as the factory's proc immediate; the ctor installs folded vtable
// 0x00C4ED70 and fits the 0x1C news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class HeightDieUpdateModuleData
{
public:
	HeightDieUpdateModuleData();
	virtual ~HeightDieUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C - 4];
};

// ?friend_newModuleData@HeightDieUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HeightDieUpdateModuleData::friend_newModuleData(INI *ini)
{
	HeightDieUpdateModuleData *data = new HeightDieUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, HeightDieUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
