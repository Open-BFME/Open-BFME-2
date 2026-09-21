// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@SlowDeathBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024B29C, 84 bytes. Dedicated TU: the factory news 0x190, runs the
// declared-only ctor (pinned at 0x45E386, EH body with vtable 0x00C42108 plus
// Sink stores matching the BFME1 donor still unrowed), then feeds the new
// data plus the class parse proc (rowed at 0x45E93F, pushed immediate, no
// pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x18C pad). Recipe:
// DumbProjectileBehaviorModuleDataFriendNew.cpp. Class identity is retail's
// own INI table at 0x00C42290 (SinkRate at +0x38 plus probability 10 at +0x3C
// per the BFME1 SlowDeathBehavior donor) pushed as the factory's proc
// immediate; the ctor fits the 0x190 news size.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SlowDeathBehaviorModuleData
{
public:
	SlowDeathBehaviorModuleData();
	virtual ~SlowDeathBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x190 - 4];
};

// ?friend_newModuleData@SlowDeathBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SlowDeathBehaviorModuleData::friend_newModuleData(INI *ini)
{
	SlowDeathBehaviorModuleData *data = new SlowDeathBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SlowDeathBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
