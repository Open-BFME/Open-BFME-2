// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "RadarMarkerClientUpdate" (addModule
// pairs the name with this factory); formerly misnamed MarkerTypeUpdateModuleData.
//
// ?friend_newModuleData@RadarMarkerClientUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00252B11, 81 bytes. Dedicated TU: the factory news 0x0C, runs the
// declared-only nullary ctor (pinned at 0x4C9C98, sole caller is this
// factory; installs vtable 0x00C5EDF8), then feeds the new data plus the
// class parse proc (rowed at 0x4C9BBC, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x08 pad). Recipe:
// SupplyTruckAIUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// RadarMarkerClientUpdateModuleData::buildFieldParse proc (table 0x00C5ED98 whose
// first field is MarkerType) pushed as the factory's proc immediate.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RadarMarkerClientUpdateModuleData
{
public:
	RadarMarkerClientUpdateModuleData();
	virtual ~RadarMarkerClientUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x0C - 4];
};

// ?friend_newModuleData@RadarMarkerClientUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RadarMarkerClientUpdateModuleData::friend_newModuleData(INI *ini)
{
	RadarMarkerClientUpdateModuleData *data = new RadarMarkerClientUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RadarMarkerClientUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
