// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "BeaconClientUpdateModuleData" (addModule
// pairs the name with this factory); formerly misnamed CleanupHazardUpdate/CleanupHazardUpdateModuleData.
//
// ?friend_newModuleData@BeaconClientUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x002529FF, 81 bytes. Dedicated TU: the rowed no-arg ctor TU
// CleanupHazardUpdateCtor.cpp proves a 0x10-byte root class (vtable plus
// three ints); the factory news 0x10, runs the declared-only ctor (rowed at
// 0x4C964C), then feeds the new data plus the class parse proc (pinned at
// 0x4C9663) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is
// non-null. Operator new and __EH_prolog resolve via their rows. The rowed
// ctor name spells the Update class, so the TU-local class keeps that
// spelling; the ModuleData/INI/parse decls are TU-local scaffolding.

class ModuleData;
class INI;
class MultiIniFieldParse;

void CleanupHazardUpdateParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class BeaconClientUpdateModuleData
{
public:
	BeaconClientUpdateModuleData();
	virtual ~BeaconClientUpdateModuleData();
	static ModuleData *friend_newModuleData(INI *ini);

private:
	int m_pad04;
	int m_i08;
	int m_i0C;
};

// ?friend_newModuleData@BeaconClientUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BeaconClientUpdateModuleData::friend_newModuleData(INI *ini)
{
	BeaconClientUpdateModuleData *data = new BeaconClientUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CleanupHazardUpdateParse);
	return reinterpret_cast<ModuleData *>(data);
}
