// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva005DDE01@Rva005DDE01@@QAEXIIABUBfmeStringRecord005DDD40@@_N@Z @0x005DDE01 50B unlock bounds-checked delegate to rowed setValue 0x005DDB66
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeStringRecord005DDD40;

class Rva005DE5B5
{
public:
	void setValueRva005DDB66(unsigned int, const struct BfmeStringRecord005DDD40 &, bool);
};

class Rva005DDE01
{
public:
	void rva005DDE01(unsigned int idx, unsigned int a, const struct BfmeStringRecord005DDD40 &b, bool c);
private:
	int m_00;
	char *m_04;
	char *m_08;
};

void Rva005DDE01::rva005DDE01(unsigned int idx, unsigned int a, const struct BfmeStringRecord005DDD40 &b, bool c)
{
	int count = (m_08 - m_04) / 0x18;
	_ReadWriteBarrier();
	if (idx >= (unsigned int)count)
		return;
	((Rva005DE5B5 *)(m_04 + idx * 0x18))->setValueRva005DDB66(a, b, c);
}
