// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva004DF3F8@Rva004DF3F8@@QAEXPAX@Z @0x004DF3F8 32B: list BfmePod12 remove by int at +0x74 via rowed remove; caller jmp at 0x0028BC21 unblocks 0x0028BC17; this list at +0x24
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


struct BfmePod12
{
	int a[3];
};

inline bool operator==(const BfmePod12 &x, const BfmePod12 &y) { return x.a[0] == y.a[0]; }
// Retail erase(iterator) relinks the node onto the freelist pool head inline
// (pool at VA 0x00DA60E8, head at +0x08; retail 0x002ABB20).
class FreelistPool { public: void *pop(); int m_00; void *m_04; void *m_head; };
extern FreelistPool g_freelistPool;
namespace _STL {
template <> list<BfmePod12>::iterator list<BfmePod12>::erase(iterator __position)
{
	_List_node_base *__prev_node = __position._M_node->_M_prev;
	_List_node_base *__next_node = __position._M_node->_M_next;
	__prev_node->_M_next = __next_node;
	__next_node->_M_prev = __prev_node;
	*(void **)__position._M_node = g_freelistPool.m_head;
	g_freelistPool.m_head = __position._M_node;
	return iterator((_List_node<BfmePod12> *)__next_node);
}
}

struct Rva004DF3F8Arg
{
	char m_pad00[0x74];
	int m_74;
};

class Rva004DF3F8
{
public:
	void rva004DF3F8(void *p);
private:
	char m_pad00[0x24];
	_STL::list<BfmePod12> m_24;
};

void Rva004DF3F8::rva004DF3F8(void *p)
{
	if (p == 0)
		return;
	int key = ((Rva004DF3F8Arg *)p)->m_74;
	m_24.remove(*(const BfmePod12 *)&key);
}
