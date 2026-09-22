// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ThreatFinderUpdate@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x0024FC08, 81 bytes. Named for the "ThreatFinderUpdate" literal
// ModuleFactory registers with this stub; ZH's module macro defines it on the
// module class. It news 0xC, runs the no-arg data ctor at 0x3ECC80
// and hands the data plus the parse proc at 0x3ECC91 to
// INI::initFromINIMultiProc when ini is non-null. ThreatFinderUpdateModuleData is ZH's
// naming convention, not a retail fact. Recipe: CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class MultiIniFieldParse;

void ThreatFinderUpdateParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ThreatFinderUpdateModuleData
{
public:
	ThreatFinderUpdateModuleData();

private:
	char m_pad[0xC];
};

class ThreatFinderUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ThreatFinderUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ThreatFinderUpdate::friend_newModuleData(INI *ini)
{
	ThreatFinderUpdateModuleData *data = new ThreatFinderUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ThreatFinderUpdateParse);
	return reinterpret_cast<ModuleData *>(data);
}
