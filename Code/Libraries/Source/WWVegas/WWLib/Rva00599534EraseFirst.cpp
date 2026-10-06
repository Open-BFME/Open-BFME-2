// cl: /GX-
// stlport
// ?rva00599534@Rva00599534@@QAEXH@Z @0x00599534 48B: list<int> at +4 erase first match via rowed erase 0x00438539; callers 0x004EC911 and 0x004EC055
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class Rva00599534
{
public:
	void rva00599534(int val);
private:
	char m_pad[4];
	_STL::list<int, _STL::allocator<int> > m_list;
};

void Rva00599534::rva00599534(int val)
{
	for (_STL::list<int, _STL::allocator<int> >::iterator it = m_list.begin(); it != m_list.end(); ++it) {
		if (*it == val) {
			m_list.erase(it);
			break;
		}
	}
}
