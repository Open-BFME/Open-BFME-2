// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
//
// ??$sort@PAUTreeHintRef00217D4C@@URva004F9185Cmp@@@_STL@@YAXPAUTreeHintRef00217D4C@@0URva004F9185Cmp@@@Z, retail 0x004f9565, 67 bytes. Banked partial (score 0.6) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
//
// Comparator shape (target evidence): retail __push_heap 0x004F6789 keeps
// conditional-destruction flags for both comparator arguments inside its &&
// and stores the EH state right after each argument is built, so the
// comparator takes const references to a second handle type that converts
// from TreeHintRef00217D4C, and each call builds caller-owned temporaries.
// The handle types' original names are unknown. operator= is the matched
// 0x002174A4 body; giving it a visible body (noinline) is what keeps swap's
// copy in esi across both assignments (retail swap 0x004F6542).
#pragma optimize("t", on)
#include <stl/_algobase.h>
#pragma optimize("", on)
#include <algorithm>
struct Key004F9185 { int _00[3]; int m_key; };
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; Key004F9185 *m_08; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) { if (m_ptr) ++m_ptr->references; }
	__declspec(noinline) TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other) { if (this != &other) { if (other.m_ptr) ++other.m_ptr->references; if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); m_ptr = other.m_ptr; } return *this; }
	__forceinline ~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct ConstTreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	ConstTreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) { if (m_ptr) ++m_ptr->references; }
	__forceinline ~ConstTreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct Rva004F9185Cmp
{
	__forceinline bool operator()(const ConstTreeHintRef00217D4C &a, const ConstTreeHintRef00217D4C &b) const { int ka = a.m_ptr->m_08->m_key; int kb = b.m_ptr->m_08->m_key; return ka > kb; }
};
template void _STL::sort<TreeHintRef00217D4C *, Rva004F9185Cmp>(TreeHintRef00217D4C *, TreeHintRef00217D4C *, Rva004F9185Cmp);
