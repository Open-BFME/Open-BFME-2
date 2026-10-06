// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva00282FE0CreateNode@@YGPAXPBX@Z, RVA 0x00282FE0, 34 bytes.
// List node creator allocating 12 via rowed byte allocator 0x000307F0 then
// constructing list<Coord3D> value at +8 via rowed _Construct 0x00282843.
// Evidence: caller 0x00283405 links node into outer list; callees all rowed;
// ret-4 stdcall shape matches sibling create 0x00568D95 34B.
#include <memory>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


namespace _STL {
template <> class allocator<char> {
public:
	static char *allocate(unsigned int bytes, const void *hint);
};
}

struct Coord3D {
	int m_pad;
};

typedef _STL::list<Coord3D> CoordList;

struct ListNode {
	void *m_next;
	void *m_prev;
	CoordList m_val;
};

void *__stdcall Rva00282FE0CreateNode(const void *src)
{
	ListNode *node = (ListNode *)_STL::allocator<char>::allocate(12, 0);
	_STL::_Construct(&node->m_val, *(const CoordList *)src);
	return node;
}
