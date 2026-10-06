// cl: /MD
//
// ?rva001F51DC@Rva001F51DC@@QAEXPAUVec2001F51DC@@@Z, retail 0x001F51DC, 47 bytes.
// Null-checked helper at +0x1B4 via virtual slot6, copies floats at +4/+8
// to 2-float out else zeroes. Caller at 0x001F7B68.
// Sibling of 0x001F517E (slot4) and 0x001F51AD (slot5).

struct Vec2001F51DC
{
	float x;
	float y;
};

struct Data001F51DC
{
	char m_pad[4];
	float x;
	float y;
};

class Provider001F51DC
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual const Data001F51DC *fetch();
};

class Rva001F51DC
{
public:
	void rva001F51DC(Vec2001F51DC *out);
private:
	char m_pad[0x1B4];
	Provider001F51DC *m_ptr;
};

void Rva001F51DC::rva001F51DC(Vec2001F51DC *out)
{
	float a = 0.0f;
	float b = 0.0f;
	Provider001F51DC *p = m_ptr;
	if (p != 0)
	{
		const Data001F51DC *d = p->fetch();
		a = d->x;
		b = d->y;
	}
	out->x = a;
	out->y = b;
}
