// cl: /MD /EHsc
//
// ?rva001F5CD0@Rva001F5CD0@@QAEXPAXPAUHolder001F5CD0@@@Z, retail 0x001F5CD0, 39 bytes.
// Null-checked fetch at holder+0x1B8, virtual slot0 of object at +0x14,
// result stored at this+0 else zeroed. Caller at 0x001FBC1F forwards same args.
// Sibling of 0x001F5C39 (holder+0x1AC), 0x001F5C60 (holder+0x1B0),
// 0x001F5CA9 (holder+0x1B4).

class Provider001F5CD0
{
public:
	virtual void *fetch(void *arg);
};

struct Mid001F5CD0
{
	char m_pad[0x14];
	Provider001F5CD0 m_prov;
};

struct Holder001F5CD0
{
	char m_pad[0x1B8];
	Mid001F5CD0 *m_mid;
};

class Rva001F5CD0
{
public:
	void rva001F5CD0(void *arg1, Holder001F5CD0 *arg2);
private:
	void *m_ptr;
};

void Rva001F5CD0::rva001F5CD0(void *arg1, Holder001F5CD0 *arg2)
{
	Mid001F5CD0 *p = arg2->m_mid;
	if (p != 0)
		m_ptr = p->m_prov.fetch(arg1);
	else
		m_ptr = 0;
}
