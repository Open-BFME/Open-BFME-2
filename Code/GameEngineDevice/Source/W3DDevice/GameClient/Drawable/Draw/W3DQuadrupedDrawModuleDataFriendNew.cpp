// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@W3DQuadrupedDraw@@SAPAVModuleData@@PAVINI@@@Z, retail
// 0x00065218, 84 bytes. Dedicated TU: the factory news 0x198, runs the
// declared-only ctor (pinned at 0x651C2: subclass ctor over the
// W3DModelDrawModuleData base at 0xC8EEF, then a member construct), then
// feeds the new data plus the class parse proc at 0xCA089 (pushed immediate,
// no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is
// non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x194 pad).
// Recipe: W3DSupplyDrawModuleDataFriendNew.cpp. Donor reference: BFME1
// W3DQuadrupedDrawModuleDataFactory.cpp keeps the same factory shape.

class ModuleData;
class INI;
class MultiIniFieldParse;

void W3DQuadrupedDrawModuleDataParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class W3DQuadrupedDrawModuleData
{
public:
	W3DQuadrupedDrawModuleData();
	virtual ~W3DQuadrupedDrawModuleData();

private:
	unsigned char m_pad[0x198 - 4];
};

class W3DQuadrupedDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DQuadrupedDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DQuadrupedDraw::friend_newModuleData(INI *ini)
{
	W3DQuadrupedDrawModuleData *data = new W3DQuadrupedDrawModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, W3DQuadrupedDrawModuleDataParse);
	return reinterpret_cast<ModuleData *>(data);
}
