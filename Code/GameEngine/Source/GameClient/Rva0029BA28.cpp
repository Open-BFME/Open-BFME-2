// cl: /DNDEBUG /MD /EHsc
// stlport
// ?rva0029BA28@Rva0029BA28@@QAEXH@Z @0x0029BA28 48B leaf called from 0x0029FEA5 list<int> at +0x18 erase first match via rowed erase 0x00438539
#include <list>

// Single-node erase binds the verified native STLport owner at RVA 0x00438539.
// Retain the callers' out-of-line call without emitting a competing copy.
namespace _STL {
template<> list<int>::iterator list<int>::erase(iterator position);
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class Rva0029BA28
{
public:
	void rva0029BA28(int val);
private:
	char m_pad[24];
	_STL::list<int, _STL::allocator<int> > m_list;
};

void Rva0029BA28::rva0029BA28(int val)
{
	for (_STL::list<int, _STL::allocator<int> >::iterator it = m_list.begin(); it != m_list.end(); ++it) {
		if (*it == val) {
			m_list.erase(it);
			break;
		}
	}
}
