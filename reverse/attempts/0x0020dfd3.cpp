// ?rva0020DFD3@Rva0020DFD3@@QAEXXZ
// partial score=0.95 date=2026-10-06
// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0020DAA5@Rva0020DAA5@@QAEXXZ @0x0020DAA5 59B
// ?rva0020DFD3@Rva0020DFD3@@QAEXXZ @0x0020DFD3 40B
// Pair sharing +0x10/+0x14 pointer range and +0x38/+0x3A flags with the
// proven Rva0020D7F9Family (cached-fin idiom, not reload).

class Rva0020DXXX
{
public:
	void rva0020D834();
};

class Rva003EDDD4
{
public:
	void rva003EDDD4(int v);
};

class Overridable;
class Rva0020DEB0
{
public:
	Overridable *rva0020DEB0();
};

class Rva003EDC16
{
public:
	void rva003EDC16();
};

class Rva0020DAA5
{
public:
	void rva0020DAA5();
private:
	char m_pad00[0x10];
	void **m_begin10;
	void **m_end14;
	char m_pad18[0x20];
	unsigned char m_38;
	unsigned char m_39;
	unsigned char m_3A;
};

class Rva0020DFD3
{
public:
	void rva0020DFD3();
private:
	char m_pad00[0x10];
	void **m_begin10;
	void **m_end14;
	char m_pad18[0x20];
	unsigned char m_38;
};

void Rva0020DAA5::rva0020DAA5()
{
	if (m_38 != 0)
		return;
	if (m_3A != 0)
		((Rva0020DXXX *)this)->rva0020D834();
	unsigned char flag = 0;
	void **beg = m_begin10;
	void **fin = m_end14;
	for (void **i = beg; i != fin; ++i)
		((Rva003EDDD4 *)*i)->rva003EDDD4((int)&flag);
}

void Rva0020DFD3::rva0020DFD3()
{
	((Rva0020DEB0 *)this)->rva0020DEB0();
	void **beg = m_begin10;
	void **fin = m_end14;
	for (void **i = beg; i != fin; ++i)
		((Rva003EDC16 *)*i)->rva003EDC16();
	m_38 = 1;
}
