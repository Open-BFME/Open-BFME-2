// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?rva0021DE75@Rva0021DE75@@QAEPAXPAX@Z @0x0021DE75 56B
// Member find-or-create: derefs the handle, runs rowed-pending map-find
// 0x00388F63 on this+0x54 with &deref, answers it when it differs from
// [this+0x54]; else runs rowed-pending 0x0021DAA8 on this+0x54 with
// (&deref, orig) then rowed-pending 0x002191FE on its result and answers
// that. Evidence: retail mov-edi-[ebp+8] mov-eax-[edi] mov-[ebp+8]-eax
// lea-esi-[ecx+0x54] lea-eax-[ebp+8] push mov-ecx-esi call plus
// cmp-eax-[esi] jne-return-found else push-edi lea-eax-[ebp+8] push
// mov-ecx-esi call mov-ecx-eax call; pop-edi-esi-ebp ret-4 (one handle).
// Handles opaque; callees unproven (address-derived).


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

class Rva0021DE75Table
{
public:
	void *rva0021DAA8(void *a1, void *a2);
};

class Rva002191FEHost
{
public:
	void *rva002191FE();
};

class Rva0021DE75
{
public:
	void *rva0021DE75(void *a1);

private:
	char m_pad[0x54];
};

void *Rva0021DE75::rva0021DE75(void *a1)
{
	void *deref = *(void **)a1;
	Rva0021DE75Table *table = (Rva0021DE75Table *)((char *)this + 0x54);
	void *found = (void *)((Rva0021MapTree *)table)->_M_find((const int &)deref);
	if (found != *(void **)table)
		return found;
	// Retail pushes orig-a1 first (&deref second): arg1=&deref, arg2=a1.
	void *r = table->rva0021DAA8(&deref, a1);
	return ((Rva002191FEHost *)r)->rva002191FE();
}
