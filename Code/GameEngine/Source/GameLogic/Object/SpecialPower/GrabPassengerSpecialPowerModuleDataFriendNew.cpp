// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@GrabPassengerSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00252088, 84 bytes. Dedicated TU: the factory news 0x84, runs the
// declared-only ctor (pinned at 0x4C5421; GrabRadius plus AllowTree fields
// live in the class table at 0x00C5D8A8), then feeds the new data plus the
// class parse proc (pinned at 0x4C4F89; chained through the rowed
// SpecialPowerModuleData base proc at 0x493207, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x80 pad).
// Recipe: DevastateSpecialPowerModuleDataFriendNew.cpp. Class identity is
// retail's own INI table at 0x00C5D8A8 (Grab led) joined to the rowed
// GrabPassengerSpecialPower behavior name.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class GrabPassengerSpecialPowerModuleData
{
public:
	GrabPassengerSpecialPowerModuleData();
	virtual ~GrabPassengerSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x84 - 4];
};

// ?friend_newModuleData@GrabPassengerSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GrabPassengerSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	GrabPassengerSpecialPowerModuleData *data = new GrabPassengerSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, GrabPassengerSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
