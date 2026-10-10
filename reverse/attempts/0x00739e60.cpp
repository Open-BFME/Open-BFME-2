// ??0BfmeThingCDE@@QAE@PAX00@Z
// partial score=0.92 date=2026-10-10
// cl: /O2 /DNDEBUG /MD /EHsc
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class CDEProvider;

class CDEVirtualBase
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3(void *arg);
	virtual void *f4();
};

class CDELeading
{
public:
	virtual void f0();
	virtual CDEProvider *f1();
	virtual CDEProvider *f2();
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
	BfmeThingCDE(void *what, void *owner, void *head);

	void *m_owner;
	CDEProvider *m_ptr4;
	CDEProvider *m_ptr8;
	CDELinkNode *m_link0;
	CDELinkNode *m_link1;
	CDELinkNode *m_prev;
	CDELinkNode *m_next;
	void *m_array;
	int m_count;
	int m_values[20];
	int m_slots[20];
	unsigned char m_status[20];
	int m_bfmeB4;
	int m_bfmeB8;
	int m_bfmeBC;
	int m_bfmeC0;
	int m_bfmeA0;
	int m_bfmeA1;
	unsigned int m_bfmeC0a;
	unsigned int m_bfmeC1;
	unsigned int m_bfmeB0;
	unsigned int m_bfmeB1;
	int m_pad100[6];
	unsigned char m_bfmeDC;
};

BfmeThingCDE::BfmeThingCDE(void *what, void *owner, void *head)
	: m_ptr4((CDEProvider *)what),
	  m_owner(owner),
	  m_ptr8(0),
	  m_prev(0),
	  m_next(0),
	  m_array(0),
	  m_count(0),
	  m_bfmeB4(0xdeadbeef),
	  m_bfmeB8(0x0badf00d),
	  m_bfmeA1(0),
	  m_bfmeC0a(0),
	  m_bfmeDC(0)
{
	m_bfmeBC = -1;
	m_bfmeC0 = -1;
	m_bfmeA0 = -1;
	m_link0 = (CDELinkNode *)head;
	CDELinkNode **link = (CDELinkNode **)head;
	m_link1 = *link;
	if (m_link1 != 0)
		m_link1->m_0c = (void *)&m_link1;
	*link = (CDELinkNode *)this;

	for (unsigned int i = 0; i < 20; ++i)
	{
		m_slots[i] = 0;
		m_values[i] = 0;
		m_status[i] = 0;
	}

	m_bfmeC1 = -1;
	m_bfmeB0 = -1;
	m_bfmeB1 = -1;
	_ReadWriteBarrier();
	m_ptr4->f3(this);
	m_ptr8 = ((CDELeading *)m_ptr4)->f2();
	if (m_ptr8 != 0)
		m_ptr8->f3(this);
}
