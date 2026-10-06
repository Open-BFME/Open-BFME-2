// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@OCLUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E5D3, 81 bytes. Dedicated TU: the rowed no-arg ctor TU
// (OCLUpdateModuleDataCtor.cpp, 0x1C-byte layout with the BFME2-only amount)
// proves the ModuleData layout; the factory news 0x1C, runs the
// declared-only ctor (rowed at 0x49B355), then feeds the new data plus the
// class parse proc (rowed at 0x49B370, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x18 pad). Recipe:
// SupplyWarehouseDockUpdateModuleDataFriendNew.cpp. Class identity is
// retail's own INI table at 0x00C50BA8 (OCL/MinDelay/MaxDelay/CreateAtEdge/
// Amount) beside the OCLUpdate.cpp debug path.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class OCLUpdateModuleData
{
public:
	OCLUpdateModuleData();
	virtual ~OCLUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C - 4];
};

// ?friend_newModuleData@OCLUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *OCLUpdateModuleData::friend_newModuleData(INI *ini)
{
	OCLUpdateModuleData *data = new OCLUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, OCLUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
