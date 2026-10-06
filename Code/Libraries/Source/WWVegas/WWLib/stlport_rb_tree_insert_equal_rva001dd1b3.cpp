// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert_equal@?$_Rb_tree@URva001DD1B3@@U1@U?$_Identity@URva001DD1B3@@@_STL@@U?$less@URva001DD1B3@@@3@V?$allocator@URva001DD1B3@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@URva001DD1B3@@U?$_Nonconst_traits@URva001DD1B3@@@_STL@@@2@ABURva001DD1B3@@@Z @0x001DDA1C 59B
// Rb_tree insert_equal for 36-byte set value: unowned caller of matched _M_insert 0x001DD8EE.
// Evidence: chain lane every callee rowed; single _M_insert call with 0 hint forwards iterator; callers 0x001DDBE7 and 0x001DE3B2.
#define _STLP_NO_EXCEPTIONS 1
#include <set>

struct Rva001DD1B3 {
    unsigned int f00;
    unsigned char m_pad[32];
    Rva001DD1B3(const Rva001DD1B3 &o);
};
inline bool operator<(const Rva001DD1B3 &a, const Rva001DD1B3 &b) { return a.f00 < b.f00; }

typedef _STL::_Rb_tree<Rva001DD1B3, Rva001DD1B3, _STL::_Identity<Rva001DD1B3>, _STL::less<Rva001DD1B3>, _STL::allocator<Rva001DD1B3> > URva001DD1B3SetTree;
template <> URva001DD1B3SetTree::iterator URva001DD1B3SetTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const Rva001DD1B3 &, _STL::_Rb_tree_node_base *);

template URva001DD1B3SetTree::iterator URva001DD1B3SetTree::insert_equal(const Rva001DD1B3 &);
