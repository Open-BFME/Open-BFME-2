// ?rva004E7F83@Rva004E7F83@@QAEPAHABH@Z
// partial score=0.97 date=2026-10-05
// ?rva004E7F83@Rva004E7F83@@QAEPAHABH@Z
// partial score=0.97 date=2026-10-05
// cl: /O1
// stlport
//
// ?rva004E7F83@Rva004E7F83@@QAEPAHPBH@Z @0x004E7F83 71B.
// Hand-rolled pointer-interning subscript over map<int,int>: lower-bound
// the pointee, insert (pointee, pointer-as-int) on a miss through the rowed
// hint insert, and return the mapped slot. Written against the real map so
// the lower_bound call inlines to the rowed Rb_tree body.
#include <map>

class Rva004E7F83
{
public:
	int *rva004E7F83(const int &key);
private:
	_STL::map<int, int> m_map;
};

int *Rva004E7F83::rva004E7F83(const int &key)
{
	_STL::map<int, int>::iterator it = m_map.lower_bound(key);
	if (it == m_map.end() || key < it->first) {
		_STL::pair<const int, int> v(key, (int)&key);
		it = m_map.insert(it, v);
	}
	return &it->second;
}
