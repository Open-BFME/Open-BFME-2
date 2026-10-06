// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001FA795@Rva001FA795@@QAEXXZ 0x001FA795 23B
// Evidence: chain via rowed 0x001FA48D; null-checked virtual slot +4 at +0 then tail-jmp to rowed Rva001FA48D on this+4. Caller call at 0x001FA980. Honest Rva names.
class Helper001FA795
{
public:
	virtual ~Helper001FA795();
	virtual void tick();
};

class Rva001FA48D
{
public:
	void rva001FA48D();
};

class Rva001FA795
{
public:
	void rva001FA795();
private:
	Helper001FA795 *m_ptr;
	Rva001FA48D m_next;
};
void Rva001FA795::rva001FA795()
{
	Helper001FA795 *p = m_ptr;
	if (p)
		p->tick();
	m_next.rva001FA48D();
}
