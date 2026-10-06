// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002E1FA5@Rva002E1FA5@@QAEXXZ @0x002E1FA5 29B.
// Swap-then-reset: swap maps at +0x29C/+0x2A8 via rowed Rb_tree swap 0x0032AC92
// then tail-jmp to rowed reset 0x002E15E6 on +0x29C. Evidence: same esi for
// both calls proves shared address (union); caller 0x0020F4D9; next shares /O1.
namespace _STL {
template<class T1, class T2> struct pair { T1 first; T2 second; };
template<class T> struct _Select1st {};
template<class T> struct less {};
template<class T> class allocator {};
template<class K, class V, class KoV, class Cmp, class Alloc>
class _Rb_tree {
public:
	void swap(_Rb_tree &other);
	char m_pad[12];
};
}
typedef _STL::pair<const int, int> P002E1FA5;
typedef _STL::_Rb_tree<int, P002E1FA5, _STL::_Select1st<P002E1FA5>, _STL::less<int>, _STL::allocator<P002E1FA5> > Tree002E1FA5;
class Rva002E15E6 {
public:
	void rva002E15E6();
};
class Rva002E1FA5 {
public:
	void rva002E1FA5();
private:
	char m_pad[0x29C];
	union {
		Tree002E1FA5 m_tree1;
		Rva002E15E6 m_rst;
	};
	Tree002E1FA5 m_tree2;
};
void Rva002E1FA5::rva002E1FA5()
{
	m_tree1.swap(m_tree2);
	return m_rst.rva002E15E6();
}
