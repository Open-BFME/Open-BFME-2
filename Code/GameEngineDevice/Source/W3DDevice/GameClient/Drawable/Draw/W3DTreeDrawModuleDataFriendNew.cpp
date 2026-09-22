// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@W3DTreeDraw@@SAPAVModuleData@@PAVINI@@@Z, retail
// 0x00064C0B, 81 bytes. Dedicated TU: the factory news 0x64, runs the
// declared-only ctor (pinned at 0xCEBBF: EH ctor with vtable 0xBCCDF0 plus
// float and AsciiString members), then feeds the new data plus the class
// parse proc at 0xCED03 (pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x60 pad). Recipe:
// W3DLaserDrawModuleDataFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void W3DTreeDrawModuleDataParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class W3DTreeDrawModuleData
{
public:
	W3DTreeDrawModuleData();
	virtual ~W3DTreeDrawModuleData();

private:
	unsigned char m_pad[0x64 - 4];
};

class W3DTreeDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DTreeDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DTreeDraw::friend_newModuleData(INI *ini)
{
	W3DTreeDrawModuleData *data = new W3DTreeDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DTreeDrawModuleDataParse);
	return reinterpret_cast<ModuleData *>(data);
}
