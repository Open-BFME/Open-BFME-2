// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@BoneFXUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00253C78, 84 bytes. Dedicated TU: the factory news 0xD94, runs the
// declared-only nullary ctor (pinned at 0x487797, sole caller is this factory
// and vtable 0xC4B0E8 is installed only there), then feeds the new data plus
// the class parse proc (rowed at 0x253C67, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0xD90 pad). Recipe:
// OCLUpdateModuleDataFriendNew.cpp. Class identity is retail's own INI table
// at 0x00BF1158 (DamageFXTypes plus DamageOCLTypes plus DamageParticleTypes
// plus Pristine plus Damaged plus Rubble FX and OCL lists per ZH BoneFXUpdate.h)
// beside the rowed BoneFXUpdate bodies (initTimes plus pool key plus name).

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class BoneFXUpdateModuleData
{
public:
	BoneFXUpdateModuleData();
	virtual ~BoneFXUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD94 - 4];
};

// ?friend_newModuleData@BoneFXUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BoneFXUpdateModuleData::friend_newModuleData(INI *ini)
{
	BoneFXUpdateModuleData *data = new BoneFXUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, BoneFXUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
