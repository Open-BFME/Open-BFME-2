// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ?rva001F8DA9@Rva001F8DA9@@QAEXXZ, retail 0x001F8DA9, 23 bytes.
// Chain via rowed 0x001F5CF7: null-checked virtual slot +4 at +0 then
// tail-jmp to rowed Rva001F5CF7 on this+0xC. Prev 0x001F8C5B next 0x001F8E45
// share flags. Callers jmp from 0x001F93FD. Honest Rva names.
class Helper001F8DA9
{
public:
	virtual ~Helper001F8DA9();
	virtual void tick();
};

class Rva001F5CF7
{
public:
	void rva001F5CF7();
};

class Rva001F8DA9
{
public:
	void rva001F8DA9();

private:
	Helper001F8DA9 *m_0;
	char m_pad4[8];
	Rva001F5CF7 m_C;
};

void Rva001F8DA9::rva001F8DA9()
{
	Helper001F8DA9 *p = m_0;
	if (p)
		p->tick();
	m_C.rva001F5CF7();
}
