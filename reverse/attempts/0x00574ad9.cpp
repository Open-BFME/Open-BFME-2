// ?rva00574AD9@Rva00574AD9@@QAE?AVRva00574AD9Result@@H@Z
// partial score=0.95 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /GX
// ?rva00574AD9@Rva00574AD9@@QAE?AVRva00574AD9Result@@H@Z retail 0x00574AD9 84B
// Retail allocates 0x20 bytes, calls the constructor body at 0x005CC3C0,
// stores the returned object pointer through [ebp+8], then increments its
// +4 count. The adjacent rowed destructor at 0x005CC37C and vtable 0x00C74E38
// support the constructor's Rva005CC37C class association. The two-word
// source at outer +8 and the constructor's scalar argument remain opaque.
class Rva005E12D1
{
public:
	virtual ~Rva005E12D1();
};

class Rva005CC37CBase
{
public:
	virtual ~Rva005CC37CBase();

protected:
	int m_ref;
};

class Rva005CC37C : public Rva005CC37CBase, public Rva005E12D1
{
public:
	Rva005CC37C(int value, const void *source);
	virtual ~Rva005CC37C();

private:
	char m_pad0C[0x10];
	int m_value1C;
};

// ?Rva00574AD9Result::Rva00574AD9Result present-unmatched
// ABI model for the one-pointer returned wrapper; the inline operation writes
// the pointer then increments its refcount. Its engine type is unresolved.
class Rva00574AD9Result
{
public:
	Rva00574AD9Result(Rva005CC37C *value) : m_value(value)
	{
		if (m_value)
			++*(int *)((char *)m_value + 4);
	}

private:
	Rva005CC37C *m_value;
};

class Rva00574AD9
{
public:
	Rva00574AD9Result rva00574AD9(int value);

private:
	char m_pad00[8];
	int m_payload[2];
};

Rva00574AD9Result Rva00574AD9::rva00574AD9(int value)
{
	return Rva00574AD9Result(new Rva005CC37C(value, m_payload));
}
