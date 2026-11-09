// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0041573F@@QAE@ABV0@@Z @0x0041573F 67B
// Honest Rva copy ctor: BfmeOwnedRecordArray56 at +0 via rowed copy 0x004151A3
// plus _Rb_tree900 at +0x1C0 via rowed copy 0x0041559E. Declared Array56 dtor
// reproduces the retail EH state. Flags copied from sibling OwnedRecord900TreeCopy.cpp.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <map>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../Include/Common/Rva002390CB.h"
struct BfmeStringRecord002CF550 {
	~BfmeStringRecord002CF550();
	AsciiString text;
	Rva002390CB ref;
};
bool operator<(const BfmeStringRecord002CF550 &l, const BfmeStringRecord002CF550 &r);
namespace _STL { template <> struct less<BfmeStringRecord002CF550> { bool operator()(const BfmeStringRecord002CF550 &l, const BfmeStringRecord002CF550 &r) const; }; }
typedef _STL::_Rb_tree<BfmeStringRecord002CF550, BfmeStringRecord002CF550, _STL::_Identity<BfmeStringRecord002CF550>, _STL::less<BfmeStringRecord002CF550>, _STL::allocator<BfmeStringRecord002CF550> > Tree900;
class BfmeOwnedRecordArray56 {
	char m_data[0x1C0];
public:
	BfmeOwnedRecordArray56(const BfmeOwnedRecordArray56 &o);
	~BfmeOwnedRecordArray56();
};
class Rva0041573F {
public:
	Rva0041573F(const Rva0041573F &src);
	~Rva0041573F();
private:
	BfmeOwnedRecordArray56 m_arr;
	Tree900 m_tree;
};
Rva0041573F::Rva0041573F(const Rva0041573F &src)
	: m_arr(src.m_arr)
	, m_tree(src.m_tree)
{
}

class Rva0041579E {
public:
	Rva0041579E(const Rva0041579E &src);
	~Rva0041579E();
private:
	int m_00;
	Rva0041573F m_04;
};
Rva0041579E::Rva0041579E(const Rva0041579E &src)
	: m_00(src.m_00)
	, m_04(src.m_04)
{
}

Rva0041579E::~Rva0041579E()
{
}
