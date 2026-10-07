// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00598149@Rva00598149@@QAEXPAX@Z @0x00598149 73B via map value-erase with increment
// Evidence: thiscall ret4 void* arg; map at +8 via edi; node second at +0x14 vs arg; rowed _M_increment 0x00024250 plus rowed map<int void*> erase 0x005530A8; flag byte at +0x2C; callers unclaimed 0x004EC8F4
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
class Rva00598149
{
public:
	void rva00598149(void *key);
private:
	char m_pad00[8];
	_STL::map<int, void *> m_map;
	char m_padAfterMap[0x2C - 8 - sizeof(_STL::map<int, void *>)];
	bool m_done;
};
void Rva00598149::rva00598149(void *key)
{
	for (_STL::map<int, void *>::iterator it = m_map.begin(); it != m_map.end();) {
		if (it->second == key) {
			_STL::map<int, void *>::iterator cur = it++;
			m_map.erase(cur);
		} else {
			++it;
		}
	}
	m_done = true;
}
