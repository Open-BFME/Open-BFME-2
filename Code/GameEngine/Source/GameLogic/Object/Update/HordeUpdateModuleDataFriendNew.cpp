// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "BannerCarrierUpdate" (addModule
// pairs the name with this factory); formerly misnamed HordeUpdateModuleData.
//
// ?friend_newModuleData@BannerCarrierUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x0024E1AB, 81 bytes. Dedicated TU: the factory news 0x44, runs the
// declared-only ctor (pinned at 0x496FA5, sole caller is this factory), then
// feeds the new data plus the class parse proc (rowed at 0x4976CA, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0x40 pad). Recipe: BoredUpdateModuleDataFriendNew.cpp. Class identity is
// the rowed BannerCarrierUpdateModuleData::buildFieldParse proc (Horde table
// 0x00C4F9E8: IdleSpawnRate MeleeFreeUnitSpawnTime DiedRespawnTime
// BannerMorphFX UnitSpawnFX ReplenishNearbyHorde ScanHordeDistance
// UpgradeRequired) pushed as the factory's proc immediate.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class BannerCarrierUpdateModuleData
{
public:
	BannerCarrierUpdateModuleData();
	virtual ~BannerCarrierUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x44 - 4];
};

// ?friend_newModuleData@BannerCarrierUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BannerCarrierUpdateModuleData::friend_newModuleData(INI *ini)
{
	BannerCarrierUpdateModuleData *data = new BannerCarrierUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, BannerCarrierUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
