// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_insert@?$_Rb_tree@VRva00064640Record@@V1@U?$_Identity@VRva00064640Record@@@_STL@@U?$less@VRva00064640Record@@@3@V?$allocator@VRva00064640Record@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@VRva00064640Record@@U?$_Nonconst_traits@VRva00064640Record@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABVRva00064640Record@@0@Z 0x005041F6 137B evidence: unlock Rb_tree insert via rowed create 0x005041B6 plus Rebalance; caller 0x0050456D unblocks 0x00504509; siblings Rva00500500Insert same recipe
#include <set>
class Rva00064640Record
{
public:
	bool operator<(const Rva00064640Record &other) const { return m_18 < other.m_18; }
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	float m_14;
	unsigned int m_18;
};
typedef _STL::_Rb_tree<Rva00064640Record, Rva00064640Record, _STL::_Identity<Rva00064640Record>, _STL::less<Rva00064640Record>, _STL::allocator<Rva00064640Record> > VRva00064640RecordSetTree;
// Declared-only: calls reach the retail-identical _M_create_node in
// stlport_rb_tree_create_nodes.cpp, dropping our wrong COMDAT copies of
// _M_create_node, _Construct and __malloc_alloc::allocate.
template <>
VRva00064640RecordSetTree::_Link_type VRva00064640RecordSetTree::_M_create_node(const VRva00064640RecordSetTree::value_type &);
template VRva00064640RecordSetTree::iterator VRva00064640RecordSetTree::insert_equal(const VRva00064640RecordSetTree::value_type &);
template VRva00064640RecordSetTree::iterator VRva00064640RecordSetTree::insert_equal(VRva00064640RecordSetTree::iterator, const VRva00064640RecordSetTree::value_type &);
template _STL::pair<VRva00064640RecordSetTree::iterator, bool> VRva00064640RecordSetTree::insert_unique(const VRva00064640RecordSetTree::value_type &);
template VRva00064640RecordSetTree::iterator VRva00064640RecordSetTree::insert_unique(VRva00064640RecordSetTree::iterator, const VRva00064640RecordSetTree::value_type &);
typedef _STL::set<Rva00064640Record, _STL::less<Rva00064640Record>, _STL::allocator<Rva00064640Record> > Rva00064640Set;
template _STL::pair<Rva00064640Set::iterator, bool> Rva00064640Set::insert(const Rva00064640Set::value_type &);
struct Rva005045C6
{
	void rva005045C6(const Rva00064640Record &v);
	Rva00064640Set m_set;
};
void Rva005045C6::rva005045C6(const Rva00064640Record &v)
{
	m_set.insert(v);
}
