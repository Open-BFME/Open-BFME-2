// cl: /MD
//
// ?rva005E508F@Rva005E508F@@QAEXH@Z @0x005E508F (8B).
// Forwarder via +0x10 ptr to rowed Rva005E4DAF::rva005E4DE5; evidence callers
// at 0x005CDB23 and 0x005E691C push one int and tail call here.

class Rva005E4DAF
{
public:
	void rva005E4DE5(int v);
	void rva005E4DAF(int v);
};

class Rva005E4E1B
{
public:
	void rva005E4E1B();
};

class Rva005E508F
{
public:
	void rva005E508F(int v);
	void rva005E5097(int v);
	void rva005E509F();

private:
	char m_pad00[0x10];
	Rva005E4DAF *m_10;
};

void Rva005E508F::rva005E508F(int v)
{
	m_10->rva005E4DE5(v);
}

void Rva005E508F::rva005E5097(int v)
{
	m_10->rva005E4DAF(v);
}

// ?rva005E509F@Rva005E508F@@QAEXXZ
// Same +0x10 pointer, no argument; tail-jumps to the rowed Rva005E4E1B body.
void Rva005E508F::rva005E509F()
{
	((Rva005E4E1B *)m_10)->rva005E4E1B();
}
