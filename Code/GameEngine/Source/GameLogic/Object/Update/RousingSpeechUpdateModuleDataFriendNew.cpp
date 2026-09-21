// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@RousingSpeechUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024F58C, 84 bytes. Dedicated TU: the factory news 0xF8, runs the
// pinned nullary ctor (0x4AD0EE, sole raw E8 caller, installs vtable
// 0x00C55048 with stores matching the parse-table offsets 0xC8 to 0xF4),
// then feeds the new data plus the class parse proc (pinned at 0x4ACD73,
// pushed immediate, chained over base proc 0x44ED95 with own table 0xC54F28
// carrying 10 of 10 BFME1 RousingSpeech fields in order) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0xF4 pad). Recipe:
// EmotionTrackerUpdateModuleDataFriendNew.cpp. Class identity is the chained
// RousingSpeech parse proc pushed as the factory's proc immediate (VA-push
// exclusive to this factory) linked to the rowed RousingSpeechUpdate pool
// key at 0x4ACED8; the ctor fits the 0xF8 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RousingSpeechUpdateModuleData
{
public:
	RousingSpeechUpdateModuleData();
	virtual ~RousingSpeechUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xF8 - 4];
};

// ?friend_newModuleData@RousingSpeechUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RousingSpeechUpdateModuleData::friend_newModuleData(INI *ini)
{
	RousingSpeechUpdateModuleData *data = new RousingSpeechUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RousingSpeechUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
