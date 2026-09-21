// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "StoreObjectsSpecialPower" (addModule
// pairs the name with this factory); formerly misnamed SupplyCenterProductionExitUpdate/SupplyCenterProductionExitUpdateModuleData.
//
// ?friend_newModuleData@StoreObjectsSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00253121, 84 bytes. Dedicated TU: the rowed no-arg ctor TU
// SupplyCenterProductionExitUpdateCtor.cpp proves a 0xCC-byte class (0xC8-byte
// opaque base plus a trailing float); the factory news 0xCC, runs the
// declared-only ctor (rowed at 0x4CD8FB), then feeds the new data plus the
// class parse proc at 0x4CD918 (pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0xC8 pad). Recipe:
// CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void SupplyCenterProductionExitUpdateParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class StoreObjectsSpecialPower
{
public:
	StoreObjectsSpecialPower();
	virtual ~StoreObjectsSpecialPower();
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xCC - 4];
};

// ?friend_newModuleData@StoreObjectsSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StoreObjectsSpecialPower::friend_newModuleData(INI *ini)
{
	StoreObjectsSpecialPower *data = new StoreObjectsSpecialPower;
	if (ini)
		ini->initFromINIMultiProc(data, SupplyCenterProductionExitUpdateParse);
	return reinterpret_cast<ModuleData *>(data);
}
