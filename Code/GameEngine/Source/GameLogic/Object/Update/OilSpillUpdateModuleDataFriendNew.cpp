// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@OilSpillUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024CFDF, 81 bytes. Dedicated TU: the factory news 0x20, runs the
// pinned nullary ctor (0x48C16C, sole raw caller is this factory; 0.6 ctor
// partial banked), then feeds the new data plus the rowed parse proc
// (0x48C151, pushed immediate) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0x1C pad). Recipe: FloodUpdateModuleDataFriendNew.cpp. Class identity is
// the rowed OilSpillUpdateModuleData::buildFieldParse proc (Breadcrumb
// table 0xC4C2A8) pushed as the factory's proc immediate; the ctor fits the
// 0x20 news size; the rowed poolkey cluster (OilSpillUpdate) closes this
// vein beside the Hero-side opaque base.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class OilSpillUpdateModuleData
{
public:
	OilSpillUpdateModuleData();
	virtual ~OilSpillUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x20 - 4];
};

// ?friend_newModuleData@OilSpillUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *OilSpillUpdateModuleData::friend_newModuleData(INI *ini)
{
	OilSpillUpdateModuleData *data = new OilSpillUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, OilSpillUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
