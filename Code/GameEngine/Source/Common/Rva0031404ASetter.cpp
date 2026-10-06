// cl: /MD
// ?rva0031404A@Rva0031404A@@QAEHH@Z, retail 0x0031404A, 12 bytes.
// Honest int-field setter at +0x34 returning 0. Evidence: unlock lane with two
// direct callers; prev/next in the same 00314xxx page are small Common helpers.
// ?rva003140CF@Rva003140CF@@QAEHH@Z, retail 0x003140CF, 21 bytes.
// Same file: null-guarded self-or-arg setter at +0x44 returning 0; unlocks nine
// callers with four becoming ready.

class Rva0031404A
{
public:
	int rva0031404A(int v);

private:
	char m_pad[0x34];
	int m_34;
};

int Rva0031404A::rva0031404A(int v)
{
	m_34 = v;
	return 0;
}

class Rva003140CF
{
public:
	int rva003140CF(int v);

private:
	char m_pad[0x44];
	int m_44;
};

int Rva003140CF::rva003140CF(int v)
{
	if (!v)
		m_44 = (int)this;
	else
		m_44 = v;
	return 0;
}
