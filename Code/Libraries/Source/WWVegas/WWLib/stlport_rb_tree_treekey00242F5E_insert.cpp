// ?_M_insert@?$_Rb_tree@UTreeKey00242F5E@@U1@U?$_Identity@UTreeKey00242F5E@@@_STL@@URva000A7AA7Less@@V?$allocator@UTreeKey00242F5E@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@UTreeKey00242F5E@@U?$_Nonconst_traits@UTreeKey00242F5E@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABUTreeKey00242F5E@@0@Z @ 0x000A7AA7 (149B).
// Set _M_insert for TreeKey00242F5E (unsigned id at +0 then AsciiString at +4).
// Retail lea ecx,[edi+8] before the 0x000A78A3 call proves a thiscall member
// comparator, twin of the rowed stdcall free ?Rva000A78A3Less@@YG at the same
// address (member ignores this, same unsigned jae/jbe plus rowed AsciiString
// less 0x0005598C). Create-node is the member twin at 0x000A799B (same 8B value
// same allocate plus rowed _Construct 0x000A7876). Rebalance rowed 0x00025490.
// Precedent: stlport_rb_tree_BfmeStringRecord004071F7_insert.cpp (149B via
// out-of-line nocase compare plus pinned twins). Caller 0x000A7C50 is the
// single-arg insert_unique for the same tree.
// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include <set>
class AsciiString { public: AsciiString(const AsciiString &); ~AsciiString(); private: void *m_data; };
struct TreeKey00242F5E { unsigned int m_id; AsciiString m_name; };
struct Rva000A7AA7Less {
    bool operator()(const TreeKey00242F5E &a, const TreeKey00242F5E &b) const;
};
typedef _STL::_Rb_tree<TreeKey00242F5E, TreeKey00242F5E, _STL::_Identity<TreeKey00242F5E>, Rva000A7AA7Less, _STL::allocator<TreeKey00242F5E> > TreeKey00242F5ESetTree;
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
template _STL::pair<TreeKey00242F5ESetTree::iterator, bool> TreeKey00242F5ESetTree::insert_unique(const TreeKey00242F5ESetTree::value_type &);
typedef _STL::set<TreeKey00242F5E, Rva000A7AA7Less, _STL::allocator<TreeKey00242F5E> > TreeKey00242F5ESet;
template _STL::pair<TreeKey00242F5ESet::iterator, bool> TreeKey00242F5ESet::insert(const TreeKey00242F5ESet::value_type &);

class Rva000A7BB5
{
public:
	~Rva000A7BB5();
};

class Rva000A79CE
{
public:
	~Rva000A79CE();
};

class Rva000A7CE9
{
public:
	void rva000A7CE9();
};

void Rva000A7CE9::rva000A7CE9()
{
	((Rva000A7BB5 *)this)->~Rva000A7BB5();
}

class Rva000A7CEE
{
public:
	void rva000A7CEE();
};

void Rva000A7CEE::rva000A7CEE()
{
	((Rva000A79CE *)this)->~Rva000A79CE();
}

