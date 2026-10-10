// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ObjectOrderQueue (WorldBuilder GameLogic/System/ObjectOrderQueue.cpp; WB's
// __FUNCTION__ strings name each body): checkForPatrol @0x00548117 108B and
// @0x00548183 (two overloads, both asserting "startOrder" and calling the
// same two xfer helpers), setPatrolStartOrder @0x005481F9.
// Evidence: caller 0x0035545C; list at +4 with NameKey at +8; find 0x00355155 row; virtual [edx+0x24]; contains 0x00548800 row
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
class Rva00355B61;
extern class AiOrdersManager *TheAiOrdersManager;

class CreateAHeroData;
typedef _STL::list<CreateAHeroData *> ListHeroPtr;
class Rva00548800
{
public:
	bool rva00548800(const ListHeroPtr *list);
	bool rva00548753(const Rva00548800 &other);
};

class ObjectOrderQueue
{
	int m_00;				// +0x00, passed to slot 7 of each armor
	_STL::list<NameKeyType> m_list;		// +0x04
	char m_pad08[0x0C - 0x08];
	ObjectID m_0C;				// +0x0C, set when flags bit 0
	ObjectID m_10;				// +0x10, set when flags bit 1
public:
	const ArmorTemplate *checkForPatrol(void *a1, const ListHeroPtr *a2);
	const ArmorTemplate *checkForPatrol(void *a1, const Rva00548800 *a2);
	void setPatrolStartOrder(ObjectID v, int flags);
};

const ArmorTemplate *ObjectOrderQueue::checkForPatrol(void *a1, const ListHeroPtr *a2)
{
	typedef _STL::list<NameKeyType>::_Node Node;
	Node *cur = (Node *)((Node *)m_list._M_node._M_data)->_M_next;
	while (cur != (Node *)m_list._M_node._M_data) {
		const ArmorTemplate *armor2 = 0;
		const ArmorTemplate *armor1 = reinterpret_cast<Rva00355B61 *>(TheAiOrdersManager)->rva00355155((NameKeyType)cur->_M_data);
		if (armor1 && armor1->check(a1)) {
			Node *nxt = (Node *)cur->_M_next;
			if (nxt != (Node *)m_list._M_node._M_data) {
				armor2 = reinterpret_cast<Rva00355B61 *>(TheAiOrdersManager)->rva00355155((NameKeyType)nxt->_M_data);
				if (armor2 && ((Rva00548800 *)armor2)->rva00548800(a2))
					return armor2;
			}
		}
		cur = (Node *)cur->_M_next;
	}
	return 0;
}

const ArmorTemplate *ObjectOrderQueue::checkForPatrol(void *a1, const Rva00548800 *a2)
{
	typedef _STL::list<NameKeyType>::_Node Node;
	Node *cur = (Node *)((Node *)m_list._M_node._M_data)->_M_next;
	while (cur != (Node *)m_list._M_node._M_data) {
		if ((NameKeyType)cur->_M_data == (NameKeyType)*(const int *)((const char *)a2 + 0x10))
			return 0;
		const ArmorTemplate *armor2 = 0;
		const ArmorTemplate *armor1 = reinterpret_cast<Rva00355B61 *>(TheAiOrdersManager)->rva00355155((NameKeyType)cur->_M_data);
		if (armor1 && armor1->check(a1)) {
			Node *nxt = (Node *)cur->_M_next;
			if (nxt != (Node *)m_list._M_node._M_data) {
				armor2 = reinterpret_cast<Rva00355B61 *>(TheAiOrdersManager)->rva00355155((NameKeyType)nxt->_M_data);
				if (armor2 && ((Rva00548800 *)armor2)->rva00548753(*a2))
					return armor2;
			}
		}
		cur = (Node *)cur->_M_next;
	}
	return 0;
}

// ObjectOrderQueue::setPatrolStartOrder @0x005481F9 110B: from the first
// list entry equal to v, hand m_00 to slot 7 of every armor the remaining
// keys resolve to, then record v at +0x0C / +0x10 by flags bits 0 / 1.
// Assigning the find result to a default-constructed iterator is what reads
// it straight from the returned pointer as retail does.
void ObjectOrderQueue::setPatrolStartOrder(ObjectID v, int flags)
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
		((ArmorTemplate *)armor)->d7(m_00);
	}
	if ((flags & 1) != 0)
		m_0C = v;
	if ((flags & 2) != 0)
		m_10 = v;
}
