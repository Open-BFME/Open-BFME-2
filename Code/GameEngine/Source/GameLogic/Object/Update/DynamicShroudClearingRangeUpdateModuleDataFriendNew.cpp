// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DynamicShroudClearingRangeUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024CE44, 81 bytes. Dedicated TU: the factory news 0x5C, runs
// the rowed nullary ctor (0x48B5C6, sole caller is this factory), then feeds
// the new data plus the rowed single-table parse proc (0x48B056, pushed
// immediate) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is
// non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x58 pad).
// Recipe: PassiveAreaEffectBehaviorModuleDataFriendNew.cpp. Class identity
// is the rowed DynamicShroudClearingRangeUpdateModuleData::buildFieldParse
// proc (ChangeInterval-led table 0xC4BE20 over the BFME1 donor layout);
// the ctor fits the 0x5C news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DynamicShroudClearingRangeUpdateModuleData
{
public:
	DynamicShroudClearingRangeUpdateModuleData();
	virtual ~DynamicShroudClearingRangeUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x5C - 4];
};

// ?friend_newModuleData@DynamicShroudClearingRangeUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DynamicShroudClearingRangeUpdateModuleData::friend_newModuleData(INI *ini)
{
	DynamicShroudClearingRangeUpdateModuleData *data = new DynamicShroudClearingRangeUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DynamicShroudClearingRangeUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
