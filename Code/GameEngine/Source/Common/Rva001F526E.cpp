// cl: /MD
//
// ?rva001F526E@Rva001F526E@@QAEXPAUVec2001F526E@@@Z, retail 0x001F526E, 47 bytes.
// Null-checked helper at +0x1B4 via virtual slot9, copies floats at +4/+8
// to 2-float out else zeroes. Caller at 0x001F7E2F.
// Sibling of 0x001F517E (slot4) through 0x001F520B (slot7).

struct Vec2001F526E
{
	float x;
	float y;
};

struct Data001F526E
{
	char m_pad[4];
	float x;
	float y;
};

class Provider001F526E
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual const Data001F526E *fetch();
};

class Rva001F526E
{
public:
	void rva001F526E(Vec2001F526E *out);
private:
	char m_pad[0x1B4];
	Provider001F526E *m_ptr;
};

void Rva001F526E::rva001F526E(Vec2001F526E *out)
{
	float a = 0.0f;
	float b = 0.0f;
	Provider001F526E *p = m_ptr;
	if (p != 0)
	{
		const Data001F526E *d = p->fetch();
		a = d->x;
		b = d->y;
	}
	out->x = a;
	out->y = b;
}
