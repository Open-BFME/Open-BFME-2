// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS
// stlport


#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include "unicode_string.h"

// Retail copies each string through its matching narrow or wide StringBase body.
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

// LadderPreferences::loadProfile fills these same offsets; the names agree
// with the upstream Common/LadderPreferences.h record and its time_t map key.
class LadderPref
{
public:
    LadderPref() {}
    __declspec(noinline) LadderPref(const LadderPref &source);
    ~LadderPref();

    UnicodeString name;
    AsciiString address;
    unsigned short port;
    long lastPlayDate;
};

// Retail's map subscript (0x005E017A) builds the default LadderPref with T(),
// not through an out-of-line __default_constructed call.
#include <utility>
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(T) T()
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<long, pair<long const, LadderPref>, _Select1st<pair<long const, LadderPref> >, less<long>, allocator<pair<long const, LadderPref> > >::~_Rb_tree(); }
// bfme link decl-only end

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

// Retail builds no copy or assignment of this map: the copy ctor once rowed here is the record tree's below.
namespace _STL {
template <> map<long, LadderPref, _STL::less<long>, _STL::allocator<_STL::pair<const long, LadderPref> > >::map(const map<long, LadderPref, _STL::less<long>, _STL::allocator<_STL::pair<const long, LadderPref> > > &);
template <> map<long, LadderPref, _STL::less<long>, _STL::allocator<_STL::pair<const long, LadderPref> > > &map<long, LadderPref, _STL::less<long>, _STL::allocator<_STL::pair<const long, LadderPref> > >::operator=(const map<long, LadderPref, _STL::less<long>, _STL::allocator<_STL::pair<const long, LadderPref> > > &);
}

template class _STL::map<long, LadderPref, _STL::less<long>, _STL::allocator<_STL::pair<const long, LadderPref> > >;

// 0x0021DBBA, the member at +0x54 of the hero sub-class record (Rva0021E85ACopy.cpp).
#include <set>
#include "BfmeStringRecord00219B0B.h"
struct BfmeStringRecord0021A940
{
	unsigned int word0;
	BfmeStringRecord00219B0B rec;
	BfmeStringRecord0021A940(const BfmeStringRecord0021A940 &source);
	~BfmeStringRecord0021A940();
};
typedef _STL::_Rb_tree<BfmeStringRecord0021A940, BfmeStringRecord0021A940, _STL::_Identity<BfmeStringRecord0021A940>, _STL::less<BfmeStringRecord0021A940>, _STL::allocator<BfmeStringRecord0021A940> > Rva0021E85ARecordTree;
namespace _STL {
template <> Rva0021E85ARecordTree::_Link_type Rva0021E85ARecordTree::_M_copy(Rva0021E85ARecordTree::_Link_type, Rva0021E85ARecordTree::_Link_type);
template <> void Rva0021E85ARecordTree::_M_erase(Rva0021E85ARecordTree::_Link_type);
}
template Rva0021E85ARecordTree::_Rb_tree(const Rva0021E85ARecordTree &);
