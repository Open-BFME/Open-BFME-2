// cl: /MD
//
// ?rva001F5141@Rva001F5141@@QAEPAUPair001F5141@@PAU2@@Z, retail 0x001F5141, 61 bytes.
// Null-checked helper at +0x1B8 via virtual slot6 taking temp at ebp-8,
// copies float+int pair to out else zeroes temp. Caller at 0x001F764B.
// Returns out pointer; second field is int (mov copy) unlike float siblings.

struct Pair001F5141
{
	float x;
	float y;
};

struct Out001F5141
{
	float x;
	int y;
};

class Provider001F5141
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual const Pair001F5141 *fetch(Pair001F5141 *tmp);
};

class Rva001F5141
{
public:
	Out001F5141 *rva001F5141(Out001F5141 *out);
private:
	char m_pad[0x1B8];
	Provider001F5141 *m_ptr;
};

Out001F5141 *Rva001F5141::rva001F5141(Out001F5141 *out)
{
	Pair001F5141 tmp;
	const Pair001F5141 *d;
	Provider001F5141 *p = m_ptr;
	if (p != 0)
		d = p->fetch(&tmp);
	else
	{
		tmp.x = 0.0f;
		tmp.y = 0.0f;
		d = &tmp;
	}
	out->x = d->x;
	out->y = *(const int *)&d->y;
	return out;
}
