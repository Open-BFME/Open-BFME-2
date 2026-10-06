// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001F93EB@Rva001F93EB@@QAEXXZ @0x001F93EB 23B
// Chain via rowed 0x001F8DA9: null-checked virtual slot +4 at +0 then
// tail-jmp to rowed Rva001F8DA9 on this+4. Caller jmps from 0x001FA49F.
// Honest Rva names; /O1 for je plus tail-jmp shape.
class Helper001F93EB
{
public:
	virtual ~Helper001F93EB();
	virtual void tick();
};

class Rva001F8DA9
{
public:
	void rva001F8DA9();
};

class Rva001F93EB
{
public:
	void rva001F93EB();

private:
	Helper001F93EB *m_0;
	Rva001F8DA9 m_4;
};
void Rva001F93EB::rva001F93EB()
{
	Helper001F93EB *p = m_0;
	if (p)
		p->tick();
	m_4.rva001F8DA9();
}
