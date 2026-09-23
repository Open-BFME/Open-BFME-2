// ??0AutoAbilityBehaviorModuleData@@QAE@XZ
// partial score=0.93 date=2026-09-23
// cl: /O1 /arch:SSE /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0AutoAbilityBehaviorModuleData@@QAE@XZ, retail 0x0045A2E7, 135 bytes.
// Auto-acquire behavior data over own INI table 0x00C41690 (SpecialAbility,
// MaxScanRange, MinScanRange, WorkingRadius, StartsActive,
// BaseMaxRangeFromStartPos, AdjustAttackMeleePosition, Query, AllowSelf,
// IdleTimeSeconds; offsets read from the retail table). MaxScanRange at +8,
// MinScanRange at +0xC, WorkingRadius at +0x10 and IdleTimeSeconds at +0x14
// null as floats; SpecialAbility at +0x18 is a name string (inline null
// AsciiString ctor, external dtor via the rowed 0x36410 pin, first EH
// state); ForbiddenStatus at +0x1C is a 128-bit status mask whose inline
// ctor resets it through the rowed bitset<128>::reset at 0x0024CA24 (plus
// a redundant 16-byte memset in the body, AttachUpdate precedent) with an
// opaque TU-local dtor for the second EH state; the six 8-byte Query
// entries at +0x2C (int state plus filter member, twin init at 0x45A1D9)
// build through the rowed ehvec helper at 0x00629512; StartsActive,
// BaseMaxRangeFromStartPos and AdjustAttackMeleePosition null while
// AllowSelf at +0x5F is true. Size 0x60 matches the ModuleData factory at
// 0x0024AFE5 news. Row supersedes the ctor pin.
//
// ORDER LAW (proven by three failed shapes): retail calls the
// ForbiddenStatus reset BEFORE the Query ehvec, but a member array always
// ehvecs in the init-list ahead of every body statement, so the reset
// cannot be a body statement. It is the body of the mask member's own
// inline ctor, emitted transparently between the SpecialAbility init and
// the array ehvec. The Query element ctor and dtor stay declared-only:
// twin's init at 0x45A1D9 is the element ctor under its construction name
// (an explicit function pointer cannot reach ehvec any other way) and the
// 0x45A226 thunk is its dtor, so the TU references both through the pins
// and the elements stay opaque exactly like the original TU saw them;
// defining them locally over-tracks the array into a third EH state.
// Array placement new is NOT a substitute: this toolchain
// emits a count cookie plus a null-check guard plus a third EH state for
// it. The empty-dtor mask is NOT a substitute either: only members with
// real (non-empty) dtors earn EH states, and the funclet table proves the
// two tracked entries are SpecialAbility and ForbiddenStatus with the
// array unwinding inside ehvec.

#include <bitset>
#include <cstring>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	char *m_data;
};

class ForbiddenStatusMask
{
public:
	ForbiddenStatusMask()
	{
		((_STL::bitset<128> *)m_words)->reset();
	}
	~ForbiddenStatusMask();

private:
	unsigned long m_words[4];
};

ForbiddenStatusMask::~ForbiddenStatusMask()
{
	m_words[0] = 0;
}

class QueryFilter
{
public:
	QueryFilter();

private:
	int m_state;
};

struct AutoAbilityQueryEntry
{
	int m_state;
	QueryFilter m_filter;

	AutoAbilityQueryEntry();
	~AutoAbilityQueryEntry();
};

class AutoAbilityBehaviorModuleData
{
public:
	AutoAbilityBehaviorModuleData();

private:
	const void *m_vtable; // +0
	int m_gap04; // +4
	float m_maxScanRange; // +8, MaxScanRange
	float m_minScanRange; // +0xC, MinScanRange
	float m_workingRadius; // +0x10, WorkingRadius
	float m_idleTimeSeconds; // +0x14, IdleTimeSeconds
	AsciiString m_specialAbility; // +0x18, SpecialAbility
	ForbiddenStatusMask m_forbiddenStatus; // +0x1C, ForbiddenStatus
	AutoAbilityQueryEntry m_query[6]; // +0x2C, Query
	bool m_startsActive; // +0x5C, StartsActive
	bool m_baseMaxRangeFromStartPos; // +0x5D, BaseMaxRangeFromStartPos
	bool m_adjustAttackMeleePosition; // +0x5E, AdjustAttackMeleePosition
	bool m_allowSelf; // +0x5F, AllowSelf
};

// ??0AutoAbilityBehaviorModuleData@@QAE@XZ @0x0045A2E7
AutoAbilityBehaviorModuleData::AutoAbilityBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C41568))
	, m_maxScanRange(0.0f)
	, m_minScanRange(0.0f)
	, m_workingRadius(0.0f)
	, m_idleTimeSeconds(0.0f)
	, m_specialAbility()
	, m_forbiddenStatus()
{
	m_startsActive = false;
	m_baseMaxRangeFromStartPos = false;
	m_adjustAttackMeleePosition = false;
	m_allowSelf = true;
	memset(&m_forbiddenStatus, 0, sizeof(m_forbiddenStatus));
}
