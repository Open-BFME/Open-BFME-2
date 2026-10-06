// cl: /MD /EHsc
//
// ?rva001F5CA9@Rva001F5CA9@@QAEXPAXPAUHolder001F5CA9@@@Z, retail 0x001F5CA9, 39 bytes.
// Null-checked fetch at holder+0x1B4, virtual slot0 of object at +0x14,
// result stored at this+0 else zeroed. Caller at 0x001FBFD1 forwards same args.
// Sibling of 0x001F5C39 (holder+0x1AC) and 0x001F5C60 (holder+0x1B0).

class Provider001F5CA9
{
public:
	virtual void *fetch(void *arg);
};

struct Mid001F5CA9
{
	char m_pad[0x14];
	Provider001F5CA9 m_prov;
};

struct Holder001F5CA9
{
	char m_pad[0x1B4];
	Mid001F5CA9 *m_mid;
};

class Rva001F5CA9
{
public:
	void rva001F5CA9(void *arg1, Holder001F5CA9 *arg2);
private:
	void *m_ptr;
};

void Rva001F5CA9::rva001F5CA9(void *arg1, Holder001F5CA9 *arg2)
{
	Mid001F5CA9 *p = arg2->m_mid;
	if (p != 0)
		m_ptr = p->m_prov.fetch(arg1);
	else
		m_ptr = 0;
}
