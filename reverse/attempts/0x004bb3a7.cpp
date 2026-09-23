// ??0CallHelpOnDamageModuleData@@QAE@XZ
// partial score=0.97 date=2026-09-23
// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0CallHelpOnDamageModuleData@@QAE@XZ, retail 0x004BB3A7, 116 bytes.
// Call-for-help data over own INI tables 0x00C6BB18 + 0x00C59F70
// (DamageTypes, CallRadius, CallDelay, MoveToAttacker, ValidObjects;
// offsets read from the retail table). DamageTypes at +8 defaults to all
// via an inline or-minus-1 ctor; CallRadius at +0xC defaults to 100.0f
// from the float pool; CallDelay at +0x10 defaults to four
// LogicFramesPerSecond; MoveToAttacker at +0x14 is false; ValidObjects at
// +0x18 is filter storage built in place through the pinned member ctor
// at 0x3623E5 plus a 28B FixedStorage temp from 0x00DFEFA4 applied
// through the pinned applyFilter at 0x362120. Size 0x1C matches the
// friend TU pad. Row supersedes the ctor pin. Shape follows
// AttachUpdateModuleDataCtor (filter plus FixedStorage temps plus
// explicit vtable), except the or-first DamageTypes init forces the
// vtable into the body (members initialize in declaration order, so an
// init-listed vtable would emit first) and the filter is constructed late
// by an explicit ctor call over plain storage (an init-listed filter
// would call before the vtable; a named construct() method call earns no
// EH state).
//
// WALL (4B, 112/116): the retail byte-1 EH state before the FixedStorage
// copy has no clean source. Scalar placement-new earns it but adds a
// null-check plus a state reset (+11B); the explicit ctor call used here
// earns no state. Repro needs a late-bumping construction without guard
// code. t=60.

#include <cstring>

extern int g_Va00DBA4E4;

struct DamageTypeMask
{
	DamageTypeMask()
	{
		m_mask |= -1;
	}
	~DamageTypeMask();

	unsigned int m_mask;
};

DamageTypeMask::~DamageTypeMask()
{
	m_mask = 0;
}

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
	~BfmeFixedStorage0004543D() {}

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();

private:
	int m_x;
};

Rva003623E5Member::~Rva003623E5Member()
{
	m_x = 0;
}

class Rva003623E5Filter
{
public:
	void applyFilter(BfmeFixedStorage0004543D storage);
};

class CallHelpOnDamageModuleData
{
public:
	CallHelpOnDamageModuleData();

private:
	void *m_vtable; // +0
	int m_gap04; // +4
	DamageTypeMask m_damageTypes; // +8, DamageTypes
	float m_callRadius; // +0xC, CallRadius
	int m_callDelay; // +0x10, CallDelay
	bool m_moveToAttacker; // +0x14, MoveToAttacker
	int m_validObjectsFilterStorage; // +0x18, ValidObjects (filter built in place)
};

// ??0CallHelpOnDamageModuleData@@QAE@XZ @0x004BB3A7
CallHelpOnDamageModuleData::CallHelpOnDamageModuleData()
	: m_damageTypes()
{
	m_vtable = reinterpret_cast<void *>(0x00C59EB8);
	m_callRadius = 100.0f;
	m_callDelay = 4 * g_Va00DBA4E4;
	m_moveToAttacker = false;
	reinterpret_cast<Rva003623E5Member *>(&m_validObjectsFilterStorage)->Rva003623E5Member::Rva003623E5Member();
	reinterpret_cast<Rva003623E5Filter *>(&m_validObjectsFilterStorage)->applyFilter(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
