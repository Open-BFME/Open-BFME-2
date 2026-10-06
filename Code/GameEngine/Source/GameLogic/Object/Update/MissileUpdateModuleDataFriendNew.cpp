// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@MissileUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024EFA0, 84 bytes. Dedicated TU: the factory news 0x120, runs
// the pinned ctor (0x4A77B8, EH body over the 0x45B4F1 base), then feeds the
// new data plus the class parse proc (pinned chained link at 0x4A74EF,
// pushed immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x11C pad).
// Recipe: CommandPointsUpgradeModuleDataFriendNew.cpp. Class identity is the
// pinned MissileUpdateModuleData::buildFieldParse proc (base proc plus table
// 0x00C53470 holding FuelLifetime through DetonateOnNoFuel) pushed as the
// factory's proc immediate; the MissileUpdate pool key at 0x4A76C3 sits in
// the same retail cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class MissileUpdateModuleData
{
public:
	MissileUpdateModuleData();
	virtual ~MissileUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x120 - 4];
};

// ?friend_newModuleData@MissileUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *MissileUpdateModuleData::friend_newModuleData(INI *ini)
{
	MissileUpdateModuleData *data = new MissileUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, MissileUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
