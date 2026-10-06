// cl: /DNDEBUG /MD
// ?rva0052DB11@Rva0052DB11@@QAE_NH@Z, retail 0x0052DB11, 60 bytes.
// Outer/inner list search returning true on inner hit with id mismatch.
// Evidence: unlock lane; no callees; callers 0x002E76DF 0x002ED452 0x002F2ED6.
struct Rva0052DB11Obj
{
	char _pad00[0x74];
	int m_74;
};

struct Rva0052DB11Inner
{
	Rva0052DB11Inner *m_next;
	char _pad04[4];
	void *m_8;
};

struct Rva0052DB11Outer
{
	Rva0052DB11Outer *m_next;
	char _pad04[4];
	void *m_8;
};

struct Rva0052DB11Head
{
	char _pad00[0x14];
	Rva0052DB11Inner *m_14;
	char _pad18[8];
	Rva0052DB11Outer *m_20;
};

class Rva0052DB11
{
public:
	bool rva0052DB11(int arg);
private:
	Rva0052DB11Head *m_0;
};

bool Rva0052DB11::rva0052DB11(int arg)
{
	Rva0052DB11Head *h = m_0;
	if (!h)
		return false;
	for (Rva0052DB11Outer *o = h->m_20; o; o = o->m_next)
	{
		void *s = o->m_8;
		if (((Rva0052DB11Obj *)s)->m_74 == arg)
			continue;
		for (Rva0052DB11Inner *in = h->m_14; in; in = in->m_next)
		{
			if (in->m_8 == s)
				return true;
		}
	}
	return false;
}
