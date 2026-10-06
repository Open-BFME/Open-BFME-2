// cl: /MD
//
// ?rva004FC275@Rva004FC275@@QAEXE@Z, retail 0x004FC275 36B: flag set with two vtable notifies.
// Evidence: __thiscall ret 4 with byte at +0x35 plus object at +0x24 calling slots 3/4; caller 0x002B6819.
class Rva004FC275Helper
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
};

class Rva004FC275
{
public:
	void rva004FC275(unsigned char v);
	void rva004FC299();
	void rva004FC2A6();

private:
	char m_pad00[0x24];
	Rva004FC275Helper *m_24;
	char m_pad28[0x0D];
	unsigned char m_35;
};

void Rva004FC275::rva004FC275(unsigned char v)
{
	if (m_35 == v)
		return;
	m_35 = v;
	Rva004FC275Helper *h = m_24;
	if (h == 0)
		return;
	if (v != 0)
		h->f3();
	else
		h->f4();
}

void Rva004FC275::rva004FC299()
{
	Rva004FC275Helper *h = m_24;
	if (h == 0)
		return;
	return h->f1();
}

void Rva004FC275::rva004FC2A6()
{
	Rva004FC275Helper *h = m_24;
	if (h == 0)
		return;
	return h->f2();
}
