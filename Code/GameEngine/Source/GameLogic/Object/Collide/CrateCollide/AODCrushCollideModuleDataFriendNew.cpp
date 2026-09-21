// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AODCrushCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00251056, 81 bytes. Dedicated TU: the factory news 0x48, runs
// the pinned ctor (0x4BBF89, EH body with the tiered FX and OCL slots plus
// the filter member), then feeds the new data plus the class parse proc
// (rowed single-table leaf at 0x4BBFFC, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x44 pad). Recipe:
// UnitCrateCollideModuleDataFriendNew.cpp. Class identity is the rowed
// AODCrushCollideModuleData::buildFieldParse proc (table 0x0085A4A8 holding
// SmallFXList at +0x08 plus SmallObjectCreationList at +0x0C plus
// MediumFXList at +0x10 plus MediumObjectCreationList at +0x14 plus
// LargeFXList at +0x18 plus LargeObjectCreationList at +0x1C plus DamageType
// at +0x20 plus Damage at +0x28) pushed as the factory's proc immediate; the
// AODCrushCollide pool key at 0x4BBF69 sits in the same cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AODCrushCollideModuleData
{
public:
	AODCrushCollideModuleData();
	virtual ~AODCrushCollideModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x48 - 4];
};

// ?friend_newModuleData@AODCrushCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AODCrushCollideModuleData::friend_newModuleData(INI *ini)
{
	AODCrushCollideModuleData *data = new AODCrushCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AODCrushCollideModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
