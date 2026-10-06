// cl: /MD
//
// ?rva001F529D@Rva001F529D@@QAEXPAUVec2001F529D@@@Z, retail 0x001F529D, 47 bytes.
// Null-checked helper at +0x1B4 via virtual slot10, copies floats at +4/+8
// to 2-float out else zeroes. Caller at 0x001F7F1C.
// Sibling of 0x001F517E (slot4) through 0x001F526E (slot9).

struct Vec2001F529D
{
	float x;
	float y;
};

struct Data001F529D
{
	char m_pad[4];
	float x;
	float y;
};

class Provider001F529D
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
	virtual void f09();
	virtual const Data001F529D *fetch();
};

class Rva001F529D
{
public:
	void rva001F529D(Vec2001F529D *out);
private:
	char m_pad[0x1B4];
	Provider001F529D *m_ptr;
};

void Rva001F529D::rva001F529D(Vec2001F529D *out)
{
	float a = 0.0f;
	float b = 0.0f;
	Provider001F529D *p = m_ptr;
	if (p != 0)
	{
		const Data001F529D *d = p->fetch();
		a = d->x;
		b = d->y;
	}
	out->x = a;
	out->y = b;
}
