// ?changeToFormation@HordeContain@@UAEXPBVThingTemplate@@@Z
// partial score=0.8 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /ICode/GameEngine/Source /DNDEBUG /MD /EHs
//
// NEAR (not exact): ?changeToFormation@HordeContain@@UAEXPBVThingTemplate@@@Z
// retail 0x00472D43..0x0047306E (811 bytes, EH, RET 4).
//
// Identity:
// - It is slot 26 of ??_7HordeContain@@6BHordeContainInterface@@@ (0x00844C58),
//   shared by HorseHordeContain and AODHordeContain.
// - WorldBuilder 0x010C6650 is HordeContain::changeToFormation.
// - Retail adds a LifetimeUpdate hand-over and makeDirty over WB.
//
// Every call, the EH states and the list erase into the free list
// 0x009B8FF4 are in place. The whole stream is 804 bytes against 811.
//
// What still differs:
// - The list allocator temporary does not land in the dead parameter slot
//   (retail [ebp+0xB]), so the leader slot moves from -0x10 to -0x18.
// - The AI pointer gets ebx where retail keeps newHorde in ebx and the AI
//   pointer in memory.
// - The list size loop keeps its iterator in a register; retail spills it to
//   [ebp-0x1C].
//
// The list uses a TU-local _STL view: the pinned ctor 0x001EB984, the pinned
// find 0x0029B694, and the rowed disposal 0x001EB769 (nothrow).
#include <string.h>
#include "Common/GameLogicObjectLookupView.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

class Rva001EB769
{
public:
	void rva001EB769() throw();
};
extern void *g_freeList001EB130;
extern GameLogic *TheGameLogic;

namespace _STL
{
template <class T> class allocator
{
public:
	allocator() throw() {}
	allocator(const allocator &) throw() {}
	~allocator() throw() {}
};
struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};
template <class T> struct _List_node : public _List_node_base
{
	T _M_data;
};
template <class T> struct _Nonconst_traits
{
};
struct _List_iterator_base
{
	_List_node_base *_M_node;
	_List_iterator_base(_List_node_base *x) : _M_node(x) {}
	void _M_incr() { _M_node = _M_node->_M_next; }
	bool operator==(const _List_iterator_base &y) const { return _M_node == y._M_node; }
	bool operator!=(const _List_iterator_base &y) const { return _M_node != y._M_node; }
};
template <class T, class Traits> struct _List_iterator : public _List_iterator_base
{
	_List_iterator(_List_node_base *n) : _List_iterator_base(n) {}
	_List_iterator(const _List_iterator &x) : _List_iterator_base(x._M_node) {}
	T &operator*() const { return ((_List_node<T> *)_M_node)->_M_data; }
	_List_iterator &operator++() { this->_M_incr(); return *this; }
};
template <class T, class A> class _List_base
{
public:
	_List_base(const A &a);
	~_List_base() { ((Rva001EB769 *)this)->rva001EB769(); }
	_List_node_base *_M_node;
};
template <class InputIter, class T> InputIter find(InputIter first, InputIter last, const T &val);
template <class InputIter> inline Int __distance(const InputIter &first, const InputIter &last)
{
	Int n = 0;
	InputIter it(first);
	while (it != last)
	{
		++it;
		++n;
	}
	return n;
}
template <class InputIter> inline Int distance(const InputIter &first, const InputIter &last)
{
	return __distance(first, last);
}
template <class T, class A = allocator<T> > class list : public _List_base<T, A>
{
public:
	typedef _List_iterator<T, _Nonconst_traits<T> > iterator;
	list(const A &a = A()) : _List_base<T, A>(a) {}
	iterator begin() const { return iterator(this->_M_node->_M_next); }
	iterator end() const { return iterator(this->_M_node); }
	UnsignedInt size() const
	{
		UnsignedInt result = distance(begin(), end());
		return result;
	}
	T &front() { return *begin(); }
	iterator erase(iterator pos)
	{
		_List_node_base *next = pos._M_node->_M_next;
		_List_node_base *prev = pos._M_node->_M_prev;
		_List_node<T> *n = (_List_node<T> *)pos._M_node;
		prev->_M_next = next;
		next->_M_prev = prev;
		*(void **)n = g_freeList001EB130;
		g_freeList001EB130 = n;
		return iterator(next);
	}
};
}

class Team;
class ThingTemplate;
class Module;

struct CreateMask
{
	unsigned int m_bits[4];
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool b);
};
extern ThingFactory *TheThingFactory;

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_commandInterface;			// +0x20
};

class AiOrdersManager
{
public:
	void clearOrders(Int type, Int id);
};
extern AiOrdersManager *TheAiOrdersManager;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Drawable
{
public:
	char m_pad000[0x43C];
	unsigned char m_43C;							// +0x43C
};

class LifetimeUpdate
{
public:
	void setLifetimeRange(UnsignedInt minFrames, UnsignedInt maxFrames);
	char m_pad00[0x20];
	UnsignedInt m_dieFrame;							// +0x20
};

class StancesBehavior
{
public:
	void rva0045F084(Int stance);
};
NameKeyType Rva0045EE2CGet();

struct Rva0028F59A
{
	Rva0028F59A(Int a, Int bit);
	unsigned int m_bits[19];
};

class HordeContain;

class HordeContainSource
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V10(0) V10(1) V10(2) V10(3) V10(4) V10(5) V10(6) V10(7) V10(8) V10(9)
	V10(10) V10(11) V10(12)
	V(130) V(131) V(132) V(133)
	virtual HordeContain *getHordeContain();			// slot 134 (+0x218)
#undef V10
#undef V
};

class ObjectContainHolder
{
public:
#define V(n) virtual void slot##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30)
	virtual HordeContainSource *getContain();			// slot 31 (+0x7C)
#undef V
};

class Object
{
public:
	Drawable *getDrawable() const;
	void SwapForExchange(Object *other);
	Module *findModule(NameKeyType key) const;
	void clearModelConditionFlagsForHorde(const int *flags);
	void makeDirty();
	Team *getTeam() const { return m_team; }
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() const { return m_ai; }
	__forceinline HordeContainSource *getContain() const
	{
		ObjectContainHolder *holder = m_containHolder;
		return holder ? holder->getContain() : 0;
	}
	char m_pad000[0x74];
	ObjectID m_id;									// +0x74
	char m_pad078[0x250 - 0x78];
	ObjectContainHolder *m_containHolder;			// +0x250
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai;						// +0x258
	char m_pad25C[0x304 - 0x25C];
	Team *m_team;									// +0x304
};

template <class T>
class LatchRestore
{
public:
	LatchRestore(T &dest, const T &src) : m_whereToRestore(dest)
	{
		m_valueToRestore = dest;
		dest = src;
	}
	virtual ~LatchRestore(void) { m_whereToRestore = m_valueToRestore; }
protected:
	T m_valueToRestore;
	T &m_whereToRestore;
};

class HC_ModuleBase
{
public:
	virtual ~HC_ModuleBase();
	Object *getObject() const { return m_object; }
	const void *m_moduleData;						// +0x04
	Object *m_object;								// +0x08
	char m_pad0C[0x11C - 0x0C];
};

class HordeContainInterface
{
public:
#define V(n) virtual void slot##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16)
	virtual void getMembers(_STL::list<Object *> *out);		// slot 17 (+0x44)
	V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25)
	virtual void changeToFormation(const ThingTemplate *newTemplate);	// slot 26
	V(27) V(28)
	virtual void transferLeader(Object *leader, Object *member, Bool flag);	// slot 29 (+0x74)
	virtual void setMembers(_STL::list<Object *> *members);	// slot 30 (+0x78)
	V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56)
	virtual void slot57();								// +0xE4
	V(58) V(59)
	virtual Bool slot60();								// +0xF0
	V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	V(90) V(91) V(92)
	virtual void slot93(Int value);						// +0x174
	V(94) V(95) V(96) V(97) V(98) V(99)
	V(100) V(101) V(102) V(103) V(104) V(105) V(106) V(107) V(108) V(109)
	V(110) V(111) V(112) V(113) V(114) V(115) V(116) V(117) V(118) V(119)
	V(120)
	virtual void slot121();								// +0x1E4
	virtual void slot122();								// +0x1E8
#undef V
};

class HordeContain : public HC_ModuleBase, public HordeContainInterface
{
public:
	virtual void changeToFormation(const ThingTemplate *newTemplate);
	char m_pad120[0x26C - 0x120];
	ObjectID m_leaderID;							// +0x26C
	char m_pad270[0x27C - 0x270];
	Int m_27C;										// +0x27C
	char m_pad280[0x2B4 - 0x280];
	Bool m_2B4;										// +0x2B4
};

void HordeContain::changeToFormation(const ThingTemplate *newTemplate)
{
	Object *newObj;
	{
		CreateMask mask;
		memset(&mask, 0, sizeof(mask));
		newObj = TheThingFactory->newObject(newTemplate, getObject()->getTeam(), &mask, false);
	}
	HordeContainSource *contain = newObj->getContain();
	if (!contain)
	{
		TheGameLogic->destroyObject(newObj);
		return;
	}
	HordeContain *newHorde = contain->getHordeContain();
	slot122();
	_STL::list<Object *> members;
	getMembers(&members);
	Object *leader = TheGameLogic->findObjectByID(m_leaderID);
	if (leader)
	{
		_STL::list<Object *>::iterator it = _STL::find(members.begin(), members.end(), leader);
		if (it != members.end())
			members.erase(it);
	}
	Bool flag = getObject()->getDrawable()->m_43C != 0;
	if (newHorde->slot60())
	{
		AIUpdateInterface *ai = getObject()->getAI();
		if (ai)
		{
			TheAiOrdersManager->clearOrders(3, getObject()->getID());
			ai->m_commandInterface.aiIdle(CMD_FROM_PLAYER);
		}
	}
	getObject()->SwapForExchange(newObj);
	newHorde->slot93(m_27C);
	LatchRestore<Bool> latch(newHorde->m_2B4, true);
	newHorde->setMembers(&members);
	Object *newLeader = TheGameLogic->findObjectByID(newHorde->m_leaderID);
	if (!newLeader && leader && members.size() > 0)
	{
		Object *first = members.front();
		if (first)
		{
			newHorde->transferLeader(leader, first, true);
			leader = 0;
		}
	}
	if (leader)
	{
		if (newLeader)
		{
			static NameKeyType s_lifetimeKey = TheNameKeyGenerator->nameToKey("LifetimeUpdate");
			LifetimeUpdate *newLife = (LifetimeUpdate *)newLeader->findModule(s_lifetimeKey);
			LifetimeUpdate *oldLife = (LifetimeUpdate *)leader->findModule(s_lifetimeKey);
			if (newLife != 0 && oldLife != 0)
			{
				UnsignedInt dieFrame = oldLife->m_dieFrame;
				UnsignedInt now = TheGameLogic->getFrame();
				if (dieFrame <= now)
					newLife->setLifetimeRange(0, 0);
				else
					newLife->setLifetimeRange(dieFrame - now, dieFrame - now);
			}
		}
		TheGameLogic->destroyObject(leader);
	}
	newHorde->slot121();
	TheGameLogic->destroyObject(newObj);
	if (flag)
		newHorde->slot57();
	Object *hordeObj = newHorde->getObject();
	StancesBehavior *stances = (StancesBehavior *)hordeObj->findModule(Rva0045EE2CGet());
	if (stances)
	{
		if (newHorde->slot60())
			stances->rva0045F084(4);
		else
		{
			stances->rva0045F084(1);
			hordeObj->clearModelConditionFlagsForHorde((const int *)&Rva0028F59A(0, 0x71));
		}
	}
	hordeObj->makeDirty();
}
