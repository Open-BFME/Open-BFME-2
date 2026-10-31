// cl: /O1 /arch:SSE /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?_M_insert@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@UBfmeStringNoCaseLess@@V?$allocator@VAsciiString@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@VAsciiString@@U?$_Nonconst_traits@VAsciiString@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABVAsciiString@@0@Z @0x0002C686 149B
// _M_insert for the nocase AsciiString set (INI macro map family).
// Evidence: unowned retail caller of the set _M_create_node at 0x0002C552;
// key compare calls the matched nocase less at 0x0002C63C; rebalances via
// rowed 0x00025490; caller is the set insert_unique at 0x0002C908.
// Precedent: stlport_set_record_001dd3bc_insert.cpp (148B set _M_insert).
#pragma inline_depth(3)
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_BFME_LOWER_BOUND_EXTERN  // bind the prime-list search to its shared retail provider
// STLport frees through the game's plain _free at 0x00030830, not the CRT import.
#define free BfmeCrtImportedFree
#include <stdlib.h>
#include <malloc.h>
#undef free
extern "C" void __cdecl free(void *) throw(...);
#include "ascii_string.h"
#include <set>
#include <memory>

struct BfmeStringNoCaseLess
{
public:
	bool operator()(const AsciiString &a, const AsciiString &b) const;
};

// Node storage comes straight from the byte allocator; this file keeps no copy of the forwarder.
namespace _STL {
template <> __declspec(dllimport) __forceinline _Rb_tree_node<AsciiString> *
_STLP_alloc_proxy<_Rb_tree_node<AsciiString> *, _Rb_tree_node<AsciiString>, allocator<_Rb_tree_node<AsciiString> > >::allocate(size_t count)
{
    return reinterpret_cast<_Rb_tree_node<AsciiString> *>(allocator<char>::allocate(count * sizeof(_Rb_tree_node<AsciiString>), 0));
}
}

// Retail's range destroy calls the out-of-line destructor 0x0048BA39 for each
// string, so its first instantiation expands the helpers but not the destructor.
namespace _STL {
template <> __declspec(dllimport) __forceinline void _Destroy<AsciiString>(AsciiString *pointer)
{
    pointer->AsciiString::~AsciiString();
}
#pragma inline_depth(3)
template void _Destroy<AsciiString *>(AsciiString *, AsciiString *);
#pragma inline_depth()
}

#pragma inline_depth(3)
typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > NoCaseSetTree;

template NoCaseSetTree::iterator NoCaseSetTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const AsciiString &, _STL::_Rb_tree_node_base *);
template _STL::pair<NoCaseSetTree::iterator, bool> NoCaseSetTree::insert_unique(const AsciiString &);
typedef _STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > NoCaseStringSet;
template _STL::pair<NoCaseStringSet::iterator, bool> NoCaseStringSet::insert(const AsciiString &);
