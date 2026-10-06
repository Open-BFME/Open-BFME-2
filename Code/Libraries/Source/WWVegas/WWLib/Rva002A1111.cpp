// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// retail 0x002A1111 71B unlock: add-if-missing list at +0x9c4 via rowed find 0x0029B694 and rowed list<int> push_back 0x0005548F; caller 0x00489F7D
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


enum ObjectID
{
	OBJECTID_NONE = 0
};

namespace _STL
{
template <class _InputIter, class _Tp>
_InputIter find(_InputIter __first, _InputIter __last, const _Tp &__val);
}

class Rva002A1111
{
public:
	void rva002A1111(ObjectID val);
private:
	char _pad[0x9c4];
	_STL::list<ObjectID> m_list;
};

void Rva002A1111::rva002A1111(ObjectID val)
{
	if (val == 0)
		return;
	_STL::list<ObjectID> &lst = m_list;
	if (_STL::find(lst.begin(), lst.end(), val) == lst.end())
		((_STL::list<int> &)lst).push_back(reinterpret_cast<const int &>(val));
}
