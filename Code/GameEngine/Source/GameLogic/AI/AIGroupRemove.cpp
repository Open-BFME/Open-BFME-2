// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?remove@AIGroup@@QAE_NPAVObject@@@Z @ 0x0036CF07 108B
// AIGroup::remove: find member in +0x04 STLport list, erase, leaveGroup,
// set dirty at +0x0C, destroy via TheAI at 0x00DFF0F8 when empty.
// Evidence: callers 0x0036CFCB 0x0036D01B plus 0x0036D7E5,
// callees leaveGroup pin 0x0028C01F plus destroyGroup row 0x002FE712,
// BFME1 AIGroupMembership remove plus ZH AIGroup remove donor shape.
//
// ?removeInvalidObjectsFromGroup@AIGroup@@QAE_NPAURva0036D7A6Outer@@@Z @ 0x0036D7A6 95B
// AIGroup member filter: walk +0x04 list, slot38 check on +0x250 receiver
// with (Object 0 1), remove failures, false when group destroyed.
// Evidence: chain caller of remove 0x0036CF07, caller 0x00372670,
// slot38 virtual plus remove row, BFME1 removeAny donor shape.
//
// ?rva0036DC6F@AIGroup@@QAEXHH@Z @ 0x0036DC6F 30B
// AIGroup first-member delegate: empty check on +0x04 list, front Object,
// rva0028C1A9 module lookup, tail-call its slot0 with forwarded args.
// Evidence: flanked by AIGroup rows 0x0036D7A6 and setAttitude 0x0036DD16,
// callee rva0028C1A9 row, ret 8 two-arg forward plus jmp [edx] tail shape.
//
// ?rva0036D805@AIGroup@@QAEXH@Z @ 0x0036D805 50B
// AIGroup broadcast: null-checked Object +0x250 provider slot34 call with
// one forwarded int arg on every member.
// Evidence: same begin/end loop as rva0036DDCD in AIGroupAttackTeam TU,
// +0x250 provider offset per ObjectRva0028C197 TU, caller 0x00379AF7.
//
// ?rva0036D837@AIGroup@@QAEXH@Z @ 0x0036D837 50B
// Same broadcast shape calling provider slot35 instead of slot34.
// Evidence: byte-identical loop to 0x0036D805 above, caller 0x003787FA.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include <algorithm>

enum ObjectID
{
	INVALID_ID = 0
};

class Rva0036D805If
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void slot34(int x);
	virtual void slot35(int x);
};

class Object
{
public:
	void leaveGroup();
	void *rva0028C1A9() const;

	char m_pad[0x250];
	Rva0036D805If *m_provider250;
};

class Rva0036DC6FIf
{
public:
	virtual void slot0(int a, int b);
};

class AIGroup;

class AI
{
public:
	void destroyGroup(AIGroup *group);
};
extern AI *TheAI;

class Rva0036D7A6Receiver
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual bool slot38(Object *obj, int a, int b);
};

struct Rva0036D7A6Inner
{
	char m_pad[0x250];
	Rva0036D7A6Receiver *m_rec;
};

struct Rva0036D7A6Outer
{
	char m_pad[0x0c];
	Rva0036D7A6Inner *m_inner;
};

class AIGroup
{
public:
	bool remove(Object *member);
	bool isEmpty() { return m_memberList.empty(); }
	bool removeInvalidObjectsFromGroup(Rva0036D7A6Outer *o);
	void rva0036DC6F(int a, int b);
	void rva0036D805(int x);
	void rva0036D837(int x);

private:
	virtual void *deleteInstance(int flags);
	_STL::list<ObjectID> m_memberList;
	char m_pad[4];
	bool m_dirty;
};

bool AIGroup::remove(Object *member)
{
	_STL::list<ObjectID>::iterator it = _STL::find(m_memberList.begin(), m_memberList.end(), *(ObjectID *)&member);
	if (it == m_memberList.end())
		return false;
	((_STL::list<int> *)&m_memberList)->erase(*(_STL::list<int>::iterator *)&it);
	member->leaveGroup();
	m_dirty = true;
	if (isEmpty()) {
		TheAI->destroyGroup(this);
		return true;
	}
	return false;
}

bool AIGroup::removeInvalidObjectsFromGroup(Rva0036D7A6Outer *o)
{
	Rva0036D7A6Inner *inner = o->m_inner;
	if (inner) {
		Rva0036D7A6Receiver *r = inner->m_rec;
		for (_STL::list<ObjectID>::iterator it = m_memberList.begin(); it != m_memberList.end();) {
			Object *obj = (Object *)(*it);
			_STL::list<ObjectID>::iterator nxt = it;
			++nxt;
			if (!r->slot38(obj, 0, 1)) {
				if (remove(obj))
					return false;
			}
			it = nxt;
		}
	}
	return true;
}

void AIGroup::rva0036DC6F(int a, int b)
{
	if (m_memberList.empty())
		return;
	Object *obj = (Object *)m_memberList.front();
	void *p = obj->rva0028C1A9();
	if (p == 0)
		return;
	((Rva0036DC6FIf *)p)->slot0(a, b);
}

void AIGroup::rva0036D805(int x)
{
	for (_STL::list<ObjectID>::iterator it = m_memberList.begin(); it != m_memberList.end(); ++it) {
		Object *obj = (Object *)(*it);
		Rva0036D805If *p = obj->m_provider250;
		if (p)
			p->slot34(x);
	}
}

void AIGroup::rva0036D837(int x)
{
	for (_STL::list<ObjectID>::iterator it = m_memberList.begin(); it != m_memberList.end(); ++it) {
		Object *obj = (Object *)(*it);
		Rva0036D805If *p = obj->m_provider250;
		if (p)
			p->slot35(x);
	}
}
