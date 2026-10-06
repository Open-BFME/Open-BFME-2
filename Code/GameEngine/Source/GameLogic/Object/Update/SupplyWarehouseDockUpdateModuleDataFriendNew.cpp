// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@SupplyWarehouseDockUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024F02F, 81 bytes. Dedicated TU: the rowed no-arg ctor TU
// (SupplyWarehouseDockUpdate.cpp, BFME1 donor, base DockUpdateModuleData)
// proves the ModuleData layout; the factory news 0x18, runs the
// declared-only ctor (rowed at 0x4A7FF0), then feeds the new data plus the
// class parse proc at 0x4A7D3A (pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x14 pad). Recipe:
// CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void SupplyWarehouseDockUpdateModuleDataParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SupplyWarehouseDockUpdateModuleData
{
public:
	SupplyWarehouseDockUpdateModuleData();
	virtual ~SupplyWarehouseDockUpdateModuleData();
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@SupplyWarehouseDockUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SupplyWarehouseDockUpdateModuleData::friend_newModuleData(INI *ini)
{
	SupplyWarehouseDockUpdateModuleData *data = new SupplyWarehouseDockUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SupplyWarehouseDockUpdateModuleDataParse);
	return reinterpret_cast<ModuleData *>(data);
}
