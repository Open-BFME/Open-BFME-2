// cl: /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?removeMessageAction@HotKeyManager@@QAEIH@Z 0x003593D8 16B; tree erase call and +0x24 this adjustment are retail evidence
#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

typedef int Int;

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

struct Rva00358E26Record
{
	char word;
	bool operator<(const Rva00358E26Record &other) const { return word < other.word; }
	bool operator==(const Rva00358E26Record &other) const { return word == other.word; }
};

namespace _STL {template<>struct __type_traits<Rva00358E26Record>:__type_traits_aux<1>{};}

typedef _STL::_Rb_tree<int, _STL::pair<int const, Rva00358E26Record>,
	_STL::_Select1st<_STL::pair<int const, Rva00358E26Record> >,
	_STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00358E26Record> > > Rva00359269Tree;

// Retail's range erase calls the rowed tree clear at 0x00358DFD and node erase at
// 0x00358D27; suppress this TU's own copies and bind the template names to those rows.
namespace _STL {
template <> void _Rb_tree<int, pair<int const, Rva00358E26Record>, _Select1st<pair<int const, Rva00358E26Record> >, less<int>, allocator<pair<int const, Rva00358E26Record> > >::clear();
template <> void _Rb_tree<int, pair<int const, Rva00358E26Record>, _Select1st<pair<int const, Rva00358E26Record> >, less<int>, allocator<pair<int const, Rva00358E26Record> > >::erase(_Rb_tree<int, pair<int const, Rva00358E26Record>, _Select1st<pair<int const, Rva00358E26Record> >, less<int>, allocator<pair<int const, Rva00358E26Record> > >::iterator);
}

// The message-action map at HotKeyManager +0x24 (HotKey.cpp's view); its key
// erase is the tree's erase(const int &), rowed in HotKey.cpp at 0x00358FA5.
class HotKeyMessageActionMap
{
public:
	unsigned int erase(const Int &messageType)
	{
		return ((Rva00359269Tree *)this)->erase(messageType);
	}
private:
	void *m_header;		// +0x00
	int m_count;		// +0x04
	int m_compare;		// +0x08
};

class HotKeyManager
{
public:
	unsigned int removeMessageAction(Int messageType);
private:
	unsigned char m_pad00[0x24];
	HotKeyMessageActionMap m_messageActionMap;		// +0x24
};

unsigned int HotKeyManager::removeMessageAction(Int messageType)
{
	return m_messageActionMap.erase(messageType);
}
