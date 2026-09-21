// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@TaintSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00251EE4, 84 bytes. Dedicated TU: the factory news 0x8C, runs the
// declared-only ctor (pinned at 0x4C4AB8; TaintObject plus TaintRadius plus
// TaintFX plus TaintOCL fields live in the class table at 0x00C5D518),
// then feeds the new data plus the class parse proc (pinned at 0x4C487B;
// chained through the rowed SpecialPowerModuleData base proc at 0x493207,
// pushed immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x88 pad).
// Recipe: DevastateSpecialPowerModuleDataFriendNew.cpp. Class identity is
// retail's own INI table at 0x00C5D518 (Taint led) joined to the
// TaintSpecialPower pool key at 0x4C48DF.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class TaintSpecialPowerModuleData
{
public:
	TaintSpecialPowerModuleData();
	virtual ~TaintSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x8C - 4];
};

// ?friend_newModuleData@TaintSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TaintSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	TaintSpecialPowerModuleData *data = new TaintSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, TaintSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
