// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@W3DLightDraw@@SAPAVModuleData@@PAVINI@@@Z, retail
// 0x00064E2F, 81 bytes. Dedicated TU: the factory news 0x48, runs the
// declared-only ctor (pinned at 0xCFB3E: frameless light ctor with vtable
// 0xBCD820 plus color and flicker inits), then feeds the new data plus the
// class parse proc at 0xCFBDF (pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x44 pad). Recipe:
// W3DLaserDrawModuleDataFriendNew.cpp. Donor reference: BFME1
// W3DLightDrawFriendNewModuleDataThunk.cpp news the same 0x48 bytes.

class ModuleData;
class INI;
class MultiIniFieldParse;

void W3DLightDrawModuleDataParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class W3DLightDrawModuleData
{
public:
	W3DLightDrawModuleData();
	virtual ~W3DLightDrawModuleData();

private:
	unsigned char m_pad[0x48 - 4];
};

class W3DLightDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DLightDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DLightDraw::friend_newModuleData(INI *ini)
{
	W3DLightDrawModuleData *data = new W3DLightDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DLightDrawModuleDataParse);
	return reinterpret_cast<ModuleData *>(data);
}
