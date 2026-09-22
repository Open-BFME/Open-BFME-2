// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ??0SpecialPowerModuleData@@QAE@ABV0@@Z at retail 0x005488E9 (95B, not 92:
// the body ends leave plus ret-4). The intermediate SpecialPowerModuleData
// base is 0x18 bytes: vtable 0xC6A520 at +0, a vector member at +4 copied
// through the rowed vector<ScienceType> copy at 0x54878E, and generated id
// words at +0x10/+0x14 fed from the absolute counter at 0x00E05F74 (fresh
// nonzero id, skipping zero). The member element type is proven by the copy
// call: a trivial 4-byte element folds to the rowed ScienceType spelling,
// so no alias pin is needed. (The sibling default-ctor shard models the
// same member as vector<AsciiString>; the default call folds for every
// spelling, so both shards are byte-exact.) The single EH state comes from
// an empty base with declared-only dtor (Topple pattern, zero emitted
// code); without it this toolchain stays frameless. Split TU because the
// default-ctor shard must keep its EH-off flags (makeDirty law).
#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

// Absolute counter at 0x00E05F74; the copy hands out a fresh nonzero id.
extern int g_Va00E05F74;

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class SpecialPowerModuleData : public EmptyBase
{
public:
	SpecialPowerModuleData();
	SpecialPowerModuleData(const SpecialPowerModuleData &other);

private:
	void *m_vtable; // +0
	_STL::vector<ScienceType> m_sciences; // +4
	void *m_unused10; // +0x10
	void *m_unused14; // +0x14
};

// ??0SpecialPowerModuleData@@QAE@ABV0@@Z @0x5488E9
SpecialPowerModuleData::SpecialPowerModuleData(const SpecialPowerModuleData &other)
	: m_vtable(reinterpret_cast<void *>(0x00C6A520))
	, m_sciences(other.m_sciences)
{
	m_unused10 = reinterpret_cast<void *>(++g_Va00E05F74);
	m_unused14 = NULL;
	if (m_unused10 == 0)
		m_unused10 = reinterpret_cast<void *>(++g_Va00E05F74);
}
