// ?rva002B3A48@Rva002B3A48@@QAEHXZ
// partial score=0.93 date=2026-10-04
// cl: /O1 /MD
// ?rva002B3A48@Rva002B3A48@@QAEHXZ @0x002B3A48 84B
// Sum over pointer array at +8/+C: for each element take rowed 0x00318FBE int value minus [rowed 0x00319159 result +0x618] when non-null, accumulate.
// Evidence: unlock lane; callees rowed 0x00318FBE 0x00319159; callers 0x002B3B0B 0x002B3B16 compare two objects results; ret no args returning sum; honest address name.
class Rva00318FBE
{
public:
	int rva00318FBE();
};
class Rva00319159
{
public:
	void *rva00319159();
};
class Rva002B3A48
{
public:
	int rva002B3A48();
private:
	char m_pad00[0x8];
	Rva00318FBE **m_begin;
	Rva00318FBE **m_end;
};
// ?rva002B3A48@Rva002B3A48@@QAEHXZ present-unmatched
int Rva002B3A48::rva002B3A48()
{
	unsigned int i = 0;
	int sum = 0;
	for (; i < (unsigned int)(m_end - m_begin); ++i)
	{
		Rva00318FBE *elem = m_begin[i];
		int v = elem->rva00318FBE();
		char *q = (char *)((Rva00319159 *)elem)->rva00319159();
		if (q)
			v -= *(int *)(q + 0x618);
		sum += v;
	}
	return sum;
}
