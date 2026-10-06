// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@BoredUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E122, 81 bytes. Dedicated TU: the factory news 0x1C, runs the
// declared-only ctor (pinned at 0x4966FE, EH body with filter/FixedStorage
// members plus unrowed 0x362087 still unrowed), then feeds the new data plus
// the class parse proc (rowed at 0x496780, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x18 pad). Recipe:
// AutoPickUpUpdateModuleDataFriendNew.cpp. Class identity is retail's own INI
// table at 0x00C4F618 (ScanDelayTime/ScanDistance/BoredFilter/
// CanScanWhileAttackingOrMoving/SpecialPowerTemplate, the scan sibling of
// AutoPickUpUpdateModuleData) plus the BoredUpdate pool key at 0x4966B9 whose
// 69B body ends where the ctor starts.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class BoredUpdateModuleData
{
public:
	BoredUpdateModuleData();
	virtual ~BoredUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C - 4];
};

// ?friend_newModuleData@BoredUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BoredUpdateModuleData::friend_newModuleData(INI *ini)
{
	BoredUpdateModuleData *data = new BoredUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, BoredUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
