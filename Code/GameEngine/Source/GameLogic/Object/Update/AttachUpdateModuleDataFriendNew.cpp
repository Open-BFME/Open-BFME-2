// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AttachUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024D8D2, 81 bytes. Dedicated TU: the factory news 0x40, runs the
// pinned nullary ctor (0x491968, sole raw caller is this factory; 150B EH
// ctor open), then feeds the new data plus the rowed parse proc (0x491957,
// pushed immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x3C pad).
// Recipe: PickupStuffUpdateModuleDataFriendNew.cpp. Class identity is the
// rowed AttachUpdateModuleData::buildFieldParse proc pushed as the
// factory's proc immediate; the ctor fits the 0x40 news size; the rowed
// poolkey 0x491912 (AttachUpdate) ends where the proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AttachUpdateModuleData
{
public:
	AttachUpdateModuleData();
	virtual ~AttachUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x40 - 4];
};

// ?friend_newModuleData@AttachUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AttachUpdateModuleData::friend_newModuleData(INI *ini)
{
	AttachUpdateModuleData *data = new AttachUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AttachUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
