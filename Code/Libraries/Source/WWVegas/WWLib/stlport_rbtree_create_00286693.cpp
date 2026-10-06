// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Honest opaque tree for retail 0x00286693 34B: node 0x24 plus _Construct Rva00285BEC at +0x10. Evidence: caller _M_insert 0x0028688A plus rowed allocate 0x000307F0 plus rowed _Construct 0x0028625D plus Rva00285672 compare 0x00285672. Key 16B plus mapped 4B matches Rva00285BEC 20B layout with two-vptr lead.
#include <map>

struct TreeKey00286693
{
	int a[4];
	bool operator<(const TreeKey00286693 &o) const { return a[0] < o.a[0]; }
};

struct TreeMapped00286693
{
	int a[1];
};

typedef _STL::pair<const TreeKey00286693, TreeMapped00286693> TreePair00286693;
typedef _STL::_Rb_tree<TreeKey00286693, TreePair00286693, _STL::_Select1st<TreePair00286693>, _STL::less<TreeKey00286693>, _STL::allocator<TreePair00286693> > Tree00286693;

class Rva00285BEC
{
public:
	Rva00285BEC(const Rva00285BEC &other);
};

namespace _STL
{
template <> void _Construct<Rva00285BEC, Rva00285BEC>(Rva00285BEC *p, const Rva00285BEC &x);
}

template <>
_STL::_Rb_tree<TreeKey00286693, TreePair00286693, _STL::_Select1st<TreePair00286693>, _STL::less<TreeKey00286693>, _STL::allocator<TreePair00286693> >::_Link_type _STL::_Rb_tree<TreeKey00286693, TreePair00286693, _STL::_Select1st<TreePair00286693>, _STL::less<TreeKey00286693>, _STL::allocator<TreePair00286693> >::_M_create_node(const TreePair00286693 &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreePair00286693>), 0);
	_STL::_Construct((Rva00285BEC *)((char *)node + 0x10), *(const Rva00285BEC *)(const void *)&value);
	return node;
}

// Explicit instantiation of only this member so the specialization above is
// emitted without dragging whole-class COMDATs (_S_minimum/_S_maximum/iterator).
template Tree00286693::_Link_type Tree00286693::_M_create_node(const TreePair00286693 &);
