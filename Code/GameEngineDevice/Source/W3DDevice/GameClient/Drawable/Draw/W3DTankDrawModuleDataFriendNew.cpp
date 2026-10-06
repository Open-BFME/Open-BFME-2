// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@W3DTankDraw@@SAPAVModuleData@@PAVINI@@@Z, retail
// 0x00064B7F, 84 bytes. Dedicated TU: the factory news 0x19C, runs the
// declared-only ctor (pinned at 0xCE6E6: subclass ctor over the
// W3DModelDrawModuleData base at 0xC8EEF), then feeds the new data plus the
// class parse proc at 0xCDF96 (pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x198 pad). Recipe:
// W3DSupplyDrawModuleDataFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void W3DTankDrawModuleDataParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class W3DTankDrawModuleData
{
public:
	W3DTankDrawModuleData();
	virtual ~W3DTankDrawModuleData();

private:
	unsigned char m_pad[0x19C - 4];
};

class W3DTankDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DTankDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DTankDraw::friend_newModuleData(INI *ini)
{
	W3DTankDrawModuleData *data = new W3DTankDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DTankDrawModuleDataParse);
	return reinterpret_cast<ModuleData *>(data);
}
