// cl: /O1 /DNDEBUG /MD
//
// ?rva002E713F@Rva002E713FOwner@@QAEXXZ @0x002E713F 57B: guarded pair-call
// (thiscall, void). Returns when +0x10 is null; invokes pinned 0x0052F294
// on this when either flag byte (+0x1BEB4/+0x1BEB5) is set; then invokes
// pinned 0x00533BEC on this+0x460 with (&+0x14, &+0x60, +0x10). Honest
// address-derived names; member/callee identities unproven.

struct Rva002E713F460
{
	void rva00533BEC(void *a, void *b, void *c);
	char m_pad[4];
};

struct Rva0052F294Node
{
	void *m_payload;
	Rva0052F294Node *m_next;
};

class Rva0036666B
{
public:
	bool rva0036666B();
};

class Rva00366B30
{
public:
	void rva00366B77();
};

class Rva00366E2E
{
public:
	void rva00366E2E();
};

class Rva002E713FOwner
{
public:
	void rva002E713F();
	void rva0052F294();
	void rva0052ED74(void *node, int flags);
private:
	char m_pad00[0x10];
	void *m_p10;
	int m_14;
	char m_pad18[0x60 - 0x18];
	int m_60;
	char m_pad64[0x460 - 0x64];
	Rva002E713F460 m_s460;
	char m_pad464[0x1BEB4 - 0x460 - 4];
	unsigned char m_b1BEB4;
	unsigned char m_b1BEB5;
};

// ?rva002E713F@Rva002E713FOwner@@QAEXXZ
void Rva002E713FOwner::rva002E713F()
{
	if (m_p10 == 0)
		return;
	if (m_b1BEB4 != 0 || m_b1BEB5 != 0)
		rva0052F294();
	m_s460.rva00533BEC(m_p10, &m_60, &m_14);
}

// ?rva0052F294@Rva002E713FOwner@@QAEXXZ @0x0052F294 88B
// Target evidence: scans 15 records at +0x60 with 0x40 stride; tests each through rowed 0x0036666B,
// dispatches by +0x38 to 0x00366B77 or 0x00366E2E, drains the +0x5C list through 0x0052ED74,
// then clears bytes +0x1BEB4/+0x1BEB5. Shared-owner relation comes from rowed 0x002E713F.
void Rva002E713FOwner::rva0052F294()
{
	Rva0036666B *slot = (Rva0036666B *)((char *)this + 0x60);
	int remaining = 15;
	do
	{
		if (slot->rva0036666B())
		{
			if (*(int *)((char *)slot + 0x38) != 0)
				((Rva00366B30 *)slot)->rva00366B77();
			else
				((Rva00366E2E *)slot)->rva00366E2E();
		}
		slot = (Rva0036666B *)((char *)slot + 0x40);
	}
	while (--remaining != 0);

	Rva0052F294Node *node = *(Rva0052F294Node **)((char *)this + 0x5C);
	while (node != 0)
	{
		rva0052ED74(node, 1);
		node = node->m_next;
	}
	((unsigned char *)this)[0x1BEB4] = 0;
	((unsigned char *)this)[0x1BEB5] = 0;
}
