// cl: /MD
//
// ?rva001F51AD@Rva001F51AD@@QAEXPAUVec2001F51AD@@@Z, retail 0x001F51AD, 47 bytes.
// Null-checked helper at +0x1B4 via virtual slot5, copies floats at +4/+8
// to 2-float out else zeroes. Caller at 0x001F7A7B.
// Sibling of 0x001F517E (same shape via slot4).

struct Vec2001F51AD
{
	float x;
	float y;
};

struct Data001F51AD
{
	char m_pad[4];
	float x;
	float y;
};

class Provider001F51AD
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual const Data001F51AD *fetch();
};

class Rva001F51AD
{
public:
	void rva001F51AD(Vec2001F51AD *out);
private:
	char m_pad[0x1B4];
	Provider001F51AD *m_ptr;
};

void Rva001F51AD::rva001F51AD(Vec2001F51AD *out)
{
	float a = 0.0f;
	float b = 0.0f;
	Provider001F51AD *p = m_ptr;
	if (p != 0)
	{
		const Data001F51AD *d = p->fetch();
		a = d->x;
		b = d->y;
	}
	out->x = a;
	out->y = b;
}
