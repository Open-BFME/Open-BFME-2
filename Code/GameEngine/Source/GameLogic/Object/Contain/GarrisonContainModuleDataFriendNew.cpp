// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@GarrisonContainModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00254F90, 84 bytes. Dedicated TU: the factory news 0xAC, runs the
// pinned nullary ctor (0x47978F, callers are this factory plus a derived
// base-call from 0x47A251, installs vtable 0x00C462D8 with stores matching
// the parse-table offsets 0x98 to 0xA8), then feeds the new data plus the
// class parse proc (pinned at 0x254F75, pushed immediate, chained over base
// proc 0x46523D with own table 0x7F3360 carrying 5 of 5 BFME1
// GarrisonContain fields in order) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0xA8 pad). Recipe: RousingSpeechUpdateModuleDataFriendNew.cpp. Class
// identity is the chained GarrisonContain parse proc pushed as the
// factory's proc immediate (VA-push exclusive to this factory, mid-chain
// link with HordeGarrison chaining above at 0x47A029) linked to the rowed
// GarrisonContain pool key at 0x47801C; the ctor fits the 0xAC news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class GarrisonContainModuleData
{
public:
	GarrisonContainModuleData();
	virtual ~GarrisonContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xAC - 4];
};

// ?friend_newModuleData@GarrisonContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GarrisonContainModuleData::friend_newModuleData(INI *ini)
{
	GarrisonContainModuleData *data = new GarrisonContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, GarrisonContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
