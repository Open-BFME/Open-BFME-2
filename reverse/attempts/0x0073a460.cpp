// ?d_008f7ec0@BfmeThingCDE@@QAEXXZ
// partial score=0.8 date=2026-09-22
// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2
// ?bfmeDtorCDE@BfmeThingCDE@@QAEXXZ
//
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/BfmeThingCDEDestructor.cpp
// (BFME1 0x008F8340). The donor also defines ?bfmeCheckABI, which the sweep did
// not place, so only the destructor body is defined here; the sibling stays
// declared-only. The node at 0x008F7EC0 clears the same 0x10-byte entries that
// this destructor passes to the array-delete helper. Its Ghidra body has no
// source row, so the member call uses an address pin for that helper.

class CDEVirtualBase
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3(void *arg);
};

class CDELeading
{
public:
	virtual void f0();
	virtual void f1();
};

class CDEProvider : public CDELeading, public virtual CDEVirtualBase
{
public:
	virtual void f0();
};

class CDELinkNode
{
public:
	void *m_00;
	char m_pad04[8];
	void *m_0c;
	char m_pad10[4];
	void *m_14;
};

struct CDEArraySlot
{
	void *activeNode;
	int unused04;
	void *prevNode;
	void *nextNode;
};

struct CDEListNode
{
	void *nextNode;
	int unused04;
	void *prevNode;
};

class BfmeThingCDE
{
public:
	bool bfmeCheckABI();
	void bfmeDtorCDE();
	void d_008f7990();
	void d_008f7ec0();

	void *m_owner;
	CDEProvider *m_ptr4;
	CDEProvider *m_ptr8;
	CDELinkNode *m_link0;
	CDELinkNode *m_link1;
	CDELinkNode *m_prev;
	CDELinkNode *m_next;
	void *m_array;
	int m_count;
	int m_values[16];
	int m_slots[16];
	unsigned char m_status[16];
	int m_bfmeB4;
	int m_bfmeB8;
	int m_bfmeBC;
	int m_bfmeC0;
	int m_bfmeA[2];
	unsigned int m_bfmeC[2];
	unsigned int m_bfmeB[2];
	unsigned char m_bfmeDC;
};

#pragma comment(linker, "/alternatename:?d_008f7990@BfmeThingCDE@@QAEXXZ=?d_008f7990@@YAXXZ")
#pragma comment(linker, "/alternatename:?d_008f7ec0@BfmeThingCDE@@QAEXXZ=?d_008f7ec0@@YAXXZ")
#pragma comment(linker, "/alternatename:?ArrayDeleteHelperBodyThunk@@YGXPAXII0@Z=?ArrayDeleteHelperBodyThunk@@YAXXZ")

void __stdcall ArrayDeleteHelperBodyThunk(void *, unsigned, unsigned, void *);
extern void __cdecl operator delete[](void *);

void BfmeThingCDE::d_008f7ec0()
{
	CDEArraySlot *curSlot = (CDEArraySlot *)m_array;
	CDEArraySlot *endSlot = (CDEArraySlot *)((char *)curSlot + (m_count << 4));
	if (curSlot == endSlot)
		return;
	while (curSlot != endSlot)
	{
		if (curSlot->activeNode == 0)
			return;
		void *nextNode = curSlot->nextNode;
		curSlot->activeNode = 0;
		if (nextNode != 0)
			((CDEListNode *)nextNode)->prevNode = curSlot->prevNode;
		void *prevNode = curSlot->prevNode;
		void *linkNode = curSlot->nextNode;
		curSlot = (CDEArraySlot *)((char *)curSlot + 0x10);
		((CDEListNode *)prevNode)->nextNode = linkNode;
	}
}

void BfmeThingCDE::bfmeDtorCDE()
{
	d_008f7990();
	if (m_ptr4 != 0)
		m_ptr4->f3(0);
	if (m_ptr8 != 0)
	{
		m_ptr8->f3(0);
		m_ptr8->f0();
		m_ptr8 = 0;
	}
	d_008f7ec0();
	if (m_array != 0)
	{
		void *cookie = (char *)m_array - 4;
		// Retail pushes 0x00A9E440 here; the donor's 0x00CF7BD0 is the BFME1
		// address of the same word. The bytes decide.
		ArrayDeleteHelperBodyThunk(m_array, 0x10, *(unsigned *)cookie,
			reinterpret_cast<void *>(0x00A9E440));
		::operator delete[](cookie);
	}
	if (m_prev != 0)
	{
		m_prev->m_00 = m_next;
		if (m_next != 0)
			m_next->m_14 = m_prev;
		m_prev = 0;
	}
	if (m_link1 != 0)
		m_link1->m_0c = m_link0;
	m_link0->m_00 = m_link1;
}
