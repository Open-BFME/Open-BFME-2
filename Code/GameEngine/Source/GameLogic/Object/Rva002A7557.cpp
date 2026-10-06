// cl: /DNDEBUG /MD
// ?rva002A7557@Rva002A7461@@QAE_NPAURva002A7557In@@H@Z @0x002A7557 49B.
// Chain from 0x002A7461: ecx passes through to Rva002A7461::rva002A7461 row.
// Returns (base8 + arg+0x618 <= total) unless arg+0x618 == 0 or byte+0x11a & 0x80 forces true.
// Evidence: chain lane, neighbours Rva002A73B8Dtor/Rva002A7588Query share /O1 /DNDEBUG /MD,
// caller 0x0049CF25 pushes (eax,1) with ecx=Player+0x60 and tests al, ret 8 proves (ptr,int).
struct Rva002A7557In
{
	char m_pad0[0x11A];
	unsigned char m_flags11A;
	char m_pad11B[0x618 - 0x11B];
	int m_val618;
};

class Rva002A7461
{
public:
	int rva002A7461();
	bool rva002A7557(Rva002A7557In *p, int unused);
	int rva002A7548(int unused);

private:
	int m_pad0;
	int m_base4;
	int m_base8;
};

bool Rva002A7461::rva002A7557(Rva002A7557In *p, int unused)
{
	(void)unused;
	int v = p->m_val618;
	if (v == 0)
		return true;
	int base = m_base8;
	int total = rva002A7461();
	bool ok = (base + v <= total);
	if (p->m_flags11A & 0x80)
		return true;
	return ok;
}

int Rva002A7461::rva002A7548(int unused)
{
	(void)unused;
	int base = m_base8;
	int total = rva002A7461();
	return total - base;
}
