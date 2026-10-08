// cl: /DNDEBUG /MD
// ?rva005E1260@Rva005E1260@@QAEAAV1@PBUInit005E1260@@@Z @0x005E1260 59B unlock ref-holder alloc via rowed operator new.
// Evidence: retail push 0x10 call rowed ??2@YAPAXI@Z 0x0002FDA0 then vtable 0x00877990 refcount at +4 payload copy +8 +0xC store to [this] inc ref return this; callers 0x005C7D3F 0x005C7F0A 0x005E15EB.
struct Init005E1260
{
	int m_a;
	int m_b;
};

class Rva005E1260Body
{
public:
	virtual ~Rva005E1260Body() {}
	int m_ref;
	int m_a;
	int m_b;
	Rva005E1260Body(const Init005E1260 *p) : m_ref(0)
	{
		m_a = p->m_a;
		m_b = p->m_b;
	}
};

class Rva005E1260
{
	Rva005E1260Body *m_ptr;
public:
	Rva005E1260 &rva005E1260(const Init005E1260 *p);
	Rva005E1260(Init005E1260 init);
};

// Native 0x005C7D37..0x005C7D4A (19B): forwards the two-word by-value
// payload to the existing timer binder and returns this. The binder's
// reference return is ignored; the wrapper owns the constructor return.
Rva005E1260::Rva005E1260(Init005E1260 init)
{
	rva005E1260(&init);
}

Rva005E1260 &Rva005E1260::rva005E1260(const Init005E1260 *p)
{
	Rva005E1260Body *q = new Rva005E1260Body(p);
	m_ptr = q;
	if (q)
		++q->m_ref;
	return *this;
}
