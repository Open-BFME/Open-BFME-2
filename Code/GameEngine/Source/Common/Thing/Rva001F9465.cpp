// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001F9465@Rva001F9465@@QAEXH@Z @0x001F9465 34B: null-checked virtual slot 3 at +0 with int arg then rowed Rva001F8E23 on this+4.
// Evidence: push esi mov esi ecx mov ecx [esi] test je then push arg plus call [eax+0xC] then push arg lea ecx [esi+4] plus call 0x001F8E23 plus pop esi ret 4; caller at 0x001FA520; precedent Rva001F8E23.cpp same shape.
class Helper001F9465
{
public:
	virtual ~Helper001F9465();
	virtual void pad1();
	virtual void pad2();
	virtual void slot3(int);
};

class Rva001F8E23
{
public:
	void rva001F8E23(int x);
};

class Rva001F9465
{
public:
	void rva001F9465(int x);
private:
	Helper001F9465 *m_ptr;
	Rva001F8E23 m_next;
};

void Rva001F9465::rva001F9465(int x)
{
	Helper001F9465 *p = m_ptr;
	if (p)
		p->slot3(x);
	m_next.rva001F8E23(x);
}
