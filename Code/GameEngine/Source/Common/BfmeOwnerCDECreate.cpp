// cl: /EHsc
// ?rva008fa850@BfmeOwnerCDE@@QAEXPAX@Z
//
// The caller at 0x008F73A0 dispatches to this owner method through its CDE
// interface. The sibling at 0x008F8D00 removes the same BfmeThingCDE nodes.
// BFME2 repair: BfmeThingCDE is 0x11C wide here (push 0x11C), not BFME1's
// 0xE0, so m_tail runs to 0x11C. B1 0x008FA850 170B -> B2 0x0073D440 170B,
// immediate-only drift at +0x38 (push 0xE0 vs 0x11C).

class CDEVirtualBase
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void *f3();
	virtual void *f4();
};

class CDELeading
{
public:
	virtual void f0();
};

class CDEProvider : public CDELeading, public virtual CDEVirtualBase
{
public:
	virtual void f0();
};

class BfmeThingCDE
{
public:
	BfmeThingCDE(void *what, void *owner, void *head);
	void initializeArray(int count);

	char m_pad[0x14];
	void *m_prev;
	BfmeThingCDE *m_next;
	char m_tail[0x11c - 0x1c];
};

class BfmeOwnerCDE
{
public:
	void rva008fa850(void *what);
	int getCDECount(void *what);

	char m_pad[0x30];
	void *m_link;
	BfmeThingCDE *m_head;
};

#pragma comment(linker, "/alternatename:??0BfmeThingCDE@@QAE@PAX00@Z=?d_008f78b0@@YAXXZ")

void BfmeOwnerCDE::rva008fa850(void *what)
{
	if (what == 0 || ((CDEProvider *)what)->f4() != 0)
		return;

	BfmeThingCDE *thing = new BfmeThingCDE(what, this, &m_link);
	thing->initializeArray(getCDECount(what));

	BfmeThingCDE *old = m_head;
	thing->m_next = old;
	if (old != 0)
		old->m_prev = &thing->m_next;
	thing->m_prev = &m_head;
	m_head = thing;
}
