// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@GeometryUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00250642, 84 bytes. Dedicated TU: the factory news 0x13C, runs
// the rowed ctor (0x4B6EE2, EH body over the OpenContain base with the vector
// and string members), then feeds the new data plus the class parse proc
// (pinned chained link at 0x4B6A3C, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x138 pad). Recipe:
// BaseUpgradeModuleDataFriendNew.cpp. Class identity is the pinned
// GeometryUpgradeModuleData::buildFieldParse proc (Upgrade base proc 0x4CE29D
// plus table 0x00858918 holding ShowGeometry at +0x118 plus HideGeometry at
// +0x124 plus WallBoundsMesh at +0x130 plus RampMesh1 at +0x134 plus
// RampMesh2 at +0x138, matching the ctor stores) pushed as the factory's
// proc immediate; the GeometryUpgrade pool key at 0x4B6ABF sits in the same
// cluster and the BFME1 constructor donor proves the class.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class GeometryUpgradeModuleData
{
public:
	GeometryUpgradeModuleData();
	virtual ~GeometryUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x13C - 4];
};

// ?friend_newModuleData@GeometryUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GeometryUpgradeModuleData::friend_newModuleData(INI *ini)
{
	GeometryUpgradeModuleData *data = new GeometryUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, GeometryUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
