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
#include <stl/_algobase.h>
#include <algorithm>
struct Key004F9185 { int _00[3]; int m_key; };
#include "../../Apt/AptRefTarget.h"
// These referents carry their key object at +0x08.
struct KeyedTarget004F9185 : TargetRef00217D4C { const Key004F9185*key()const{return m_08;} Key004F9185 *m_08; };
inline __declspec(noinline) TreeHintRef00217D4C &TreeHintRef00217D4C::operator=(const TreeHintRef00217D4C &other) { if (this != &other) { if (other.m_ptr) ++other.m_ptr->references; if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); m_ptr = other.m_ptr; } return *this; }
__forceinline TreeHintRef00217D4C::~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
struct ConstTreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	ConstTreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) { if (m_ptr) ++m_ptr->references; }
	__forceinline ~ConstTreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct Rva004F9185Cmp
{
	__forceinline bool operator()(const ConstTreeHintRef00217D4C &a, const ConstTreeHintRef00217D4C &b) const { int ka = static_cast<const KeyedTarget004F9185 *>(a.m_ptr)->key()->m_key; int kb = static_cast<const KeyedTarget004F9185 *>(b.m_ptr)->key()->m_key; return ka > kb; }
};
// Native4F6590..4F6628,152B. STLport _algo.c unguarded insertion with
// the established converting-handle comparison and owning-reference ABI.
// The volatile cursor constrains compiler reloads to retail's stack home;
// it is not evidence of an original volatile qualifier or concurrent access.
// copy_backward<TreeHintRef00217D4C *> is rowed at 0x004F6FE1 in
// StlSweepW5Rva004F6FE1.cpp; declaration-only so __merge_backward calls that
// body and this TU emits no second (non-retail) copy.
namespace _STL {
template <> TreeHintRef00217D4C *copy_backward<TreeHintRef00217D4C *, TreeHintRef00217D4C *>(
	TreeHintRef00217D4C *, TreeHintRef00217D4C *, TreeHintRef00217D4C *);
}
namespace _STL {
template<> void __unguarded_linear_insert<TreeHintRef00217D4C *,TreeHintRef00217D4C,Rva004F9185Cmp>(TreeHintRef00217D4C *last,TreeHintRef00217D4C value,Rva004F9185Cmp cmp) {
 TreeHintRef00217D4C *volatile next=last-1;
 while(cmp(value,*next)) {
  *last=*next;
  last=next;
  --next;
 }
 *last=value;
}
}
template void _STL::sort<TreeHintRef00217D4C *, Rva004F9185Cmp>(TreeHintRef00217D4C *, TreeHintRef00217D4C *, Rva004F9185Cmp);

// Native 4F6657..4F66F0 and 4F66F0..4F6789: integer payload bounds,
// the same two owning comparator temporaries as this sort family.
// A const key accessor preserves native half-count EDI and right-handle ESI.
template TreeHintRef00217D4C *_STL::__lower_bound(TreeHintRef00217D4C *,TreeHintRef00217D4C *,const TreeHintRef00217D4C &,Rva004F9185Cmp,int *);
template TreeHintRef00217D4C *_STL::__upper_bound(TreeHintRef00217D4C *,TreeHintRef00217D4C *,const TreeHintRef00217D4C &,Rva004F9185Cmp,int *);

// Native 4F74A1..4F75F2, 337B: the random-access gcd __rotate (_algo.c),
// reached from the 0x4F7A28 dispatcher; copy ctor inline, assignment the
// out-of-line 0x2174A4 worker, swap_ranges the 0x4F6FFC body.
template TreeHintRef00217D4C *_STL::__rotate(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,int *,TreeHintRef00217D4C *);

// Native 4F840B..4F853A, 303B: stable_sort's buffer-less merge (_algo.c);
// the comparator and both owning handle temporaries inline into the
// two-element case, swap is the rowed 0x4F6542.
template void _STL::__merge_without_buffer(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,int,int,Rva004F9185Cmp);

// Native 4F792B..4F7A0F, 228B: __merge_backward (_algo.c) of the adaptive
// merge, inlined key compare, copy_backward the 0x4F6FE1 body.
template TreeHintRef00217D4C *_STL::__merge_backward(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,Rva004F9185Cmp);
