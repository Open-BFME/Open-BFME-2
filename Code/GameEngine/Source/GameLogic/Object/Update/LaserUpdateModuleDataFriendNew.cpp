// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@LaserUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024D55A, 81 bytes. Dedicated TU: the factory news 0x1C, runs the
// rowed nullary ctor (0x363147, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x363166, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x18 pad). Recipe:
// SlowDeathBehaviorModuleDataFriendNew.cpp. Class identity is the rowed
// LaserUpdateModuleData::buildFieldParse proc (Laser table 0xC17208) pushed
// as the factory's proc immediate; the ctor fits the 0x1C news size; the
// rowed poolkey 0x363102 (LaserUpdate) ends where the ctor begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class LaserUpdateModuleData
{
public:
	LaserUpdateModuleData();
	virtual ~LaserUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C - 4];
};

// ?friend_newModuleData@LaserUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *LaserUpdateModuleData::friend_newModuleData(INI *ini)
{
	LaserUpdateModuleData *data = new LaserUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, LaserUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
