// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@StopSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002522B5, 84 bytes. Dedicated TU: the factory news 0x80, runs
// the rowed ctor (0x4C68AB, trivial 22B body over the pinned SpecialPower
// base with the and-zero StopPowerTemplate at +0x7C and the folded vtable
// 0x00C5E7A8), then feeds the new data plus the class parse proc (rowed
// base-call link at 0x4C6751, pushed immediate, SpecialPower base proc
// plus table 0x00C5DDE4 holding StopPowerTemplate at +0x7C, the sole
// field; the StopSpecialPower pool key sits in the same cluster) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x7C pad). Recipe:
// DefectorSpecialPowerModuleDataFriendNew.cpp. Class identity is the
// rowed StopSpecialPowerModuleData::buildFieldParse proc pushed as the
// factory's proc immediate (unique image-wide).

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class StopSpecialPowerModuleData
{
public:
	StopSpecialPowerModuleData();
	virtual ~StopSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x80 - 4];
};

// ?friend_newModuleData@StopSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StopSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	StopSpecialPowerModuleData *data = new StopSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, StopSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
