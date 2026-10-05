// ?rva00488C90@Rva00488C90@@QAEHXZ
// partial score=0.85 date=2026-10-05
// cl: /O1 /Oi- /DNDEBUG /MD /arch:SSE
//
// ?rva00488C90@Rva00488C90@@QAEHXZ @0x00488C90 52B.
// Slot 28 is called twice. A null result becomes 0.0f; otherwise the float
// at +0x324 is truncated through __ftol2.

class Rva00488C90Ret
{
public:
	char m_pad[0x324];
	float m_value;
};

class Rva00488C90
{
public:
	int rva00488C90();

	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual Rva00488C90Ret *s28();
};

int Rva00488C90::rva00488C90()
{
	volatile float v;
	if (s28() != 0)
		v = s28()->m_value;
	else
		v = 0.0f;
	return (int)v;
}
