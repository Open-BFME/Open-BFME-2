// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva005F2295@Rva005F22D2@@QAEXH@Z, retail 0x005F2295, 61 bytes.
// Remove-by-key with notify: find key in map at +0x10 via rowed _M_find 0x00388F63,
// if found forEach via 0x005F224E with forwarder 0x005CC208 then erase via 0x005530A8.
// Evidence: same list+map layout as Clear 0x005F22D2; callers 0x005E4B93 0x005E4DDC.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Rva005F224EListener
{
public:
	virtual void notify(void *, int);
};

class Rva005F224EList
{
public:
	void forEach(void (Rva005F224EListener::*notify)(void *, int), void *arg, int value);
private:
	Rva005F224EListener **m_begin;
	Rva005F224EListener **m_end;
	Rva005F224EListener **m_capacity;
	unsigned int m_index;
};

class Rva005CC208
{
public:
	virtual void dummy0();
	virtual void dummy1();
	virtual void rva005CC208();
};

class Rva005F22D2
{
public:
	void rva005F2295(int key);
private:
	Rva005F224EList m_list00;
	_STL::map<int, int> m_map10;
};

void Rva005F22D2::rva005F2295(int key)
{
	_STL::map<int, int>::iterator it = m_map10.find(key);
	if (it != m_map10.end()) {
		m_list00.forEach((void (Rva005F224EListener::*)(void *, int))&Rva005CC208::rva005CC208, this, key);
		_STL::map<int, void *> &alias = reinterpret_cast<_STL::map<int, void *> &>(m_map10);
		alias.erase(reinterpret_cast<_STL::map<int, void *>::iterator &>(it));
	}
}
