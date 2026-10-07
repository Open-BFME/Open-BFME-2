// cl: /O1 /MD
// ?rva002B2BEC@Rva002B2BEC@@QAEPAXPAURva002B2BECArg@@@Z @0x002B2BEC 38B.
// Null-passing lookup (thiscall (Arg*) to void*, ret 4): probe the +0x2C
// slot through rowed 0x002104B6 on the +0xB0 helper; on null return it
// unchanged (eax is already zero, so no xor), else forward it into pinned
// 0x002BF652 on the 0xDFEF18 singleton and return that.
//
// Target evidence (game.dat, read-only, capstone): frameless (this flows
// untouched into the 0x2104B6 call), add eax,0x2c then push, al gate with
// gate with je straight to ret, singleton double-load, tail call result in
// eax. Identity unproven: honest address-derived names.
struct Rva002B2BECArg
{
	unsigned char m_pad00[0x2C];
	void *m_2C;
};

class Rva002104B6
{
public:
	void *rva002104B6(void *slot);
};

class Rva002BF652
{
public:
	void *rva002BF652(void *value);
};

extern Rva002BF652 *g_Va00DFEF18;

class Rva002B2BEC
{
public:
	void *rva002B2BEC(Rva002B2BECArg *arg);

private:
	unsigned char m_pad00[0xB0];
	Rva002104B6 *m_b0;
};

void *Rva002B2BEC::rva002B2BEC(Rva002B2BECArg *arg)
{
	void *r = m_b0->rva002104B6(&arg->m_2C);
	if (r == 0)
		return r;
	return g_Va00DFEF18->rva002BF652(r);
}
