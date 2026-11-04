// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Identity: ModuleFactory registers this data class under "UpgradeSoundSelectorClientBehaviorModuleData" (addModule
// pairs the name with this factory); formerly misnamed BattlePlanUpdate/BattlePlanUpdateModuleData.
// stlport
//
// ??0UpgradeSoundSelectorClientBehaviorModuleData@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x004CB9F3.
// Root class (no base call): vtable plus a trailing E16 vector at +0x08
// default-constructed through the vector_base pinned at retail 0x00211E58,
// with the one-byte allocator temporary at [esp+0x07] (frameless).
// Factory stub order names it; stub size 0x14 confirms the layout.
#include <vector>

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

class Thing;
class ModuleData;

class INI;
class UpgradeSoundSelectorClientBehaviorModuleData
{
public:
	UpgradeSoundSelectorClientBehaviorModuleData();
	static void parseVoicePriority(INI*,void*,void*,const void*);
	static void parseSoundUpgrade(INI *, void *, void *, const void *);
	virtual ~UpgradeSoundSelectorClientBehaviorModuleData();
	char m_pad04[0x4];
	_STL::vector<BfmeE16> m_vec08; // +0x08
};

UpgradeSoundSelectorClientBehaviorModuleData::UpgradeSoundSelectorClientBehaviorModuleData()
	: m_vec08()
{
}

// UpgradeSoundSelectorClientBehaviorModuleData::~UpgradeSoundSelectorClientBehaviorModuleData: defined in UpgradeSoundSelectorClientBehaviorModuleDataDtor.cpp (its row's unit).
