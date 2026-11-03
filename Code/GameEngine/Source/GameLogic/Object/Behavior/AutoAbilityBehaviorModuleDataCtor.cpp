// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /arch:SSE /EHsc /MD /DNDEBUG
// stlport
//
// ??0AutoAbilityBehaviorModuleData@@QAE@XZ, retail 0x0045A2E7, 135 bytes.
// Target evidence: own vtable 0x00C41568, INI table 0x00C41690 (SpecialAbility,
// MaxScanRange, MinScanRange, WorkingRadius, StartsActive,
// BaseMaxRangeFromStartPos, AdjustAttackMeleePosition, Query, AllowSelf,
// IdleTimeSeconds), the factory 0x0024AFE5 news 0x60, and the rowed dtor
// 0x0045A517 (Snapshot base, string at +0x18, six-entry query array at +0x2C).
// EH state 0 is the Snapshot base and state 1 the SpecialAbility string; the
// ForbiddenStatus mask at +0x1C is reset through the rowed bitset<128>::reset
// 0x0024CA24 and then cleared again with memset; the Query entries build
// through ehvec with the element ctor 0x0045A1D9 and dtor 0x0045A226.
#include "Common/Snapshot.h"
#include "../../../../Include/Common/BfmeModuleData.h"
// Preserve the native Snapshot teardown in the constructor's EH cleanup.
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
#include "ascii_string.h"
#include <bitset>
#include <string.h>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"

class AutoAbilityQueryEntry
{
public:
	AutoAbilityQueryEntry();
	~AutoAbilityQueryEntry();

private:
	int m_state;
	Rva003623E5Member m_filter;
};

// The native ehvec constructor callback is the rowed 18-byte init at
// 45A1D9: initialize state, construct the +4 filter, return this. Its
// thiscall ABI is the compiler's array-element constructor ABI; keep the
// established row name when binding the compiler-generated callback.
#pragma comment(linker, "/alternatename:??0AutoAbilityQueryEntry@@QAE@XZ=?init@AutoAbilityQueryEntry@@QAEPAV1@XZ")

// C41568 has all 31 shared ModuleData slots, with this class's own deleter.
class AutoAbilityBehaviorModuleData : public ModuleData
{
public:
	AutoAbilityBehaviorModuleData();
	virtual ~AutoAbilityBehaviorModuleData();

private:
	int m_moduleTagNameKey; // +4
	float m_maxScanRange; // +8
	float m_minScanRange; // +0xC
	float m_workingRadius; // +0x10
	float m_idleTimeSeconds; // +0x14
	AsciiString m_specialAbility; // +0x18
	_STL::bitset<128> m_forbiddenStatus; // +0x1C
	AutoAbilityQueryEntry m_query[6]; // +0x2C
	bool m_startsActive; // +0x5C
	bool m_baseMaxRangeFromStartPos; // +0x5D
	bool m_adjustAttackMeleePosition; // +0x5E
	bool m_allowSelf; // +0x5F
};

AutoAbilityBehaviorModuleData::AutoAbilityBehaviorModuleData()
	: m_maxScanRange(0.0f)
	, m_minScanRange(0.0f)
	, m_workingRadius(0.0f)
	, m_idleTimeSeconds(0.0f)
{
	m_startsActive = false;
	m_baseMaxRangeFromStartPos = false;
	m_adjustAttackMeleePosition = false;
	m_allowSelf = true;
	memset(&m_forbiddenStatus, 0, sizeof(m_forbiddenStatus));
}
