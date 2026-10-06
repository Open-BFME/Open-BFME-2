// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DestroyEnvironmentUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024F474, 81 bytes. Dedicated TU: the factory news 0x10, runs the
// pinned nullary ctor (0x4AC615, 20-byte inline installing vtable 0x00C4ED70
// plus zero at +8 plus 100 at +0xC), then feeds the new data plus the class
// parse proc (rowed at 0x4AC629, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0xC pad). Recipe:
// SlotToLockUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// DestroyEnvironmentUpdateModuleData::buildFieldParse proc (table 0x00C54D28
// holds StartTime at +8 plus DestructionTime at +0xC, matching the ctor
// stores) pushed as the factory's proc immediate; the DestroyEnvironmentUpdate
// pool key (rowed at 0x4AC686) plus the Update ctor (0x4AC63A) sit in the same
// retail cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DestroyEnvironmentUpdateModuleData
{
public:
	DestroyEnvironmentUpdateModuleData();
	virtual ~DestroyEnvironmentUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x10 - 4];
};

// ?friend_newModuleData@DestroyEnvironmentUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DestroyEnvironmentUpdateModuleData::friend_newModuleData(INI *ini)
{
	DestroyEnvironmentUpdateModuleData *data = new DestroyEnvironmentUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DestroyEnvironmentUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
