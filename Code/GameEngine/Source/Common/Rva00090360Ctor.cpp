// cl: /MD
// ??0Rva00090360@@QAE@XZ 33B @0x00090360: ctor calling rowed base 0x00262002 then storing vtable 0x007C7E20 then zeroing +0x14 (10 dwords) and +0x3C. Size 0x40 per caller alloc at 0x0004C55E. Evidence: rowed base callee plus vtable plus caller.
class Rva0026201C
{
public:
	Rva0026201C();
	virtual ~Rva0026201C();
protected:
	char m_pad04[12];
	struct Rva90381Node *m_head10;
};

class Rva00090360 : public Rva0026201C
{
public:
	Rva00090360();
	virtual ~Rva00090360();
	void rva00090381(struct Rva90381Node *n);
private:
	int m_14[10];
	int m_3C;
};

struct Rva90381Node
{
	virtual void *rva(int x);
	char m_pad04[8];
	Rva90381Node *m_next;
	Rva90381Node *m_prev;
};

struct Node00262045;
class Rva00262045
{
public:
	void rva00262045(struct Node00262045 *n);
};

void __cdecl operator delete(void *p);

// ?rva00090381@Rva00090360@@QAEXPAURva90381Node@@@Z @0x00090381 47B
// Slot 15 offset 0x3C of vtable 0x007C7E20. Unlinks n via rowed 0x00262045,
// clears head at +0x10 if it equals n, releases via slot0 plus rowed delete 0x0002FD60.
// Callers in dtor 0x0009045E.
void Rva00090360::rva00090381(struct Rva90381Node *n)
{
	if (n != 0) {
		((Rva00262045 *)this)->rva00262045((struct Node00262045 *)n);
		if (m_head10 == n)
			m_head10 = 0;
		operator delete(n->rva(0));
	}
}

Rva00090360::Rva00090360()
{
	for (int i = 0; i < 10; ++i)
		m_14[i] = 0;
	m_3C = 0;
}
