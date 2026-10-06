// cl: /MD
//
// ?rva001F52CC@Rva001F52CC@@QAEXPAUVec2001F52CC@@@Z, retail 0x001F52CC, 52 bytes.
// Null-checked helper at +0x1B4 via virtual slot11, copies floats at +4/+8
// to 2-float out else global 1.0f. Caller at 0x001F8009.
// Sibling of 0x001F523A (slot8 with same default).


struct Vec2001F52CC
{
	float x;
	float y;
};

struct Data001F52CC
{
	char m_pad[4];
	float x;
	float y;
};

class Provider001F52CC
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
	virtual void f10();
	virtual const Data001F52CC *fetch();
};

class Rva001F52CC
{
public:
	void rva001F52CC(Vec2001F52CC *out);
private:
	char m_pad[0x1B4];
	Provider001F52CC *m_ptr;
};

void Rva001F52CC::rva001F52CC(Vec2001F52CC *out)
{
	float a = 1.0f;
	float b = 1.0f;
	Provider001F52CC *p = m_ptr;
	if (p != 0)
	{
		const Data001F52CC *d = p->fetch();
		a = d->x;
		b = d->y;
	}
	out->x = a;
	out->y = b;
}
