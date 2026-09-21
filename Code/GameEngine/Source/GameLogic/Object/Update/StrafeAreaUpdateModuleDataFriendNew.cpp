// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@StrafeAreaUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024D737, 81 bytes. Dedicated TU: the factory news 0x20, runs the
// rowed nullary ctor (0x3A4E5A, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x3A4D12, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x1C pad). Recipe:
// SlowDeathBehaviorModuleDataFriendNew.cpp. Class identity is the rowed
// StrafeAreaUpdateModuleData::buildFieldParse proc (Strafe table 0xC1B1F8)
// pushed as the factory's proc immediate; the ctor fits the 0x20 news size;
// the rowed poolkey 0x3A4CCD (StrafeAreaUpdate) ends where the proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class StrafeAreaUpdateModuleData
{
public:
	StrafeAreaUpdateModuleData();
	virtual ~StrafeAreaUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x20 - 4];
};

// ?friend_newModuleData@StrafeAreaUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StrafeAreaUpdateModuleData::friend_newModuleData(INI *ini)
{
	StrafeAreaUpdateModuleData *data = new StrafeAreaUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, StrafeAreaUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
