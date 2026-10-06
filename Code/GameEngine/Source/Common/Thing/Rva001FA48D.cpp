// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001FA48D@Rva001FA48D@@QAEXXZ 0x001FA48D 23B
// Evidence: chain via rowed 0x001F93EB; null-checked virtual slot +4 at +0 then tail-jmp to rowed Rva001F93EB on this+4. Caller jmp at 0x001FA7A7. Honest Rva names.
class Helper001FA48D
{
public:
	virtual ~Helper001FA48D();
	virtual void tick();
};

class Rva001F93EB
{
public:
	void rva001F93EB();
};

class Rva001FA48D
{
public:
	void rva001FA48D();
private:
	Helper001FA48D *m_ptr;
	Rva001F93EB m_next;
};
void Rva001FA48D::rva001FA48D()
{
	Helper001FA48D *p = m_ptr;
	if (p)
		p->tick();
	m_next.rva001F93EB();
}
