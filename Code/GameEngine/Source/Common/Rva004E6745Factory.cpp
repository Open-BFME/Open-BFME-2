// cl: /O1 /MD /EHsc
//
// Two EH-guarded member factories in the 0x4E063F shape: 0x4E6745 news a
// 0x20-byte Rva004E669A with (this plus three ints) and 0x4E7F43 news a
// 0x28-byte Rva004E7D72 with (this), each stored to m_00 with this
// returned. Retail 0x004E6745 70B, 0x004E7F43 59B. Both ctors are pinned
// as honest address-derived candidates (new-expression targets); the
// 0x4E7D72 body itself is an in-range target for later recovery.

class Rva004E669A
{
public:
	Rva004E669A(void *parent, int a, int b, int c);

private:
	char m_pad[0x20];
};

class Rva004E6745
{
public:
	Rva004E6745 *rva004E6745(int a, int b, int c);

private:
	Rva004E669A *m_00;
};

// ?rva004E6745@Rva004E6745@@QAEPAURva004E6745@@HHH@Z @0x004E6745 70B.
Rva004E6745 *Rva004E6745::rva004E6745(int a, int b, int c)
{
	m_00 = new Rva004E669A(this, a, b, c);
	return this;
}

class Rva004E7D72
{
public:
	Rva004E7D72(void *parent);

private:
	char m_pad[0x28];
};

class Rva004E7F43
{
public:
	Rva004E7F43 *rva004E7F43();

private:
	Rva004E7D72 *m_00;
};

// ?rva004E7F43@Rva004E7F43@@QAEPAURva004E7F43@@XZ @0x004E7F43 59B.
Rva004E7F43 *Rva004E7F43::rva004E7F43()
{
	m_00 = new Rva004E7D72(this);
	return this;
}
