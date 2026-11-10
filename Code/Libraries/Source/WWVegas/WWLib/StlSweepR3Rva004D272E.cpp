// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}



struct Rva004D272ERecord {  char bytes[1]; };


// Instantiate the recovered member; retain only its required template dependencies.
// Declared only (stl batch): retail's body for this name is the rowed one at its
// pinned address; this TU's copy is not retail's.
namespace _STL { template <> _STL::_Rb_tree_iterator<_STL::pair<int const,Rva004D272ERecord>,_STL::_Nonconst_traits<_STL::pair<int const,Rva004D272ERecord> > > _Rb_tree<int,_STL::pair<int const,Rva004D272ERecord>,_STL::_Select1st<_STL::pair<int const,Rva004D272ERecord> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,Rva004D272ERecord> > >::insert_unique(_STL::_Rb_tree_iterator<_STL::pair<int const,Rva004D272ERecord>,_STL::_Nonconst_traits<_STL::pair<int const,Rva004D272ERecord> > >,_STL::pair<int const,Rva004D272ERecord> const &); }
template _STL::_Rb_tree_iterator<_STL::pair<int const, Rva004D272ERecord>, _STL::_Nonconst_traits<_STL::pair<int const, Rva004D272ERecord> > > _STL::map<int, Rva004D272ERecord, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva004D272ERecord> > >::insert(_STL::_Rb_tree_iterator<_STL::pair<int const, Rva004D272ERecord>, _STL::_Nonconst_traits<_STL::pair<int const, Rva004D272ERecord> > >, _STL::pair<int const, Rva004D272ERecord> const &);

// The declared helper binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:?insert_unique@?$_Rb_tree@HU?$pair@$$CBHURva004D272ERecord@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva004D272ERecord@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva004D272ERecord@@@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHURva004D272ERecord@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva004D272ERecord@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHURva004D272ERecord@@@2@@Z=?insert_unique@?$_Rb_tree@UBfmeStringRecord004D05B8@@U1@U?$_Identity@UBfmeStringRecord004D05B8@@@_STL@@U?$less@UBfmeStringRecord004D05B8@@@3@V?$allocator@UBfmeStringRecord004D05B8@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@UBfmeStringRecord004D05B8@@U?$_Nonconst_traits@UBfmeStringRecord004D05B8@@@_STL@@@2@U32@ABUBfmeStringRecord004D05B8@@@Z")
