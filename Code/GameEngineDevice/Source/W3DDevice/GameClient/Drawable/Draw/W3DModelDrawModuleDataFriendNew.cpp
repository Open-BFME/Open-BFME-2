// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@W3DModelDraw@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x000648D6, 83 bytes. Dedicated TU: the factory news 0x188, runs the
// declared-only ctor (pinned at 0xC8EEF), then feeds the new data plus the
// class parse proc at 0xC9240 (pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x184 pad). Recipe:
// SupplyWarehouseDockUpdateModuleDataFriendNew.cpp. The ctor installs vtable
// 0xBCADE8 and builds seven E16 vectors; the proc adds the W3DModelDraw
// table at 0xBCB3C8 (InitialRecoilSpeed first, BFME1 donor field order).

class ModuleData;
class INI;
class MultiIniFieldParse;

void W3DModelDrawModuleDataParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class W3DModelDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

class W3DModelDrawModuleData
{
public:
	W3DModelDrawModuleData();
	virtual ~W3DModelDrawModuleData();

private:
	unsigned char m_pad[0x188 - 4];
};

// ?friend_newModuleData@W3DModelDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DModelDraw::friend_newModuleData(INI *ini)
{
	W3DModelDrawModuleData *data = new W3DModelDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DModelDrawModuleDataParse);
	return reinterpret_cast<ModuleData *>(data);
}
