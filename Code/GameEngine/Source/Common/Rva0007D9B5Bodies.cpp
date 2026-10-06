// cl: /DNDEBUG /MD
//
// Dump range 1 small pair (0x0007D9B5 26B, 0x0007D9CF 29B). Boundaries are
// ret-4 terminated extents verified from retail bytes via the tools.
// Honest address-derived names; only bytes, ABIs and displacements carry
// identity. Both call the pinned 0x0007C8AE (thiscall, no args); the first
// also calls the pinned 0x00135010 through the +0x04 member with its int
// arg. No header edits, no STL, no fallbacks.

class Rva0007D9B5Sub
{
public:
	void subMethod(int x);
};

class Rva0007D9B5Host
{
public:
	void rva0007D9B5(int x);
	void rva0007D9CF(const int *p);
	void other();

	void *m_00;
	Rva0007D9B5Sub *m_04; // +0x04
	int m_08; // +0x08
	int m_0C; // +0x0C
	int m_10; // +0x10
};

void Rva0007D9B5Host::rva0007D9B5(int x)
{
	m_04->subMethod(x);
	other();
}

void Rva0007D9B5Host::rva0007D9CF(const int *p)
{
	m_08 = p[0];
	m_0C = p[1];
	m_10 = p[2];
	other();
}
