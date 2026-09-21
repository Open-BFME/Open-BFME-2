// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@InvisibilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025553A, 81 bytes. Dedicated TU: the factory news 0x1DC, runs
// the pinned ModuleData ctor (0x00255474, sole caller), then feeds the new
// data plus the class parse proc (rowed at 0x004A381C, pushed immediate, no
// pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus pad). Recipe:
// DemoTrapUpdateModuleDataFriendNew.cpp. Class identity is retail's own
// nine-entry INI table at 0x00C52468 (landed buildFieldParse row) with the
// InvisibilityUpdate behavior pool key at 0x004A393C same cluster.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class InvisibilityUpdateModuleData
{
public:
	InvisibilityUpdateModuleData();
	virtual ~InvisibilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1DC - 4];
};

// ?friend_newModuleData@InvisibilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *InvisibilityUpdateModuleData::friend_newModuleData(INI *ini)
{
	InvisibilityUpdateModuleData *data = new InvisibilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, InvisibilityUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
