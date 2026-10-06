// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@W3DLaserDraw@@SAPAVModuleData@@PAVINI@@@Z, retail
// 0x00064962, 81 bytes. Dedicated TU: the factory news 0x74, runs the
// declared-only ctor (pinned at 0xC9A6F: frameless ctor with an E16 vector
// at +0x2C, a member construct at +0x4C and laser field inits), then feeds
// the new data plus the class parse proc at 0xC928F (pushed immediate, no
// pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x70 pad). Recipe:
// W3DSupplyDrawModuleDataFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void W3DLaserDrawModuleDataParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class W3DLaserDrawModuleData
{
public:
	W3DLaserDrawModuleData();
	virtual ~W3DLaserDrawModuleData();

private:
	unsigned char m_pad[0x74 - 4];
};

class W3DLaserDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DLaserDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DLaserDraw::friend_newModuleData(INI *ini)
{
	W3DLaserDrawModuleData *data = new W3DLaserDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DLaserDrawModuleDataParse);
	return reinterpret_cast<ModuleData *>(data);
}
