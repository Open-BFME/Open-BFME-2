// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@W3DTruckDraw@@SAPAVModuleData@@PAVINI@@@Z, retail
// 0x00064AF0, 84 bytes. Dedicated TU: the factory news 0x1F0, runs the
// declared-only ctor (pinned at 0xCB1C9: subclass ctor over the
// W3DModelDrawModuleData base at 0xC8EEF, then vtable 0xBCC508), then feeds
// the new data plus the class parse proc at 0xCB133 (pushed immediate, no
// pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x1EC pad). Recipe:
// W3DSupplyDrawModuleDataFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void W3DTruckDrawModuleDataParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class W3DTruckDrawModuleData
{
public:
	W3DTruckDrawModuleData();
	virtual ~W3DTruckDrawModuleData();

private:
	unsigned char m_pad[0x1F0 - 4];
};

class W3DTruckDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DTruckDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DTruckDraw::friend_newModuleData(INI *ini)
{
	W3DTruckDrawModuleData *data = new W3DTruckDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DTruckDrawModuleDataParse);
	return reinterpret_cast<ModuleData *>(data);
}
