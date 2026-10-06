// cl: /MD /EHsc
//
// ?rva001F5C39@Rva001F5C39@@QAEXPAXPAUHolder001F5C39@@@Z, retail 0x001F5C39, 39 bytes.
// Null-checked fetch at holder+0x1AC, virtual slot0 of object at +0x14,
// result stored at this+0 else zeroed. Caller at 0x001FC438 forwards same args.

class Provider001F5C39
{
public:
	virtual void *fetch(void *arg);
};

struct Mid001F5C39
{
	char m_pad[0x14];
	Provider001F5C39 m_prov;
};

struct Holder001F5C39
{
	char m_pad[0x1AC];
	Mid001F5C39 *m_mid;
};

class Rva001F5C39
{
public:
	void rva001F5C39(void *arg1, Holder001F5C39 *arg2);
private:
	void *m_ptr;
};

void Rva001F5C39::rva001F5C39(void *arg1, Holder001F5C39 *arg2)
{
	Mid001F5C39 *p = arg2->m_mid;
	if (p != 0)
		m_ptr = p->m_prov.fetch(arg1);
	else
		m_ptr = 0;
}
