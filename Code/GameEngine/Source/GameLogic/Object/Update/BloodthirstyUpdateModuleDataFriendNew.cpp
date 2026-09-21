// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@BloodthirstyUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024A7E8, 81 bytes. Dedicated TU: the factory news 0x18, runs the
// rowed nullary ctor (0x44E2AC, vtable plus sacrifice filter plus experience
// float plus initiate-voice pair), then feeds the new data plus the class
// parse proc (rowed at 0x44E099, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x14 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// BloodthirstyUpdateModuleData::buildFieldParse proc (SacrificeFilter plus
// ExperienceModifier plus InitiateVoice) pushed as the factory's proc
// immediate; the ctor installs vtable 0x00C3F160 and fits the 0x18 news
// size; the rowed BloodthirstyUpdate pool key at 0x44E07E ends where the
// proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class BloodthirstyUpdateModuleData
{
public:
	BloodthirstyUpdateModuleData();
	virtual ~BloodthirstyUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@BloodthirstyUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BloodthirstyUpdateModuleData::friend_newModuleData(INI *ini)
{
	BloodthirstyUpdateModuleData *data = new BloodthirstyUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, BloodthirstyUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
