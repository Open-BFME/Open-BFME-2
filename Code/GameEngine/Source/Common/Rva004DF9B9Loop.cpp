// cl: /MD
// ?rva004DF9B9@Rva004DF9B9@@QAEXPAXH@Z RVA 0x004DF9B9 size 43
// Sibling of 0x004DF9E4: iterates +0x2c..+0x30 calling vtable+0 when [elem+4] & mask with (arg 1).
// Evidence: callers in 0x004E01E3; neighbours use /O1 /MD; same layout as 0x004DF9E4.
class FilterElem
{
public:
	virtual void v0(void *a, int b);
	virtual void v1(void *a);
	int m_flags;
};

class Rva004DF9B9
{
public:
	void rva004DF9B9(void *a, int mask);
private:
	char m_pad[0x2c];
	FilterElem **m_begin;
	FilterElem **m_end;
};

void Rva004DF9B9::rva004DF9B9(void *a, int mask)
{
	FilterElem **beg = m_begin;
	FilterElem **end = m_end;
	for (; beg != end; ++beg)
	{
		FilterElem *e = *beg;
		if (e->m_flags & mask)
			e->v0(a, 1);
	}
}
