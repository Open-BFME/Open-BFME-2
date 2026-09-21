// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@TransportAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024BDF2, 81 bytes. Dedicated TU: the factory news 0x64, runs the
// pinned ctor (0x26E5D7, EH body installing vtable 0x00BFA288), then feeds
// the new data plus the class parse proc (rowed single-table leaf at
// 0x2638FF, pushed immediate, Turret-led table 0x00BF9378) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x60 pad). Recipe:
// SpecialEnemySenseUpdateModuleDataFriendNew.cpp. Class identity is the
// retail registrar at 0x25A14C pairing behavior TransportAIUpdate with this
// factory (plus behavior factory 0x24F192); WanderAIUpdateModuleData derives
// from this class.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x64 - 4];
};

// ?friend_newModuleData@TransportAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TransportAIUpdateModuleData::friend_newModuleData(INI *ini)
{
	TransportAIUpdateModuleData *data = new TransportAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, TransportAIUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
