// cl: /MD
//
// ?rva001F523A@Rva001F523A@@QAEXPAUVec2001F523A@@@Z, retail 0x001F523A, 52 bytes.
// Null-checked helper at +0x1B4 via virtual slot8, copies floats at +4/+8
// to 2-float out else global 1.0f. Caller at 0x001F7D42.
// Sibling of 0x001F517E family with default 0.0f; default here is global.


struct Vec2001F523A
{
	float x;
	float y;
};

struct Data001F523A
{
	char m_pad[4];
	float x;
	float y;
};

class Provider001F523A
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
	virtual const Data001F523A *fetch();
};

class Rva001F523A
{
public:
	void rva001F523A(Vec2001F523A *out);
private:
	char m_pad[0x1B4];
	Provider001F523A *m_ptr;
};

void Rva001F523A::rva001F523A(Vec2001F523A *out)
{
	float a = 1.0f;
	float b = 1.0f;
	Provider001F523A *p = m_ptr;
	if (p != 0)
	{
		const Data001F523A *d = p->fetch();
		a = d->x;
		b = d->y;
	}
	out->x = a;
	out->y = b;
}
