// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@FloatUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024D0F1, 81 bytes. Dedicated TU: the factory news 0xC, runs the
// rowed nullary ctor (0x48D7A6, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x48D7B3, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 8 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// FloatUpdateModuleData::buildFieldParse proc (Enabled table 0xC4C7A4)
// pushed as the factory's proc immediate; the ctor installs the folded
// vtable 0x00C4ED70 and fits the 0xC news size; the rowed poolkey 0x48D761
// (FloatUpdate) ends where the ctor begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class FloatUpdateModuleData
{
public:
	FloatUpdateModuleData();
	virtual ~FloatUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xC - 4];
};

// ?friend_newModuleData@FloatUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FloatUpdateModuleData::friend_newModuleData(INI *ini)
{
	FloatUpdateModuleData *data = new FloatUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FloatUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
