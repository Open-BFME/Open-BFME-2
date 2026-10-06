// cl: /MD
//
// ?rva001F520B@Rva001F520B@@QAEXPAUVec2001F520B@@@Z, retail 0x001F520B, 47 bytes.
// Null-checked helper at +0x1B4 via virtual slot7, copies floats at +4/+8
// to 2-float out else zeroes. Caller at 0x001F7C55.
// Sibling of 0x001F517E (slot4), 0x001F51AD (slot5), 0x001F51DC (slot6).

struct Vec2001F520B
{
	float x;
	float y;
};

struct Data001F520B
{
	char m_pad[4];
	float x;
	float y;
};

class Provider001F520B
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual const Data001F520B *fetch();
};

class Rva001F520B
{
public:
	void rva001F520B(Vec2001F520B *out);
private:
	char m_pad[0x1B4];
	Provider001F520B *m_ptr;
};

void Rva001F520B::rva001F520B(Vec2001F520B *out)
{
	float a = 0.0f;
	float b = 0.0f;
	Provider001F520B *p = m_ptr;
	if (p != 0)
	{
		const Data001F520B *d = p->fetch();
		a = d->x;
		b = d->y;
	}
	out->x = a;
	out->y = b;
}
