// cl: /MD
// Range-27 list-append with notify.
// ?Rva00525D9A@Holder00525D9A@@QAEXPAUObj00525D9A@@@Z @0x00525D9A 102B
// Thiscall (this passes in ecx, stack arg in edx): walks the Pod12 node
// list at this+0x14 for a node whose data key (+8) matches o->m_74. On a
// miss, appends a {key, 0, g_00BBB9AC} element via the rowed out-of-line
// list<BfmePod12>::push_back 0x00420DF3 and notifies with the callback
// 0x005CB260 (the rowed slot-1 forwarder Rva005CB260::rva005CB260, passed as a
// member-function pointer the callee row 0x005258F8 types as int) plus the new
// tail node.
extern const float g_00BBB9AC;

struct BfmePod12
{
	int m_0;
	char m_4;
	char m_pad[3];
	float m_8;
};

struct Pod12Node00525D9A
{
	Pod12Node00525D9A *m_next;
	Pod12Node00525D9A *m_prev;
	BfmePod12 m_data;
};

struct NodeRef00525D9A
{
	Pod12Node00525D9A *m_ptr;
	NodeRef00525D9A(Pod12Node00525D9A *p) { m_ptr = p; }
};

namespace _STL
{
template <class _Tp> class allocator {};
template <class _Tp, class _Alloc = allocator<_Tp> > class list;
template <> class list<BfmePod12, allocator<BfmePod12> >
{
public:
	Pod12Node00525D9A *m_head;
	void push_back(const BfmePod12 &);
};
}

struct Obj00525D9A
{
	char m_pad[0x74];
	int m_74;
};

class Rva005CB260
{
public:
	virtual void rva005CB260_slot0();
	virtual void rva005CB260_slot1();
	void rva005CB260();
};

union Callback00525D9A
{
	void (Rva005CB260::*m_method)();
	int m_value;
};

struct Holder00525D9A
{
	char m_pad[0x14];
	_STL::list<BfmePod12> m_list;
	void Rva005258F8(int a, NodeRef00525D9A node);
	void Rva00525D9A(Obj00525D9A *o);
};

void Holder00525D9A::Rva00525D9A(Obj00525D9A *o)
{
	Pod12Node00525D9A *head = m_list.m_head;
	Pod12Node00525D9A *node = head->m_next;
	if (node != head)
	{
		int key = o->m_74;
		do
		{
			if (node->m_data.m_0 == key)
				goto done;
			node = node->m_next;
		} while (node != head);
	}
	{
		BfmePod12 elem;
		elem.m_0 = o->m_74;
		elem.m_4 = 0;
		elem.m_8 = g_00BBB9AC;
		m_list.push_back(elem);
		head = m_list.m_head;
		Callback00525D9A cb;
		cb.m_method = &Rva005CB260::rva005CB260;
		Rva005258F8(cb.m_value, head->m_prev);
	}
done:;
}
