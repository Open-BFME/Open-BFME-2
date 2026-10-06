// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001F944E@Rva001F944E@@QAEXXZ 0x001F944E 23B
// Evidence: chain via rowed 0x001F8E0C; null-checked virtual slot +4 at +0 then tail-jmp to rowed Rva001F8E0C on this+4. Caller jmp at 0x001FA502. Honest Rva names.

class Helper001F944E
{
public:
	virtual ~Helper001F944E();
	virtual void tick();
};

class Rva001F8E0C
{
public:
	void rva001F8E0C();
};

class Rva001F944E
{
public:
	void rva001F944E();
private:
	Helper001F944E *m_ptr;
	Rva001F8E0C m_next;
};
void Rva001F944E::rva001F944E()
{
	Helper001F944E *p = m_ptr;
	if (p)
		p->tick();
	m_next.rva001F8E0C();
}
