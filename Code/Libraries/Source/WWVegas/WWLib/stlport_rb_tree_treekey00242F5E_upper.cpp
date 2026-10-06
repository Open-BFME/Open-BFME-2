// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_upper_bound TreeKey00242F5E set, retail 0x000A7909, 56 bytes.
// Set _M_upper_bound for TreeKey00242F5E (unsigned id at +0 then AsciiString
// at +4) via member comparator Rva000A7AA7Less pinned at 0x000A78A3. Sibling
// of 0x000A78D1 lower_bound in the same TU family. Evidence: callers
// 0x000A7A53 and 0x000A7C2E; neighbours 0x000A78D1 and 0x000A7941.
// The empty member comparator and rowed stdcall provider use the same key pair.
#pragma comment(linker, "/alternatename:??RRva000A7AA7Less@@QBE_NABUTreeKey00242F5E@@0@Z=?Rva000A78A3Less@@YG_NABUTreeKey00242F5E@@0@Z")
#include <set>
class AsciiString { public: AsciiString(const AsciiString &); ~AsciiString(); private: void *m_data; };
struct TreeKey00242F5E { unsigned int m_id; AsciiString m_name; };
struct Rva000A7AA7Less {
    bool operator()(const TreeKey00242F5E &a, const TreeKey00242F5E &b) const;
};
typedef _STL::_Rb_tree<TreeKey00242F5E, TreeKey00242F5E, _STL::_Identity<TreeKey00242F5E>, Rva000A7AA7Less, _STL::allocator<TreeKey00242F5E> > TreeKey00242F5ESetTree;
template TreeKey00242F5ESetTree::_Link_type TreeKey00242F5ESetTree::_M_upper_bound(const TreeKey00242F5ESetTree::key_type &) const;
