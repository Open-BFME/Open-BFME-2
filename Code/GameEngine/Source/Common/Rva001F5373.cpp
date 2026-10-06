// cl: /MD
//
// ?rva001F5373@Rva001F5373@@QAEXPAUVec2001F5373@@@Z, retail 0x001F5373, 55 bytes.
// Null-checked helper at +0x1AC via virtual slot6 taking temp at ebp-8,
// copies floats at +0/+4 to 2-float out else zeroes. Caller at 0x001F72E8.

struct Vec2001F5373
{
	float x;
	float y;
};

class Provider001F5373
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual const Vec2001F5373 *fetch(Vec2001F5373 *tmp);
};

class Rva001F5373
{
public:
	void rva001F5373(Vec2001F5373 *out);
private:
	char m_pad[0x1AC];
	Provider001F5373 *m_ptr;
};

void Rva001F5373::rva001F5373(Vec2001F5373 *out)
{
	float a = 0.0f;
	float b = 0.0f;
	Provider001F5373 *p = m_ptr;
	if (p != 0)
	{
		Vec2001F5373 tmp;
		const Vec2001F5373 *d = p->fetch(&tmp);
		a = d->x;
		b = d->y;
	}
	out->x = a;
	out->y = b;
}
