// cl: /MD
//
// ?rva00547223@Rva00547223@@QAEPAV1@PAH0@Z retail 0x00547223 34B.
// Fluent setter: copies *a into +0 and b[0..2] into +4/+8/+0xC, then returns
// this. The returned this is why retail starts with mov eax,ecx and writes the
// whole record through eax; a void return uses ecx as the destination base and
// drops that two-byte copy. Evidence: callers 0x005472A3 0x00547511, adjacent
// unlock-lane bodies share /O1.
class Rva00547223
{
public:
	Rva00547223 *rva00547223(int *a, int *b);
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

Rva00547223 *Rva00547223::rva00547223(int *a, int *b)
{
	m_00 = *a;
	m_04 = b[0];
	m_08 = b[1];
	m_0C = b[2];
	return this;
}
