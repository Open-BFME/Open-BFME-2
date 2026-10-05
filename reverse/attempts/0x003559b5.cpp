// ?Make@Rva003559B5Maker@@QAEXHHH@Z
// partial score=0.75 date=2026-10-05
// cl: /O1 /EHs

struct Rva003559B5Val
{
	char m_pad[0x2c];
	Rva003559B5Val *Init(int a, int b);
};

struct Rva003559B5Host
{
	void Attach(int out, Rva003559B5Val *p);
};

struct Rva003559B5Maker
{
	Rva003559B5Host m_host;
	int m_04;
	int m_a;
	int m_b;
	void Make(int out, int a, int b);
};

void Rva003559B5Maker::Make(int out, int a, int b)
{
	Rva003559B5Val *p = new Rva003559B5Val;
	Rva003559B5Val *q;
	try
	{
		if (p != 0)
			q = p->Init(a, b);
		else
			q = 0;
		if (q != 0)
			m_host.Attach(out, q);
	}
	catch (...)
	{
		delete p;
	}
}
