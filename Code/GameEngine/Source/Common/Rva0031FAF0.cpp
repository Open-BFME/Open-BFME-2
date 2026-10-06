// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
// ?rva0031FAF0@Rva0031FAF0@@QAEXXZ @0x0031FAF0 280B chain: clears 6 lists at +0x158 plus one at +0x170 then releases two strings and zeroes ints.
// Evidence: calls rowed dtors 0x2004FD and 0x31F831 plus delete 0x2FD60 and List_base clear 0x23DAA5 and releaseBuffer 0x36410; callers at 0x320044 and 0x32056F; prev/next flags /O1 /EHsc /MD.
#include "ascii_string.h"

class Rva002004FD
{
public:
	~Rva002004FD();
};

class Rva0031F831
{
public:
	~Rva0031F831();
	AsciiString m_str;
	char m_pad[4];
	int m_8;
};

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class _List_base
	{
	public:
		void clear();
	};
	typedef _List_base<int, allocator<int> > ListBaseInt;
}

struct NodeA
{
	NodeA *m_next;
	NodeA *m_prev;
	Rva002004FD *m_obj;
};

struct ListA
{
	NodeA *m_header;
};

struct NodeB
{
	NodeB *m_next;
	NodeB *m_prev;
	Rva0031F831 *m_obj;
};

struct ListB
{
	NodeB *m_header;
};

class Rva0031FAF0
{
public:
	void rva0031FAF0();
private:
	AsciiString m_s0;
	int m_4;
	int m_8;
	AsciiString m_c;
	int m_10;
	int m_14;
	char m_pad18[0x1C];
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
	int m_4c;
	int m_50;
	int m_54;
	int m_58;
	int m_5c;
	int m_60;
	int m_64;
	int m_68;
	int m_6c;
	int m_70;
	int m_74;
	int m_78;
	int m_7c;
	int m_80;
	int m_84;
	int m_88;
	int m_8c;
	int m_90;
	char m_pad94[0xBC];
	int m_150;
	int m_154;
	ListA m_lists[6];
	ListB m_list170;
};

void Rva0031FAF0::rva0031FAF0()
{
	ListA *p = m_lists;
	int n = 6;
	do
	{
		NodeA *cur = p->m_header->m_next;
		while (cur != p->m_header)
		{
			Rva002004FD *obj = cur->m_obj;
			if (obj)
				delete obj;
			cur = cur->m_next;
		}
		(( _STL::ListBaseInt *)p)->clear();
		++p;
		--n;
	} while (n != 0);

	NodeB *curB = m_list170.m_header->m_next;
	while (curB != m_list170.m_header)
	{
		Rva0031F831 *obj = curB->m_obj;
		if (obj)
		{
			obj->m_8 = 0;
			delete obj;
		}
		curB = curB->m_next;
	}
	(( _STL::ListBaseInt *)&m_list170)->clear();

	m_s0.clear();
	m_8 = 0;
	m_4 = 0;
	m_c.clear();
	m_10 = 0;
	m_14 = 0;
	m_34 = 0;
	m_38 = 0;
	m_3c = 0;
	m_40 = 0;
	m_44 = 0;
	m_48 = 0;
	m_4c = 0;
	m_50 = 0;
	m_54 = 0;
	m_58 = 0;
	m_5c = 0;
	m_60 = 0;
	m_64 = 0;
	m_68 = 0;
	m_6c = 0;
	m_70 = 0;
	m_74 = 0;
	m_78 = 0;
	m_7c = 0;
	m_80 = 0;
	m_84 = 0;
	m_88 = 0;
	m_8c = 0;
	m_90 = 0;
	m_154 = 0;
	m_150 = 0;
}
