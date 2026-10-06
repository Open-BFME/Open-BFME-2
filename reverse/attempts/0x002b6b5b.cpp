// ?rva002B6B5B@Rva002B6B5B@@QAE_NPAX00_N@Z
// partial score=0.6 date=2026-10-06
// cl: /O1 /MD
// ?rva002B6B5B@Rva002B6B5B@@QAE_NPAXPAXPAX_N@Z @0x002B6B5B 116B: __thiscall
// bool with 4 stack args (ret 0x10). Gate chain: pinned 0x69D6 probe on the
// +0x4 sub-object with &p8->m18 must pass; the +0xB8 value must be non-null
// and differ from the +0x20 member of p10 (equal skips straight to the p14
// gate); else the banked 0x2B488E scan (via its established
// Rva002BA8F1Logic pin) must hit, then the pinned 0x2B2C12 worker must return
// 0/1 (a null +0xB8 shares that call site with (p8,p10) args). Then p14==0
// returns true else the rowed 0x319413 check decides. Evidence: retail
// push-order (args before ecx), shared call-site tails via jumps, neg-free
// 0/1 range check (jl/jg), xor-al false vs mov-al-1 true, shared pops
// epilogue. Boundary: Ghidra FUN_006b6b5b 116B; prev/next prologues.
// Names address-derived except rowed callees and pins.
class Rva004069D6Holder
{
public:
	int rva004069D6(void *p);
};

class Rva002BA8F1Logic
{
public:
	int rva002B488E(void *p);
};

class Rva0037DCA5;
class Rva003193EC
{
public:
	bool rva00319413(Rva0037DCA5 *p);
};

struct Arg8
{
	char m_pad[0x18];
	void *m18; // +0x18 address taken for the 0x69D6 probe
};

struct ArgC
{
	char m_pad[0xB8];
	int m_b8; // +0xB8 scan value
};

struct Arg10
{
	char m_pad[0x20];
	int m20; // +0x20 compared against the scan value
};

class Rva002B6B5B
{
public:
	bool rva002B6B5B(void *p8, void *pC, void *p10, bool p14);
	int rva002B2C12(void *a, void *b);
};

bool Rva002B6B5B::rva002B6B5B(void *p8, void *pC, void *p10, bool p14)
{
	if (!((Rva004069D6Holder *)((char *)pC + 4))->rva004069D6(&((Arg8 *)p8)->m18))
		return false;
	int v = ((ArgC *)pC)->m_b8;
	if (v != 0)
	{
		if (v == ((Arg10 *)p10)->m20)
			goto checkp14;
		int r488e = ((Rva002BA8F1Logic *)this)->rva002B488E((void *)v);
		if (r488e == 0)
			return false;
		p8 = (void *)r488e;
	}
	int r = rva002B2C12(p8, p10);
	if (r < 0 || r > 1)
		return false;
checkp14:
	if (!p14)
		return true;
	if (((Rva003193EC *)p10)->rva00319413((Rva0037DCA5 *)pC))
		return true;
	return false;
}
