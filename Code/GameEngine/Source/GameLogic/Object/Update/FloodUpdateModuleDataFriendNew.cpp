// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@FloodUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024D17A, 81 bytes. Dedicated TU: the factory news 0x14, runs the
// pinned nullary ctor (0x48DF7A, sole raw caller is this factory), then feeds
// the new data plus the rowed parse proc (0x48E15B, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x10 pad). Recipe:
// AttachUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// FloodUpdateModuleData::buildFieldParse proc (Flood table 0xC4C9A8 with
// FloodMember at +0) pushed as the factory's proc immediate; the ctor fits
// the 0x14 news size; the rowed poolkey 0x48E0FA (Flood) closes this cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class FloodUpdateModuleData
{
public:
	FloodUpdateModuleData();
	virtual ~FloodUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x14 - 4];
};

// ?friend_newModuleData@FloodUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FloodUpdateModuleData::friend_newModuleData(INI *ini)
{
	FloodUpdateModuleData *data = new FloodUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FloodUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
