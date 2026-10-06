// ?rva001F5A6A@Rva001F5A6A@@QAEPAXPAXHH@Z
// partial score=0.93 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva001F5A6A@Rva001F5A6A@@QAEPAXPAXHH@Z @0x001F5A6A 58B.
// Null-or-forward worker: when p2 is 0, zeroes 12B at p1; else forwards
// (p1, p2, pre-incremented this+0x48, p3) to the unrowed cdecl worker at
// 0x001F50BC (pinned from the emitted spelling; caller cleanup). Returns
// p1 in both paths. Strict param/callee types unproven.
void __cdecl rva001F50BC(void *p1, int p2, int p3, int p4);

class Rva001F5A6A
{
public:
	void *rva001F5A6A(void *p1, int p2, int p3);
private:
	char m_pad00[0x48];
	int m_48;
};

void *Rva001F5A6A::rva001F5A6A(void *p1, int p2, int p3)
{
	int zero = 0;
	if (p2 == zero)
	{
		((int *)p1)[0] = zero;
		((int *)p1)[1] = zero;
		((int *)p1)[2] = zero;
		return p1;
	}
	else
		rva001F50BC(p1, p2, ++m_48, p3);
	return p1;
}
