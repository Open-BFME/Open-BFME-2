// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
// stlport
// ??1RampageBehaviorModuleData@@UAE@XZ, RVA 0x00458C9B, size 48.
// Virtual dtor destroying RequiredUpgrade vector at +8 then restoring
// Snapshot base vtable 0xBBB554 with trivial base inlined (no base call).
// Evidence: EH state 0 single vector teardown 0x2CC70, vtable-last
// 0xBBB554 same shape as UpgradeModuleData 0x255A42, slot-0 deleter
// 0x458C7F calls here, ctor 0x458C0F owns class and table 0xC40EF8.
#include <vector>

#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

#include "../../../../Include/Common/ModuleData.h"

inline ModuleData::~ModuleData() {}

class RampageBehaviorModuleData : public ModuleData
{
public:
	RampageBehaviorModuleData();
	RampageBehaviorModuleData(int);

private:
	_STL::vector<AsciiString> m_requiredUpgrade; // +0x08
	float m_healthThreshold; // +0x14
	int m_lifeTimer; // +0x18
	int m_angryLifeTimer; // +0x1C
	int m_resetTimer; // +0x20
	float m_enemyCheckRange; // +0x24
	int m_enemyThreshold; // +0x28
};

// ?dummyCtor@RampageBehaviorModuleData@@QAE@H@Z present-unmatched
RampageBehaviorModuleData::RampageBehaviorModuleData(int)
{
}

void deleteRampageBehaviorModuleData(RampageBehaviorModuleData *rampageBehaviorModuleData)
{
    delete rampageBehaviorModuleData;
}
