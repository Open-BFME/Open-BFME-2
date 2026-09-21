// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@RadarUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00254291, 81 bytes. Dedicated TU: the factory news 0xC, runs the
// pinned nullary ctor (0x3ECC80, a shared fold with the DefaultRadius
// factory 0x24FC08 whose proc 0x3ECC91 holds the DefaultRadius table; the
// pin documents the share), then feeds the new data plus the class parse
// proc (rowed at 0x254280, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 8 pad). Recipe:
// SlotToLockUpgradeModuleDataFriendNew.cpp (shared-fold ctor pin play).
// Class identity is the rowed RadarUpdateModuleData::buildFieldParse proc
// (single RadarExtendTime field at +8, matching the 0xC news size) pushed
// as the factory's proc immediate.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RadarUpdateModuleData
{
public:
	RadarUpdateModuleData();
	virtual ~RadarUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x0C - 4];
};

// ?friend_newModuleData@RadarUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RadarUpdateModuleData::friend_newModuleData(INI *ini)
{
	RadarUpdateModuleData *data = new RadarUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RadarUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
