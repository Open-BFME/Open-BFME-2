// cl: /MD
//
// ?rva001F517E@Rva001F517E@@QAEXPAUVec2001F517E@@@Z, retail 0x001F517E, 47 bytes.
// Null-checked helper at +0x1B4 via virtual slot4, copies floats at +4/+8
// to 2-float out else zeroes. Caller at 0x001F798E.

struct Vec2001F517E
{
	float x;
	float y;
};

struct Data001F517E
{
	char m_pad[4];
	float x;
	float y;
};

class Provider001F517E
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual const Data001F517E *fetch();
};

class Rva001F517E
{
public:
	void rva001F517E(Vec2001F517E *out);
private:
	char m_pad[0x1B4];
	Provider001F517E *m_ptr;
};

void Rva001F517E::rva001F517E(Vec2001F517E *out)
{
	float a = 0.0f;
	float b = 0.0f;
	Provider001F517E *p = m_ptr;
	if (p != 0)
	{
		const Data001F517E *d = p->fetch();
		a = d->x;
		b = d->y;
	}
	out->x = a;
	out->y = b;
}
