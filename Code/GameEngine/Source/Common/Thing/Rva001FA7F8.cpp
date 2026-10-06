// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001FA7F8@Rva001FA7F8@@QAEXXZ 0x001FA7F8 23B
// Evidence: chain via rowed 0x001FA4F0; null-checked virtual slot +4 at +0 then tail-jmp to rowed Rva001FA4F0 on this+4. Caller call at 0x001FB1AC. Honest Rva names.
class Helper001FA7F8
{
public:
	virtual ~Helper001FA7F8();
	virtual void tick();
};

class Rva001FA4F0
{
public:
	void rva001FA4F0();
};

class Rva001FA7F8
{
public:
	void rva001FA7F8();
private:
	Helper001FA7F8 *m_ptr;
	Rva001FA4F0 m_next;
};
void Rva001FA7F8::rva001FA7F8()
{
	Helper001FA7F8 *p = m_ptr;
	if (p)
		p->tick();
	m_next.rva001FA4F0();
}
