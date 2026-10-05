// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ??0GroupOrder@@QAE@ABV0@@Z at retail 0x005488E9 (95B, not 92:
// the body ends leave plus ret-4). The intermediate GroupOrder
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
extern "C" const void *const vtbl_00C6A520[];  // ??_7GroupOrder@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6A520=??_7GroupOrder@@6B@")

#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

// Absolute counter at 0x00E05F74; the copy hands out a fresh nonzero id.
extern int g_Va00E05F74;
// g_Va00E05F74: matched references place it at VA 0xe05f74 (zero-filled .bss).
int g_Va00E05F74;

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class GroupOrder : public EmptyBase
{
public:
	GroupOrder();
	GroupOrder(const GroupOrder &other);

private:
	void *m_vtable; // +0
	_STL::vector<ScienceType> m_sciences; // +4
	void *m_unused10; // +0x10
	void *m_unused14; // +0x14
};

// ??0GroupOrder@@QAE@ABV0@@Z @0x5488E9
GroupOrder::GroupOrder(const GroupOrder &other)
	: m_vtable(reinterpret_cast<void *>(((unsigned int)vtbl_00C6A520)))
	, m_sciences(other.m_sciences)
{
	m_unused10 = reinterpret_cast<void *>(++g_Va00E05F74);
	m_unused14 = NULL;
	if (m_unused10 == 0)
		m_unused10 = reinterpret_cast<void *>(++g_Va00E05F74);
}
