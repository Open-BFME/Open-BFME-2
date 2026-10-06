// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
//
// ??1AutoAbilityBehaviorModuleData@@UAE@XZ, retail 0x0045A517, 73 bytes.
// Destroys the query array at +0x2C (6 entries via ehvec ??_M with the pinned
// element dtor at 0x0045A226) then the StringBase at +0x18 via the pinned
// 0x00036410, then restores the Snapshot base vtable 0x00BBB554. Member order
// (string plus array) drives states 0 plus 1 so teardown reads 1 plus 0
// exactly as retail. Shape follows LargeGroupBonusUpdateModuleDataDtor
// (shared Snapshot base dtor; novtable
// suppresses the entry derived-vtable store retail lacks). Layout follows the
// pinned ctor at 0x0045A2E7 (floats at +8/+0xC/+0x10/+0x14, zero at +0x18,
// bitset reset at +0x1C via rowed 0x0024CA24, array at +0x2C via ehvec ??_L
// with init 0x0045A1D9, bytes at 0x5C-0x5F) and the factory at 0x0024AFE5
// which news 0x60. Called by the ??_G at 0x0045A4FB.

#include "Common/Snapshot.h"

template <typename T>
class StringBase
{
public:
	~StringBase();

private:
	void *m_data;
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();
private:
	unsigned m_unknown;
};

class AutoAbilityQueryEntry
{
public:
	~AutoAbilityQueryEntry();

private:
	int m_state;
	Rva00360D26Member m_filter;
};

class __declspec(novtable) AutoAbilityBehaviorModuleData : public Snapshot
{
public:
	virtual ~AutoAbilityBehaviorModuleData();

private:
	int m_unused04; // +4
	float m_08; // +8
	float m_0C; // +0xC
	float m_10; // +0x10
	float m_14; // +0x14
	StringBase<char> m_str18; // +0x18
	unsigned char m_bitset1C[0x10]; // +0x1C, bitset128 via rowed reset in ctor
	AutoAbilityQueryEntry m_query2C[6]; // +0x2C
	bool m_5C; // +0x5C
	bool m_5D; // +0x5D
	bool m_5E; // +0x5E
	bool m_5F; // +0x5F
};

AutoAbilityBehaviorModuleData::~AutoAbilityBehaviorModuleData()
{
}

// Retail 0x0045A226, 8 bytes. The parent's six-element teardown names
// this destructor; the element ctor independently establishes the filter
// at +4. Its destructor forwards to the matched pool member destructor.
AutoAbilityQueryEntry::~AutoAbilityQueryEntry()
{
}
