// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@HordeGarrisonContainModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024BAD1, 81 bytes. Dedicated TU: the factory news 0xD4, runs the
// rowed nullary ctor (0x47A251, sole caller is this factory), then feeds the
// new data plus the rowed parse proc (0x47A025, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus pad). Recipe:
// GarrisonContainModuleDataFriendNew.cpp. Class identity is the rowed
// HordeGarrisonContainModuleData::buildFieldParse proc (ExitDelay table
// 0xC46388 chained on the pinned GarrisonContain base proc) pushed as the
// factory's proc immediate; the ctor installs vtable 0x00BF4328 and fits
// the 0xD4 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class HordeGarrisonContainModuleData
{
public:
	HordeGarrisonContainModuleData();
	virtual ~HordeGarrisonContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD4 - 4];
};

// ?friend_newModuleData@HordeGarrisonContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HordeGarrisonContainModuleData::friend_newModuleData(INI *ini)
{
	HordeGarrisonContainModuleData *data = new HordeGarrisonContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, HordeGarrisonContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
