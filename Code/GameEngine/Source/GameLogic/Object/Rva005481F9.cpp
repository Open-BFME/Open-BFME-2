// cl: /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva005481F9@Rva00548117@@QAEXW4ObjectID@@H@Z @0x005481F9 110B
// Evidence: caller 0x00355245; list at +4 with NameKey at +8; find 0x0029B694 row; armor lookup 0x00355155 row; virtual [edx+0x1c]
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include <algorithm>

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectID { INVALID_ID = 0 };

class ArmorTemplate
{
public:
	virtual void d0();
	virtual void d1();
	virtual void d2();
	virtual void d3();
	virtual void d4();
	virtual void d5();
	virtual void d6();
	virtual void d7(int v);
	virtual void d8();
	virtual bool check(void *) const;
};

class Rva00355B61
{
public:
	const ArmorTemplate *rva00355155(NameKeyType key) const;
};
// Bind the native VA 0x00E01E18 slot to its existing subsystem owner;
// casts below retain this unit's independently verified local view.
class AiOrdersManager;
extern AiOrdersManager *TheAiOrdersManager;

class Rva00548117
{
	int m_val;
	_STL::list<NameKeyType> m_list;
	int m_a;
	int m_b;
public:
	void rva005481F9(ObjectID v, int flags);
};

void Rva00548117::rva005481F9(ObjectID v, int flags)
{
	typedef _STL::list<ObjectID> ListObj;
	ListObj &lst = (ListObj &)m_list;
	ListObj::iterator it;
	it = _STL::find(lst.begin(), lst.end(), v);
	if (it == lst.end())
		return;
	for (; it != lst.end(); ++it) {
		const ArmorTemplate *armor = reinterpret_cast<Rva00355B61 *>(TheAiOrdersManager)->rva00355155((NameKeyType)*it);
		if (!armor)
			continue;
		((ArmorTemplate *)armor)->d7(*(int *)this);
	}
	int tmp = (int)v;
	if ((flags & 1) != 0)
		*(int *)((char *)this + 0xC) = tmp;
	if ((flags & 2) != 0)
		*(int *)((char *)this + 0x10) = tmp;
}
