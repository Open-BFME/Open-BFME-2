// cl: /O1 /MD
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

class Rva002C5FBA
{
public:
	void *rva002C5FBA(int key);
};

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

class Rva004E94FB
{
public:
	void rva004E94FB();
	void rva004E951C(void *o);
	void *rva004E955F(int unused, int key);

private:
	Rva004E94FBHead *m_00;
};

// ?rva004E94FB@Rva004E94FB@@QAEXXZ @0x004E94FB 33B.
void Rva004E94FB::rva004E94FB()
{
	Rva004E94FBHead *head = m_00;
	for (Rva004E94FBNode *n = head->m_first; n != (Rva004E94FBNode *)head; n = (Rva004E94FBNode *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)n))
		n->m_14->rva002C6845();
}

// ?rva004E951C@Rva004E94FB@@QAEXPAX@Z @0x004E951C 67B.
void Rva004E94FB::rva004E951C(void *o)
{
	Rva004E951CTwo t = { 1, 1 };
	((Rva004E951CObj *)o)->v10(&t);
	Rva004E94FBHead *head = m_00;
	for (Rva004E94FBNode *n = head->m_first; n != (Rva004E94FBNode *)head; n = (Rva004E94FBNode *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)n))
		((Rva002C7008 *)n->m_14)->rva002C7008(o);
}

// ?rva004E955F@Rva004E94FB@@QAEPAXHH@Z @0x004E955F 51B.
void *Rva004E94FB::rva004E955F(int unused, int key)
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
