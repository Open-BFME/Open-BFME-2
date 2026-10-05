// cl: /O1 /DNDEBUG /MD
// ?rva005E5884@Rva005E5884@@QAEHPAXH@Z @0x005E5884 26B.
// Helper-then-member forwarder tail-called from 0x005E5920 when RAMFile write fails.
// Evidence: thiscall ret 8 two ignored stack args; cmp [this+0x40] then [this+0x38]
// null check sharing single or eax minus 1; virtual slot 3 no args returning int.
class Rva005E5884Second
{
public:
	virtual int v0() throw();
	virtual int v1() throw();
	virtual int v2() throw();
	virtual int v3() throw();
};
class Rva005E5884
{
public:
	int rva005E5884(void *a1, int a2);
private:
	char m_pad[0x38];
	Rva005E5884Second *m_38;
	int m_3C;
	int m_40;
};
int Rva005E5884::rva005E5884(void *a1, int a2)
{
	if (m_40 == 0)
	{
		Rva005E5884Second *p = m_38;
		if (p != 0)
			return p->v3();
	}
	return -1;
}
