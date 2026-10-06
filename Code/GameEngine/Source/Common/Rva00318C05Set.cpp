// cl: /MD
//
// ?rva00318C05@Rva00318C05@@QAEX_N@Z, retail 0x00318C05, 45 bytes.
// Early-out byte flag at +0x64 then null-checked pointer at +0x88 with
// virtual slots 0xc (true) / 0x10 (false). Callers at 0x002B359D and
// 0x002B5AF7 loop an array and pass the outer bool through. Identity
// beyond the two offsets is unproven so the name stays honest
// address-derived.

class Rva00318C05Inner
{
public:
	virtual void f0() = 0;
	virtual void f1() = 0;
	virtual void f2() = 0;
	virtual void f3() = 0;
	virtual void f4() = 0;
};

class Rva00318C05
{
public:
	void rva00318C05(bool enabled);
private:
	char m_pre[0x64];
	bool m_64;
	char m_mid[0x23];
	Rva00318C05Inner *m_88;
};

void Rva00318C05::rva00318C05(bool enabled)
{
	if (enabled == m_64)
		return;
	Rva00318C05Inner *p = m_88;
	if (p != 0)
	{
		if (enabled)
			p->f3();
		else
			p->f4();
	}
	m_64 = enabled;
}
