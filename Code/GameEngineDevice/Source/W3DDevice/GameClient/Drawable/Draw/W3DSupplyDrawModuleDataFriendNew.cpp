// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@W3DSupplyDraw@@SAPAVModuleData@@PAVINI@@@Z, retail
// 0x00064A61, 84 bytes. Dedicated TU: the factory news 0x18C, runs the
// declared-only ctor (pinned at 0xCAF17: frameless subclass ctor over the
// W3DModelDrawModuleData base at 0xC8EEF, then vtable 0xBCC0D0), then feeds
// the new data plus the class parse proc at 0xCAE28 (pushed immediate, no
// pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x188 pad). Recipe:
// W3DModelDrawModuleDataFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void W3DSupplyDrawModuleDataParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class W3DSupplyDrawModuleData
{
public:
	W3DSupplyDrawModuleData();
	virtual ~W3DSupplyDrawModuleData();

private:
	unsigned char m_pad[0x18C - 4];
};

class W3DSupplyDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DSupplyDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DSupplyDraw::friend_newModuleData(INI *ini)
{
	W3DSupplyDrawModuleData *data = new W3DSupplyDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DSupplyDrawModuleDataParse);
	return reinterpret_cast<ModuleData *>(data);
}
