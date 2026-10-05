// ??0Rva0039B0C9@@QAE@PAURva0039B0C9Arg@@@Z
// partial score=0.7 date=2026-10-05
// cl: /O1 /MD
// ??0Rva0039B0C9@@QAE@PAURva0039B0C9Arg@@@Z @0x0039B0C9 40B: runs the
// pinned 0x0039AEBC worker on this with the arg +4 dword, zeroes +0x38,
// publishes the arg to +0x34, installs vptr 0x00C1AD34 and sets +0x3c.
// Evidence: single pointer arg (ret 4), ecx stays this into the pinned call,
// vtable store needs the virtual dtor (declared, pinned when found).
struct Rva0039B0C9Arg
{
	int m_00;
	int m_04;
};

class Rva0039B0C9
{
public:
	Rva0039B0C9(Rva0039B0C9Arg *a);
	void rva0039AEBC(int x);
	virtual ~Rva0039B0C9();

private:
	char m_pad00[0x34];
	Rva0039B0C9Arg *m_arg34;
	int m_38;
	unsigned char m_3c;
};

Rva0039B0C9::Rva0039B0C9(Rva0039B0C9Arg *a)
{
	rva0039AEBC(a->m_04);
	m_38 = 0;
	m_arg34 = a;
	m_3c = 1;
}
