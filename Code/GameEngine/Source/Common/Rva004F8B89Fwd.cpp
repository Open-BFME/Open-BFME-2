// cl: /MD
// stlport
//
// Three small dump-range forwarders/walkers: 0x4F8B89 repacks three ints
// plus a stack byte into the pinned stdcall 0x4F7EE9, 0x4E99D6 forwards
// three ints plus a stack byte into the pinned cdecl 0x4E98F7, and
// 0x4E94FB walks a node list through the pinned 0x2C6845 plus the rowed
// _M_increment. Retail 0x004F8B89 25B, 0x004E99D6 27B, 0x004E94FB 33B.
// Pins are honest address-derived candidates.

void __stdcall rva004F7EE9(int a, int b, int c, void *d);
void __cdecl rva004E98F7(int a, int b, int c, void *d);

// ?rva004E99D6@@YAXHHH@Z @0x004E99D6 27B.
void __cdecl rva004E99D6(int a, int b, int c)
{
	char tmp;
	rva004E98F7(a, b, c, &tmp);
}

namespace _STL
{
typedef bool _Rb_tree_Color_type;
struct _Rb_tree_node_base
{
	_Rb_tree_Color_type _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

class Rva002C6845
{
public:
	void rva002C6845();
};

class Rva002C7008
{
public:
	void rva002C7008(void *arg);
};

class Rva004E93E8
{
public:
	void *rva004E93E8();
};

class Rva004E9600
{
public:
	void *rva004E95D4(void *key);
};

class Rva004E93A8
{
public:
	int rva004E93A8();
};

class Rva002C585A
{
public:
	void rva002C585A(int count);
};

class SkirmishAI
{
public:
	void update();
};

class Rva004E8FF6
{
public:
	void rva004E8FF6(void *arg);
	void rva004E9040(void *arg);
};

struct Rva00DFEEF8World
{
	char m_pad[0x940];
	Rva004E8FF6 *m_obj;
};

extern Rva00DFEEF8World *g_00DFEEF8;

class Rva002C5FBA
{
public:
	void *rva002C5FBA(int key);
private:
	char m_pad[0x0C];
	class AITargetChooser *m_target;
};

class Rva002C589B;
class AITargetChooser
{
public:
	Rva002C589B *rva00505408(int key);
};

// ?rva002C5FBA@Rva002C5FBA@@QAEPAXH@Z @0x002C5FBA 17B.
// Null-checked forwarder at +0x0C to rowed AITargetChooser 0x00505408.
// Evidence: retail mov ecx [ecx+C] test je jmp plus pin plus caller 0x004E9575.
void *Rva002C5FBA::rva002C5FBA(int key)
{
	AITargetChooser *t = m_target;
	if (t != 0)
		return t->rva00505408(key);
	return 0;
}

struct Rva004E951CTwo
{
	unsigned char m_a;
	unsigned char m_b;
};

class Rva004E951CObj
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10(Rva004E951CTwo *t);
};

struct Rva004E94FBNode
{
	char m_pad[0x14];
	Rva002C6845 *m_14;
};

struct Rva004E94FBHead
{
	char m_pad[8];
	Rva004E94FBNode *m_first;
};

class AIGameTeam
{
public:
	void rva004E94FB();
	void rva004E951C(void *o);
	void *rva004E955F(int unused, int key);
	void rva004E9446();
	void update();

private:
	Rva004E94FBHead *m_00;
	char m_pad04[0x0C - 0x04];
	void *m_0C;
	void *m_10;
	char m_pad14[0x24 - 0x14];
	unsigned char m_24;
};

// ?rva004E94FB@AIGameTeam@@QAEXXZ @0x004E94FB 33B.
void AIGameTeam::rva004E94FB()
{
	Rva004E94FBHead *head = m_00;
	for (Rva004E94FBNode *n = head->m_first; n != (Rva004E94FBNode *)head; n = (Rva004E94FBNode *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)n))
		n->m_14->rva002C6845();
}

// ?rva004E951C@AIGameTeam@@QAEXPAX@Z @0x004E951C 67B.
void AIGameTeam::rva004E951C(void *o)
{
	Rva004E951CTwo t = { 1, 1 };
	((Rva004E951CObj *)o)->v10(&t);
	Rva004E94FBHead *head = m_00;
	for (Rva004E94FBNode *n = head->m_first; n != (Rva004E94FBNode *)head; n = (Rva004E94FBNode *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)n))
		((Rva002C7008 *)n->m_14)->rva002C7008(o);
}

// ?rva004E955F@AIGameTeam@@QAEPAXHH@Z @0x004E955F 51B.
void *AIGameTeam::rva004E955F(int unused, int key)
{
	Rva004E94FBHead *head = m_00;
	for (Rva004E94FBNode *n = head->m_first; n != (Rva004E94FBNode *)head; n = (Rva004E94FBNode *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)n))
	{
		void *inner = *(void **)((char *)n->m_14 + 0x164);
		void *found = ((Rva002C5FBA *)inner)->rva002C5FBA(key);
		if (found != 0)
			return found;
	}
	return 0;
}

// ?update@AIGameTeam@@QAEXXZ @0x004E9710 182B.
void AIGameTeam::update()
{
	if (m_24 != 0)
	{
		Rva002C585A *x = 0;
		if (m_0C != m_10)
		{
			void *p = ((Rva004E93E8 *)this)->rva004E93E8();
			if (p != 0)
			{
				void *q = ((Rva004E9600 *)this)->rva004E95D4(p);
				void *tmp = *(void **)((char *)q + 0x164);
				x = (Rva002C585A *)*(void **)((char *)tmp + 0x14);
				if (x != 0)
					x->rva002C585A(((Rva004E93A8 *)this)->rva004E93A8());
			}
			else
				m_24 = 0;
		}
		if (m_24 != 0)
		{
			g_00DFEEF8->m_obj->rva004E8FF6(((Rva004E93E8 *)this)->rva004E93E8());
			Rva004E94FBHead *head = m_00;
			for (Rva004E94FBNode *m = head->m_first; m != (Rva004E94FBNode *)head; m = (Rva004E94FBNode *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)m))
			{
				void *inner = *(void **)((char *)m->m_14 + 0x164);
				*(void **)((char *)inner + 0x18) = x;
				((SkirmishAI *)m->m_14)->update();
			}
			((AIGameTeam *)this)->rva004E9446();
			g_00DFEEF8->m_obj->rva004E9040(((Rva004E93E8 *)this)->rva004E93E8());
		}
	}
}

class Rva0059AED2
{
public:
	void rva0059AED2();
};

class Rva004F6187
{
public:
	void rva004F6187();
	void rva004F61B1();

private:
	char m_pad[0x78];
	int m_flag;
};

// ?rva004F6187@Rva004F6187@@QAEXXZ @0x004F6187 42B.
void Rva004F6187::rva004F6187()
{
	void ***pend = (void ***)((char *)this + 0x10);
	int n = 2;
	do
	{
		void **p = (void **)pend[-1];
		void **end = *pend;
		while (p != end)
		{
			((Rva0059AED2 *)*p)->rva0059AED2();
			++p;
		}
		pend = (void ***)((char *)pend + 0xC);
		--n;
	} while (n != 0);
}

class Rva0059ADB9
{
public:
	bool rva0059ADB9();
};

// ?rva004F61B1@Rva004F6187@@QAEXXZ @0x004F61B1 110B.
// Target evidence: the two begin/end pairs at +0x0C/+0x10 and +0x18/+0x1C
// each scan pointer elements and call the matched predicate at 0x0059ADB9;
// the resulting flags conditionally clear or set the dword at +0x78.
// Structural inference: the pair offsets match adjacent method 0x004F6187's
// two-list walk, so its address-derived owner spelling is reused. The owner
// identity remains unresolved.
void Rva004F6187::rva004F61B1()
{
	bool found[2];
	void ***range = (void ***)((char *)this + 0x10);
	int i = 0;
	do
	{
		found[i] = false;
		register void **endValue = *range;
		register void **current = range[-1];
		void ** volatile end = endValue;
		if (current != endValue)
		{
			do
			{
				if (((Rva0059ADB9 *)*current)->rva0059ADB9())
				{
					found[i] = true;
					break;
				}
				++current;
			} while (current != end);
		}
		++i;
		range += 3;
	} while (i < 2);
	if (found[1])
	{
		if (!found[0])
			m_flag = 1;
	}
	else
		m_flag = 0;
}
