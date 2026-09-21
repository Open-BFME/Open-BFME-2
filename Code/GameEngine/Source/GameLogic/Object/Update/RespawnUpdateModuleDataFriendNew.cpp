// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "RespawnBody" (addModule
// pairs the name with this factory); formerly misnamed RespawnUpdateModuleData.
//
// ?friend_newModuleData@RespawnBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00251596, 81 bytes. Dedicated TU: the factory news 0x6C, runs the
// pinned ctor (0x4C14DF, EH body over the SupplyTruck base plus vtable plus
// filter plus respawn flag), then feeds the new data plus the class parse
// proc (pinned chained link at 0x4C12D0, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x68 pad). Recipe:
// CrateCollideModuleDataFriendNew.cpp. Class identity is the pinned
// RespawnBodyModuleData::buildFieldParse proc (SupplyTruck base proc plus
// table 0x00C5B8BC holding PermanentlyKilledByFilter at +0x64 plus CanRespawn
// at +0x68, matching the ctor stores) pushed as the factory's proc
// immediate; the RespawnUpdate pool key at 0x4C1455 sits in the same retail
// cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RespawnBodyModuleData
{
public:
	RespawnBodyModuleData();
	virtual ~RespawnBodyModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x6C - 4];
};

// ?friend_newModuleData@RespawnBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RespawnBodyModuleData::friend_newModuleData(INI *ini)
{
	RespawnBodyModuleData *data = new RespawnBodyModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RespawnBodyModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
