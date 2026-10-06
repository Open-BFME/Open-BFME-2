// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ReplaceObjectUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024FCEA, 84 bytes. Dedicated TU: the factory news 0xE0, runs the
// pinned ctor (0x4B2AC4, frameless body over the opaque intermediate base),
// then feeds the new data plus the class parse proc (pinned chained link at
// 0x24FC94, pushed immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5)
// when ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0xDC pad).
// Recipe: RadiateFearUpdateModuleDataFriendNew.cpp. Class identity is the
// pinned ReplaceObjectUpdateModuleData::buildFieldParse proc (base proc plus
// table 0x00BEF960 holding ReplaceObject plus ReplaceRadius plus ReplaceFX
// plus Scatter) pushed as the factory's proc immediate; the
// ReplaceObjectUpdate pool key at 0x4B2A29 sits in the same retail cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ReplaceObjectUpdateModuleData
{
public:
	ReplaceObjectUpdateModuleData();
	virtual ~ReplaceObjectUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xE0 - 4];
};

// ?friend_newModuleData@ReplaceObjectUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ReplaceObjectUpdateModuleData::friend_newModuleData(INI *ini)
{
	ReplaceObjectUpdateModuleData *data = new ReplaceObjectUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ReplaceObjectUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
