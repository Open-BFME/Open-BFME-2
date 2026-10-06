// cl: /MD
// ?rva004DF9E4@Rva004DF9E4@@QAEXPAXH@Z RVA 0x004DF9E4 size 42
// Iterates pointer array at +0x2c..+0x30 calling vtable+4 when [elem+4] & mask.
// Evidence: callers at 0x004E0449 0x004E0466 0x004E049B pass (ptr mask 2 1 4); neighbours use /O1 /MD.
class FilterElem
{
public:
	virtual void v0(void *a);
	virtual void v1(void *a);
	int m_flags;
};

class Rva004DF9E4
{
public:
	void rva004DF9E4(void *a, int mask);
private:
	char m_pad[0x2c];
	FilterElem **m_begin;
	FilterElem **m_end;
};

void Rva004DF9E4::rva004DF9E4(void *a, int mask)
{
	FilterElem **beg = m_begin;
	FilterElem **end = m_end;
	for (; beg != end; ++beg)
	{
		FilterElem *e = *beg;
		if (e->m_flags & mask)
			e->v1(a);
	}
}
