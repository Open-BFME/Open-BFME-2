// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@OneRingPenaltyUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E42C, 81 bytes. Dedicated TU: the factory news 0x24, runs the
// declared-only nullary ctor (rowed at 0x4999F1, sole caller is this
// factory; installs vtable 0x00C50298), then feeds the new data plus the
// class parse proc (rowed at 0x499A5F, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x20 pad). Recipe:
// MarkerTypeUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// OneRingPenaltyUpdateModuleData::buildFieldParse proc (table 0x00C503B0
// Ring fields) pushed as the factory's proc immediate.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class OneRingPenaltyUpdateModuleData
{
public:
	OneRingPenaltyUpdateModuleData();
	virtual ~OneRingPenaltyUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x24 - 4];
};

// ?friend_newModuleData@OneRingPenaltyUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *OneRingPenaltyUpdateModuleData::friend_newModuleData(INI *ini)
{
	OneRingPenaltyUpdateModuleData *data = new OneRingPenaltyUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, OneRingPenaltyUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
