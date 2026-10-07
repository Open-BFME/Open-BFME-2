// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva00407E28@Rva00407E28@@QAEHH@Z retail 0x00407E28 43B
// ?rva00407E53@Rva00407E28@@QAE_NH@Z retail 0x00407E53 65B
// ?rva00407DE0@Rva00407E28@@QAE_NHH@Z retail 0x00407DE0 72B
// Evidence: unlock lane; update existing with flag +0x38 bit2 plus value plus -1; caller 0x00408C11.
// Evidence: unlock lane; two maps at +0x14/+0x20 insert 0/-1 returns bool; callers 0x00408C11 0x005B1B5E.
// Evidence: unlock lane; map<int int> at +0x14 via rowed _M_find 0x00388F63 and operator[] 0x0028932C; callers 0x005B05E8 0x005B07C1 0x005B0EE6 0x005B1B5E; prev-next Rb_tree hint same flags.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Rva00407E28
{
public:
	int rva00407E28(int key);
	bool rva00407E53(int key);
	bool rva00407DE0(int key, int value);
private:
	char m_pad[0x14];
	_STL::map<int, int> m_map1;
	_STL::map<int, int> m_map2;
	char m_pad2[0x38 - 0x14 - 12 - 12];
	int m_flags;
};

bool Rva00407E28::rva00407DE0(int key, int value)
{
	if (m_map1.find(key) == m_map1.end())
		return false;
	m_flags |= 4;
	m_map1[key] = value;
	m_map2[key] = -1;
	return true;
}

bool Rva00407E28::rva00407E53(int key)
{
	if (m_map1.find(key) != m_map1.end())
		return false;
	m_map1[key] = 0;
	m_map2[key] = -1;
	return true;
}

int Rva00407E28::rva00407E28(int key)
{
	_STL::map<int, int>::iterator it = m_map1.find(key);
	if (it == m_map1.end())
		return -1;
	return m_map1[key];
}
