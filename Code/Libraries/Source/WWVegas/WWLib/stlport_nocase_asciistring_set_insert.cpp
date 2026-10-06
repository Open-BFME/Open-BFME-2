// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_insert@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@UBfmeStringNoCaseLess@@V?$allocator@VAsciiString@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@VAsciiString@@U?$_Nonconst_traits@VAsciiString@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABVAsciiString@@0@Z @0x0002C686 149B
// _M_insert for the nocase AsciiString set (INI macro map family).
// Evidence: unowned retail caller of the set _M_create_node at 0x0002C552;
// key compare calls the matched nocase less at 0x0002C63C; rebalances via
// rowed 0x00025490; caller is the set insert_unique at 0x0002C908.
// Precedent: stlport_set_record_001dd3bc_insert.cpp (148B set _M_insert).
#define _STLP_NO_EXCEPTIONS 1
#include <set>

#include "ascii_string.h"

struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &a, const AsciiString &b) const;
};

typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > NoCaseSetTree;
template <> NoCaseSetTree::_Link_type NoCaseSetTree::_M_create_node(const AsciiString &);

template NoCaseSetTree::iterator NoCaseSetTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const AsciiString &, _STL::_Rb_tree_node_base *);
template _STL::pair<NoCaseSetTree::iterator, bool> NoCaseSetTree::insert_unique(const AsciiString &);
typedef _STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > NoCaseStringSet;
template _STL::pair<NoCaseStringSet::iterator, bool> NoCaseStringSet::insert(const AsciiString &);
