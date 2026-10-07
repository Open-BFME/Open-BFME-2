// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?rva0021BC2C@Rva0021BC2C@@QAEHH@Z @0x0021BC2C 39B
// Member count-or-zero: runs the rowed-pending map-find 0x00388F63 on
// this+0x24 with &arg, then when its result differs from this+0x24 answers
// ([result+0x18]-[result+0x14])>>2 else 0. Evidence: retail lea-esi
// this+0x24 lea-eax-&arg push mov-ecx-esi call; mov-ecx-eax cmp-ecx-[esi]
// pop-esi je-xor else mov-eax-[ecx+0x18] sub-eax-[ecx+0x14] sar-2 ret-4
// (int, one int arg). Map/vector identities unproven (address-derived).
class Rva0021BC2C;
class Rva0021DE75;

namespace _STL
{
template <class A, class B> struct pair;
template <class T> struct _Rb_tree_node;
template <class T> struct _Select1st;
template <class T> struct less;
template <class T> class allocator;
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
private:
	template <class SearchKey>
	_Rb_tree_node<Value> *_M_find(const SearchKey &key) const;
	friend class ::Rva0021BC2C;
	friend class ::Rva0021DE75;
};
}

typedef _STL::pair<const int, int> Rva0021MapValue;
typedef _STL::_Rb_tree_node<Rva0021MapValue> Rva0021MapNode;
typedef _STL::_Rb_tree<int, Rva0021MapValue, _STL::_Select1st<Rva0021MapValue>, _STL::less<int>, _STL::allocator<Rva0021MapValue> > Rva0021MapTree;

struct Rva0021BC2CVec
{
	char m_pad[0x14];
	int m_14;
	int m_18;
};



class Rva0021BC2C
{
public:
	int rva0021BC2C(int a1);

private:
	char m_pad[0x24];
};

int Rva0021BC2C::rva0021BC2C(int a1)
{
	void *table = (char *)this + 0x24;
	void *found = (void *)((Rva0021MapTree *)table)->_M_find(a1);
	// Retail falls through to the hit (mov/sub/sar) and jumps to the miss
	// (xor), so test for hit (!=) with the compute inside.
	if (found != *(void **)table) {
		Rva0021BC2CVec *v = (Rva0021BC2CVec *)found;
		return (v->m_18 - v->m_14) >> 2;
	}
	return 0;
}
