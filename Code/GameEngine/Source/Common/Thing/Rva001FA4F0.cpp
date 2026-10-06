// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001FA4F0@Rva001FA4F0@@QAEXXZ 0x001FA4F0 23B
// Evidence: chain via rowed 0x001F944E; null-checked virtual slot +4 at +0 then tail-jmp to rowed Rva001F944E on this+4. Caller jmp at 0x001FA80A. Honest Rva names.
class Helper001FA4F0
{
public:
	virtual ~Helper001FA4F0();
	virtual void tick();
};

class Rva001F944E
{
public:
	void rva001F944E();
};

class Rva001FA4F0
{
public:
	void rva001FA4F0();
private:
	Helper001FA4F0 *m_ptr;
	Rva001F944E m_next;
};
void Rva001FA4F0::rva001FA4F0()
{
	Helper001FA4F0 *p = m_ptr;
	if (p)
		p->tick();
	m_next.rva001F944E();
}
