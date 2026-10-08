// ??$__unguarded_linear_insert@PAUTreeHintRef00217D4C@@U1@URva004F9185Cmp@@@_STL@@YAXPAUTreeHintRef00217D4C@@U1@URva004F9185Cmp@@@Z
// partial score=0.6 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB
//
// ??$sort@PAUTreeHintRef00217D4C@@URva004F9185Cmp@@@_STL@@YAXPAUTreeHintRef00217D4C@@0URva004F9185Cmp@@@Z, retail 0x004f9565, 67 bytes. Banked partial (score 0.6) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
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
	const TargetRef00217D4C *m_ptr;
	ConstTreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) { if (m_ptr) ++((TargetRef00217D4C *)m_ptr)->references; }
	__forceinline ~ConstTreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); }
};
struct Rva004F9185Cmp
{
	__forceinline bool operator()(const ConstTreeHintRef00217D4C &a, const ConstTreeHintRef00217D4C &b) const { int ka = a.m_ptr->m_08->m_key; int kb = b.m_ptr->m_08->m_key; return ka > kb; }
};
template void _STL::sort<TreeHintRef00217D4C *, Rva004F9185Cmp>(TreeHintRef00217D4C *, TreeHintRef00217D4C *, Rva004F9185Cmp);
