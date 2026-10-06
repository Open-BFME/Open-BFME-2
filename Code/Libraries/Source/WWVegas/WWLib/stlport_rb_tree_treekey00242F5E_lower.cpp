// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_lower_bound TreeKey00242F5E set, retail 0x000A78D1, 56 bytes.
// Set _M_lower_bound for TreeKey00242F5E (unsigned id at +0 then AsciiString
// at +4) via member comparator Rva000A7AA7Less pinned at 0x000A78A3. Same
// shape as 0x00448D65. Evidence: callers 0x000A7A3F and 0x000A7C3B; neighbours
// 0x000A78A3 Less and 0x000A799B create_node share the same tree.
// The empty member comparator and rowed stdcall provider use the same key pair.
#pragma comment(linker, "/alternatename:??RRva000A7AA7Less@@QBE_NABUTreeKey00242F5E@@0@Z=?Rva000A78A3Less@@YG_NABUTreeKey00242F5E@@0@Z")
#include <set>
class AsciiString { public: AsciiString(const AsciiString &); ~AsciiString(); private: void *m_data; };
struct TreeKey00242F5E { unsigned int m_id; AsciiString m_name; };
struct Rva000A7AA7Less {
    bool operator()(const TreeKey00242F5E &a, const TreeKey00242F5E &b) const;
};
typedef _STL::_Rb_tree<TreeKey00242F5E, TreeKey00242F5E, _STL::_Identity<TreeKey00242F5E>, Rva000A7AA7Less, _STL::allocator<TreeKey00242F5E> > TreeKey00242F5ESetTree;
template TreeKey00242F5ESetTree::_Link_type TreeKey00242F5ESetTree::_M_lower_bound(const TreeKey00242F5ESetTree::key_type &) const;
